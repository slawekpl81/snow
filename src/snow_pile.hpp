#pragma once

#include "raylib.h"
#include <vector>

class SnowPile {
public:
  static constexpr int grainSize = 4;
  static constexpr int maxSlope = 2;

  explicit SnowPile(int width, int height);

  void addSnow(float x, int amount = 1);

  void update();

  void draw() const;


  int screenWidth, screenHeight;
  std::vector<int> columns;
};
