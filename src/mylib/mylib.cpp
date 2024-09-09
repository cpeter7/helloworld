#include <iostream>

#include "mylib.h"
#include <cstdint>
#include <cxxopts.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

/**
 * @brief Prints out hello world and tests the JSON Lib.
 *
 */
int print_hello_world() {

  int i;
  // int x[2];
  // x[2] = 2;

  std::cout << "Hello world from mylib\n";

  std::cout << "JSON Lib Version:" << NLOHMANN_JSON_VERSION_MAJOR << "."
            << NLOHMANN_JSON_VERSION_MINOR << "." << NLOHMANN_JSON_VERSION_PATCH
            << "\n";

  std::cout << "fmt Lib Version:" << FMT_VERSION << "\n";

  std::cout << "spdlog Lib Version:" << SPDLOG_VER_MAJOR << "."
            << SPDLOG_VER_MINOR << "." << SPDLOG_VER_PATCH << "\n";

  std::cout << "cxxopts Lib Version:" << CXXOPTS__VERSION_MAJOR << "."
            << CXXOPTS__VERSION_MINOR << "." << CXXOPTS__VERSION_PATCH << "\n";

  return 1;
}

std::uint32_t factorial(std::uint32_t number) {
  return number <= 1 ? 1 : factorial(number - 1) * number;
}
