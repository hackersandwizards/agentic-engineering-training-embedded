// Decodes a C1-Link hex capture into readable frames.
//
//   c1link_dump data/captures/startup.hex
//
// Capture format: whitespace-separated hex byte pairs; '#' starts a comment.

#include "common/crc16.h"
#include "protocol/c1link.h"

#include <cctype>
#include <cstdio>
#include <string>
#include <vector>

namespace {

using namespace culina;
using namespace culina::c1link;

std::vector<std::uint8_t> read_capture(const char* path) {
    std::vector<std::uint8_t> bytes;
    std::FILE* f = std::fopen(path, "r");
    if (f == nullptr) {
        return bytes;
    }
    int c = 0;
    int nibble = -1;
    bool in_comment = false;
    while ((c = std::fgetc(f)) != EOF) {
        if (c == '#') {
            in_comment = true;
        }
        if (c == '\n') {
            in_comment = false;
        }
        if (in_comment || std::isspace(c) != 0) {
            continue;
        }
        const int value = std::isdigit(c) != 0 ? c - '0' : std::tolower(c) - 'a' + 10;
        if (value < 0 || value > 15) {
            continue;
        }
        if (nibble < 0) {
            nibble = value;
        } else {
            bytes.push_back(static_cast<std::uint8_t>((nibble << 4) | value));
            nibble = -1;
        }
    }
    std::fclose(f);
    return bytes;
}

const char* type_name(std::uint8_t type) {
    switch (type) {
    case 0x01:
        return "REQ";
    case 0x02:
        return "RSP";
    case 0x03:
        return "TLM";
    case 0x04:
        return "NAK";
    default:
        return "???";
    }
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::fprintf(stderr, "usage: %s <capture.hex>\n", argv[0]);
        return 2;
    }
    const std::vector<std::uint8_t> bytes = read_capture(argv[1]);
    if (bytes.empty()) {
        std::fprintf(stderr, "no bytes in %s\n", argv[1]);
        return 1;
    }

    std::size_t i = 0;
    int frames = 0;
    bool malformed = false;
    while (i + kHeaderSize <= bytes.size()) {
        if (bytes[i] != kSync0 || bytes[i + 1] != kSync1) {
            ++i;
            continue;
        }
        const std::uint8_t type = bytes[i + 3];
        const std::uint8_t seq = bytes[i + 4];
        const std::uint8_t msg = bytes[i + 5];
        const std::uint16_t len = get_u16(&bytes[i + 6]);
        const std::size_t frame_size = kHeaderSize + static_cast<std::size_t>(len) + kCrcSize;
        if (len > kMaxPayload || frame_size > bytes.size() - i) {
            std::fprintf(stderr, "malformed frame at offset %zu\n", i);
            malformed = true;
            ++i;
            continue;
        }

        std::printf("%04zu  %s seq=%3u msg=0x%02x len=%u  payload=", i, type_name(type), seq, msg,
                    len);
        for (std::uint16_t j = 0; j < len; ++j) {
            std::printf("%02x", bytes[i + kHeaderSize + j]);
        }
        const std::uint16_t wire_crc = get_u16(&bytes[i + kHeaderSize + len]);
        const std::uint16_t computed = crc16_ccitt(&bytes[i + 2], kHeaderSize - 2 + len);
        std::printf("  crc=%04x %s\n", wire_crc, wire_crc == computed ? "ok" : "BAD");
        if (wire_crc != computed) {
            malformed = true;
        }

        i += frame_size;
        ++frames;
    }
    if (i < bytes.size()) {
        std::fprintf(stderr, "truncated data at offset %zu\n", i);
        malformed = true;
    }
    std::printf("%d frame(s)\n", frames);
    return frames > 0 && !malformed ? 0 : 1;
}
