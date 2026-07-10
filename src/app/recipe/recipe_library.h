#pragma once

#include "app/recipe/recipe.h"
#include "common/result.h"

#include <cstddef>

namespace culina::app {

// All recipes found in a directory of .rcp files, loaded once at startup.
class RecipeLibrary {
public:
    Status load_directory(const char* dir_path);

    std::size_t count() const { return count_; }
    const Recipe* at(std::size_t index) const { return index < count_ ? &recipes_[index] : nullptr; }
    const Recipe* find(const char* name) const;

    static constexpr std::size_t kMaxRecipes = 64;

private:
    Recipe recipes_[kMaxRecipes];
    std::size_t count_ = 0;
};

} // namespace culina::app
