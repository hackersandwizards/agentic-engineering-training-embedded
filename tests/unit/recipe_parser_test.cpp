#include "app/recipe/recipe_parser.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>

namespace {

using namespace culina;
using namespace culina::app;

std::string write_recipe(const char* content) {
    const std::string path = ::testing::TempDir() + "recipe_under_test.rcp";
    std::FILE* f = std::fopen(path.c_str(), "w");
    EXPECT_NE(f, nullptr);
    std::fputs(content, f);
    std::fclose(f);
    return path;
}

TEST(RecipeParser, ParsesAFullRecipe) {
    const std::string path = write_recipe("# breakfast classic\n"
                                          "name: Porridge\n"
                                          "step: weigh | weight=250 | text=Add oats\n"
                                          "step: heat | temp=95.0 | time=600 | speed=1 | "
                                          "text=Simmer gently\n"
                                          "step: note | text=Let it rest\n");
    Recipe recipe;
    ASSERT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::Ok);
    EXPECT_STREQ(recipe.name, "Porridge");
    ASSERT_EQ(recipe.step_count, 3u);

    EXPECT_EQ(recipe.steps[0].kind, StepKind::Weigh);
    EXPECT_EQ(recipe.steps[0].target_weight, 250);
    EXPECT_STREQ(recipe.steps[0].text, "Add oats");

    EXPECT_EQ(recipe.steps[1].kind, StepKind::Heat);
    EXPECT_EQ(recipe.steps[1].target_temp, 950);
    EXPECT_EQ(recipe.steps[1].duration_s, 600u);
    EXPECT_EQ(recipe.steps[1].dial_speed, 1);

    EXPECT_EQ(recipe.steps[2].kind, StepKind::Note);
}

TEST(RecipeParser, RejectsUnknownStepKind) {
    const std::string path = write_recipe("name: Broken\nstep: fry | time=60\n");
    Recipe recipe;
    EXPECT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::InvalidArgument);
}

TEST(RecipeParser, RejectsRecipeWithoutSteps) {
    const std::string path = write_recipe("name: Empty\n");
    Recipe recipe;
    EXPECT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::InvalidArgument);
}

TEST(RecipeParser, IgnoresUnknownKeysAndComments) {
    const std::string path = write_recipe("name: Tea\n"
                                          "# steep, do not boil\n"
                                          "step: heat | temp=80.0 | time=180 | rating=5\n");
    Recipe recipe;
    ASSERT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::Ok);
    EXPECT_EQ(recipe.steps[0].target_temp, 800);
}

TEST(RecipeParser, LongNamesAreTruncatedSafely) {
    const std::string long_name(60, 'X');
    const std::string path =
        write_recipe(("name: " + long_name + "\nstep: note | text=hello\n").c_str());
    Recipe recipe;
    ASSERT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::Ok);
    EXPECT_EQ(std::strlen(recipe.name), sizeof(recipe.name) - 1);
}

TEST(RecipeParser, MissingFileFails) {
    Recipe recipe;
    EXPECT_EQ(parse_recipe_file("/nonexistent/nope.rcp", &recipe), Status::InvalidArgument);
}

TEST(RecipeParser, RejectsInvalidPointersAndOversizedLines) {
    Recipe recipe;
    EXPECT_EQ(parse_recipe_file(nullptr, &recipe), Status::InvalidArgument);
    EXPECT_EQ(parse_recipe_file("unused", nullptr), Status::InvalidArgument);

    const std::string content =
        "name: " + std::string(300, 'x') + "\nstep: note | text=unreachable\n";
    const std::string path = write_recipe(content.c_str());
    EXPECT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::Overflow);
}

TEST(RecipeParser, RejectsInvalidNumericFields) {
    const char* invalid_recipes[] = {
        "name: Bad\nstep: mix | speed=-1 | time=10\n",
        "name: Bad\nstep: mix | speed=11 | time=10\n",
        "name: Bad\nstep: mix | speed=2 | time=-1\n",
        "name: Bad\nstep: heat | temp=nan | time=10 | speed=1\n",
        "name: Bad\nstep: heat | temp=200 | time=10 | speed=1\n",
        "name: Bad\nstep: weigh | weight=0\n",
        "name: Bad\nstep: weigh | weight=2201\n",
    };

    for (const char* content : invalid_recipes) {
        const std::string path = write_recipe(content);
        Recipe recipe;
        EXPECT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::InvalidArgument) << content;
    }
}

TEST(RecipeParser, RejectsMissingRequiredFields) {
    const char* incomplete_recipes[] = {
        "name: Bad\nstep: mix | speed=2\n",
        "name: Bad\nstep: heat | time=10 | speed=1\n",
        "name: Bad\nstep: weigh | text=Nothing to weigh\n",
    };

    for (const char* content : incomplete_recipes) {
        const std::string path = write_recipe(content);
        Recipe recipe;
        EXPECT_EQ(parse_recipe_file(path.c_str(), &recipe), Status::InvalidArgument) << content;
    }
}

} // namespace
