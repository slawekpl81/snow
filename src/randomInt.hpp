#pragma once

#include <random>

namespace random_numbers {

inline int random_int(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<int> distrib(min, max);
  return distrib(gen);
}
}; // namespace random_numbers
