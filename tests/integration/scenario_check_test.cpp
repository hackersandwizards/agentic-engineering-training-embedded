#include "cli/script_runner.h"

#include <gtest/gtest.h>

#include <cctype>
#include <filesystem>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;

std::vector<std::string> list_scenarios() {
    std::vector<std::string> paths;
    for (const char* group : {"checks", "demo"}) {
        const fs::path dir = fs::path(CULINA_DATA_DIR) / "scenarios" / group;
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.path().extension() == ".scn") {
                paths.push_back(entry.path().string());
            }
        }
    }
    std::sort(paths.begin(), paths.end());
    return paths;
}

class ScenarioCheck : public ::testing::TestWithParam<std::string> {};

TEST_P(ScenarioCheck, Passes) {
    culina::system::SystemSim sim;
    EXPECT_EQ(culina::cli::run_script(sim, GetParam().c_str(), /*echo=*/false), culina::Status::Ok)
        << "scenario failed: " << GetParam();
}

std::string scenario_name(const ::testing::TestParamInfo<std::string>& info) {
    const fs::path path(info.param);
    std::string name = path.parent_path().filename().string() + "_" + path.stem().string();
    for (char& c : name) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            c = '_';
        }
    }
    return name;
}

INSTANTIATE_TEST_SUITE_P(All, ScenarioCheck, ::testing::ValuesIn(list_scenarios()), scenario_name);

} // namespace
