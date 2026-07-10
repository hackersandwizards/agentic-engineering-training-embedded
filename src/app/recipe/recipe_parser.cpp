#include "app/recipe/recipe_parser.h"

#include <cerrno>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace culina::app {

namespace {

const char* skip_spaces(const char* p) {
    while (*p == ' ' || *p == '\t') {
        ++p;
    }
    return p;
}

void trim_end(char* s) {
    std::size_t len = std::strlen(s);
    while (len > 0 &&
           (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

bool parse_kind(const char* token, StepKind* kind) {
    if (std::strcmp(token, "note") == 0) {
        *kind = StepKind::Note;
    } else if (std::strcmp(token, "mix") == 0) {
        *kind = StepKind::Mix;
    } else if (std::strcmp(token, "heat") == 0) {
        *kind = StepKind::Heat;
    } else if (std::strcmp(token, "weigh") == 0) {
        *kind = StepKind::Weigh;
    } else {
        return false;
    }
    return true;
}

struct Fields {
    bool temp = false;
    bool speed = false;
    bool time = false;
    bool weight = false;
};

bool parse_long(const char* text, long min, long max, long* out) {
    errno = 0;
    char* end = nullptr;
    const long value = std::strtol(text, &end, 10);
    if (errno != 0 || end == text || *skip_spaces(end) != '\0' || value < min || value > max) {
        return false;
    }
    *out = value;
    return true;
}

bool parse_temperature(const char* text, DeciCelsius* out) {
    errno = 0;
    char* end = nullptr;
    const float value = std::strtof(text, &end);
    if (errno != 0 || end == text || *skip_spaces(end) != '\0' || !std::isfinite(value) ||
        value < 37.0f || value > 160.0f) {
        return false;
    }
    *out = from_celsius(value);
    return true;
}

bool apply_field(RecipeStep* step, Fields* fields, const char* key, const char* value) {
    if (std::strcmp(key, "text") == 0) {
        std::strncpy(step->text, value, sizeof(step->text) - 1);
    } else if (std::strcmp(key, "temp") == 0) {
        fields->temp = parse_temperature(value, &step->target_temp);
        return fields->temp;
    } else if (std::strcmp(key, "speed") == 0) {
        long parsed = 0;
        fields->speed = parse_long(value, 0, 10, &parsed);
        step->dial_speed = static_cast<std::uint8_t>(parsed);
        return fields->speed;
    } else if (std::strcmp(key, "time") == 0) {
        long parsed = 0;
        fields->time = parse_long(value, 1, 86400, &parsed);
        step->duration_s = static_cast<std::uint32_t>(parsed);
        return fields->time;
    } else if (std::strcmp(key, "weight") == 0) {
        long parsed = 0;
        fields->weight = parse_long(value, 1, 2200, &parsed);
        step->target_weight = static_cast<Grams>(parsed);
        return fields->weight;
    }
    return true;
}

Status parse_step(char* body, RecipeStep* step) {
    char* cursor = body;
    bool first = true;
    Fields fields;
    while (cursor != nullptr) {
        char* token = cursor;
        char* bar = std::strchr(cursor, '|');
        if (bar != nullptr) {
            *bar = '\0';
            cursor = bar + 1;
        } else {
            cursor = nullptr;
        }
        token = const_cast<char*>(skip_spaces(token));
        trim_end(token);

        if (first) {
            StepKind kind = StepKind::Note;
            if (!parse_kind(token, &kind)) {
                return Status::InvalidArgument;
            }
            step->kind = kind;
            first = false;
            continue;
        }

        char* eq = std::strchr(token, '=');
        if (eq == nullptr) {
            continue;
        }
        *eq = '\0';
        trim_end(token);
        if (!apply_field(step, &fields, token, skip_spaces(eq + 1))) {
            return Status::InvalidArgument;
        }
    }
    const bool valid =
        step->kind == StepKind::Note ||
        (step->kind == StepKind::Mix && fields.speed && step->dial_speed > 0 && fields.time) ||
        (step->kind == StepKind::Heat && fields.temp && fields.time) ||
        (step->kind == StepKind::Weigh && fields.weight);
    return valid ? Status::Ok : Status::InvalidArgument;
}

} // namespace

Status parse_recipe_file(const char* path, Recipe* out) {
    if (path == nullptr || out == nullptr) {
        return Status::InvalidArgument;
    }
    std::FILE* file = std::fopen(path, "r");
    if (file == nullptr) {
        return Status::InvalidArgument;
    }

    *out = Recipe{};
    char line[256];
    Status status = Status::Ok;
    while (std::fgets(line, sizeof(line), file) != nullptr) {
        if (std::strchr(line, '\n') == nullptr && std::feof(file) == 0) {
            status = Status::Overflow;
            break;
        }
        trim_end(line);
        const char* p = skip_spaces(line);
        if (*p == '\0' || *p == '#') {
            continue;
        }
        if (std::strncmp(p, "name:", 5) == 0) {
            std::strncpy(out->name, skip_spaces(p + 5), sizeof(out->name) - 1);
        } else if (std::strncmp(p, "step:", 5) == 0) {
            if (out->step_count >= sizeof(out->steps) / sizeof(out->steps[0])) {
                status = Status::Overflow;
                break;
            }
            char body[256];
            std::strncpy(body, skip_spaces(p + 5), sizeof(body) - 1);
            body[sizeof(body) - 1] = '\0';
            status = parse_step(body, &out->steps[out->step_count]);
            if (status != Status::Ok) {
                break;
            }
            ++out->step_count;
        }
    }
    if (status == Status::Ok && std::ferror(file) != 0) {
        status = Status::HardwareFault;
    }
    std::fclose(file);

    if (status == Status::Ok && (out->name[0] == '\0' || out->step_count == 0)) {
        status = Status::InvalidArgument;
    }
    return status;
}

} // namespace culina::app
