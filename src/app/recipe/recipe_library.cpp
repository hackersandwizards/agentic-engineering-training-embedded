#include "app/recipe/recipe_library.h"

#include "app/recipe/recipe_parser.h"
#include "common/logging.h"

#include <cstdio>
#include <cstring>
#include <dirent.h>

namespace culina::app {

namespace {
bool has_rcp_extension(const char* name) {
    const std::size_t len = std::strlen(name);
    return len > 4 && std::strcmp(name + len - 4, ".rcp") == 0;
}
} // namespace

Status RecipeLibrary::load_directory(const char* dir_path) {
    DIR* dir = ::opendir(dir_path);
    if (dir == nullptr) {
        return Status::InvalidArgument;
    }

    count_ = 0;
    const dirent* entry = nullptr;
    while ((entry = ::readdir(dir)) != nullptr) {
        if (!has_rcp_extension(entry->d_name)) {
            continue;
        }
        if (count_ >= kMaxRecipes) {
            CULINA_LOG_WARN("recipe library full, ignoring %s", entry->d_name);
            continue;
        }
        char path[512];
        std::snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        const Status status = parse_recipe_file(path, &recipes_[count_]);
        if (status != Status::Ok) {
            CULINA_LOG_WARN("skipping %s: %s", entry->d_name, status_name(status));
            continue;
        }
        ++count_;
    }
    ::closedir(dir);
    return Status::Ok;
}

const Recipe* RecipeLibrary::find(const char* name) const {
    for (std::size_t i = 0; i < count_; ++i) {
        if (std::strcmp(recipes_[i].name, name) == 0) {
            return &recipes_[i];
        }
    }
    return nullptr;
}

} // namespace culina::app
