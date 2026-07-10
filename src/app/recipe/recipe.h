#pragma once

#include "common/units.h"

#include <cstddef>
#include <cstdint>

namespace culina::app {

enum class StepKind : std::uint8_t {
    Note, // instruction only, waits for the user
    Mix,
    Heat,
    Weigh, // waits until the target weight is in the bowl
};

struct RecipeStep {
    StepKind kind = StepKind::Note;
    char text[96] = {};
    DeciCelsius target_temp = 0;
    std::uint8_t dial_speed = 0;
    std::uint32_t duration_s = 0;
    Grams target_weight = 0;
};

struct Recipe {
    char name[32] = {};
    RecipeStep steps[16];
    std::size_t step_count = 0;
};

} // namespace culina::app
