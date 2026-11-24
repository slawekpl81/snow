#pragma once

#include <print>

// -----------------------------------------------------
inline void print_val(int val, std::string &&name) {
  std::println(stdout, "[DEV] {}: {}", name, val);
}
// -----------------------------------------------------
inline void print_val(float val, std::string &&name) {
  std::println(stdout, "[DEV] {}: {}", name, val);
}
// -----------------------------------------------------
