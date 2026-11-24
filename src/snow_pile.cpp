#include "snow_pile.hpp"

#include "dev_print.hpp"
#include "randomInt.hpp"

#include "raylib.h"

// #include <algorithm>

// ------------------------------------------------------
SnowPile::SnowPile(int width, int height)
    : screenWidth(width), screenHeight(height) {

  // screenWidth = GetScreenWidth();
  // screenHeight = GetScreenHeight();

  int numColumns = (screenWidth / grainSize) + 1;

  // print_val(grainSize, "grainSize");
  // print_val(screenWidth, "screenWidth");
  // print_val(numColumns, "numColumns");

  columns.resize(numColumns, 0);
}

// ------------------------------------------------------
void SnowPile::addSnow(float x, int amount) {
  int col = static_cast<int>(x / grainSize);

  if (col >= 0 && col < columns.size()) {
    columns[col] += amount;
  }
}

// ------------------------------------------------------
void SnowPile::update() {
  bool left2Right = random_numbers::random_int(0, 1) == 0;

  if (left2Right) {
    for (size_t i = 0; i < columns.size() - 1; ++i) {
      if (columns[i] - columns[i + 1] > maxSlope) {
        columns[i]--;
        columns[i + 1]++;
      } else if (columns[i + 1] - columns[i] > maxSlope) {
        columns[i + 1]--;
        columns[i]++;
      }
    }
  } else {
    for (size_t i = columns.size() - 1; i > 0; i--) {
      if (columns[i] - columns[i - 1] > maxSlope) {
        columns[i]--;
        columns[i - 1]++;
      } else if (columns[i - 1] - columns[i] > maxSlope) {
        columns[i - 1]--;
        columns[i]++;
      }
    }
  }
}

// ------------------------------------------------------
void SnowPile::draw() const {
  for (size_t i = 0; i < columns.size(); ++i) {
    int count = columns[i];
    if (count <= 0)
      continue;

    int x = static_cast<int>(i * grainSize);
    int totalHeight = count * grainSize;
    int startY = screenHeight - totalHeight;

    DrawRectangle(x, startY, grainSize, totalHeight, RAYWHITE);
    DrawRectangle(x, startY, grainSize, grainSize, LIGHTGRAY);
  }
}
// ------------------------------------------------------
