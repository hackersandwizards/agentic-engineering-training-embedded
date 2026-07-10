#include "cli/script_runner.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;

std::vector<std::string> list_check_scenarios() {
    std::vector<std::string> paths;
    const fs::path dir = fs::path(CULINA_DATA_DIR) / "scenarios" / "checks";
    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.path().extension() == ".scn") {
            paths.push_back(entry.path().string());
        }
    }
    std::sort(paths.begin(), paths.end());
    return paths;
}

class ScenarioCheck : public ::testing::TestWithParam<std::string> {};

TEST_P(ScenarioCheck, Passes) {
    culina::system::SystemSim sim;
    EXPECT_EQ(culina::cli::run_script(sim, GetParam().c_str(), /*echo=*/false),
              culina::Status::Ok)
        << "scenario failed: " << GetParam();
}

std::string scenario_name(const ::testing::TestParamInfo<std::string>& info) {
    std::string name = fs::path(info.param).stem().string();
    for (char& c : name) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            c = '_';
        }
    }
    return name;
}

INSTANTIATE_TEST_SUITE_P(Checks, ScenarioCheck, ::testing::ValuesIn(list_check_scenarios()),
                         scenario_name);

} // namespace
