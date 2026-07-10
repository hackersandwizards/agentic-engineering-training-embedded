#pragma once

#include "app/recipe/recipe.h"
#include "common/result.h"

namespace culina::app {

// Parses the .rcp recipe format:
//
//   name: Bread Dough
//   step: mix | speed=3 | time=300 | text=Knead to a smooth dough
//   step: weigh | weight=500 | text=Add flour until 500 g
//   step: heat | temp=37.0 | time=1200 | speed=1 | text=Proof
//   step: note | text=Rest outside the bowl
//
// Unknown keys are ignored; comment lines start with '#'.
Status parse_recipe_file(const char* path, Recipe* out);

} // namespace culina::app
