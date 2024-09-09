#include "config.h"
#include "mylib.h"
#include <iostream>
#include <nlohmann/json.hpp>

int main() {
  std::cout << "PROJECT_NAME:" << project_name << std::endl;
  std::cout << "PROJECT_VERSION:" << project_version << std::endl;

  std::cout << "JSON Lib Version:" << NLOHMANN_JSON_VERSION_MAJOR << "."
            << NLOHMANN_JSON_VERSION_MINOR << "." << NLOHMANN_JSON_VERSION_PATCH
            << "\n";

  print_hello_world();
}