//
// Created by Leonardo rocha on 3/31/25.
//

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

TEST(CppForgeBootstrapTest, GeneratesRootCMakeLists) {
// Arrange
fs::path testRoot = "test_sandbox";
fs::create_directory(testRoot);

std::string yamlContent = R"(
cmake:
  version: 3.21
  project: test_project

modules:
  - name: core
    type: lib
    test: true
    packages: []
  - name: app
    type: exe
    test: true
    packages: []
)";

fs::path yamlPath = testRoot / "modules.yaml";
std::ofstream(yamlPath) << yamlContent;

// Act
// TODO: Call cppforge bootstrap logic here
// simulate_bootstrap(testRoot);

// Assert
fs::path rootCMake = testRoot / "CMakeLists.txt";
ASSERT_TRUE(fs::exists(rootCMake)) << "CMakeLists.txt should be generated at root";

std::ifstream cmakeFile(rootCMake);
std::string cmakeContent((std::istreambuf_iterator<char>(cmakeFile)), std::istreambuf_iterator<char>());

EXPECT_NE(cmakeContent.find("project(test_project)"), std::string::npos);
EXPECT_NE(cmakeContent.find("add_subdirectory(core)"), std::string::npos);
EXPECT_NE(cmakeContent.find("add_subdirectory(app)"), std::string::npos);

// Cleanup
fs::remove_all(testRoot);
}
