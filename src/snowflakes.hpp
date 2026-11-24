#pragma once

#include "raylib.h"
#include "snow_pile.hpp"
#include <vector>

// -----------------------------------------------------------
class Snowflake {
public:
  Vector2 position;
  Vector2 speed;
  float scale;
  float rotation;
  float rotSpeed;
  float swayOffset;
  int spriteIndex_x, spriteIndex_y;
  float alpha;

  float flipAngle, flipSpeed;

  explicit Snowflake();
  // UPDATE
  void update(float deltaTime, SnowPile &pile);

  // DRAW
  void draw(Texture2D &tex) const;
};

// -----------------------------------------------------------
class AllSnowflakes {
public:
  static constexpr int size = 100;
  std::vector<Snowflake> data;

  AllSnowflakes() : data(size) {}

  // UPDATE
  void update(float dt, SnowPile &pile) {
    for (auto &sf : data) {
      sf.update(dt, pile);
    }
  }

  // DRAW
  void draw(Texture2D &tex) {
    for (auto const &sf : data) {
      sf.draw(tex);
    }
  }
};
