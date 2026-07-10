#include "common/logging.h"

#include "common/result.h"

#include <cstdio>

namespace culina {
namespace {

void default_sink(LogLevel level, const char* message) {
    static const char* const names[] = {"DEBUG", "INFO", "WARN", "ERROR"};
    std::fprintf(stderr, "[%s] %s\n", names[static_cast<int>(level)], message);
}

LogSink g_sink = default_sink;
LogLevel g_level = LogLevel::Info;

} // namespace

const char* status_name(Status status) {
    switch (status) {
    case Status::Ok:
        return "Ok";
    case Status::Timeout:
        return "Timeout";
    case Status::CrcMismatch:
        return "CrcMismatch";
    case Status::Overflow:
        return "Overflow";
    case Status::InvalidArgument:
        return "InvalidArgument";
    case Status::NotReady:
        return "NotReady";
    case Status::HardwareFault:
        return "HardwareFault";
    case Status::ProtocolError:
        return "ProtocolError";
    }
    return "Unknown";
}

void set_log_sink(LogSink sink) { g_sink = sink != nullptr ? sink : default_sink; }

void set_log_level(LogLevel level) { g_level = level; }

void log_message(LogLevel level, const char* fmt, ...) {
    if (level < g_level) {
        return;
    }
    char buffer[192];
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    g_sink(level, buffer);
}

} // namespace culina
