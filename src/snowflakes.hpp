#pragma once

#include "raylib.h"
#include <vector>

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

  explicit Snowflake();

  void update(float deltaTime);

  void draw(Texture2D &tex) const;
};

class AllSnowflakes {
public:
  static constexpr int size = 100;
  std::vector<Snowflake> data;

  AllSnowflakes() : data(size) {}

  void update(float dt) {
    for (auto &sf : data) {
      sf.update(dt);
    }
  }

  void draw(Texture2D &tex) {
    for (auto const &sf : data) {
      sf.draw(tex);
    }
  }
};
