#include "snowflakes.hpp"
#include "randomInt.hpp"
#include "raylib.h"
#include "snow_pile.hpp"
#include <cmath>

// ----------------------------------------------------------------
Snowflake::Snowflake() {
  // Rozrzucenie po całym ekranie na starcie
  position = {
      static_cast<float>(random_numbers::random_int(0, GetScreenWidth())),
      static_cast<float>(random_numbers::random_int(-100, GetScreenHeight()))};

  float temp = random_numbers::random_int(2, 10) *
               0.1f; // Zakres 0.2 - 1.0 (brak zbyt wolnych płatków)

  speed = {0.0f, 150.0f * temp};
  scale = 0.25f * temp;
  rotation = static_cast<float>(random_numbers::random_int(0, 360));
  rotSpeed = static_cast<float>(random_numbers::random_int(-40, 40));
  swayOffset = static_cast<float>(random_numbers::random_int(0, 100));
  spriteIndex_x = random_numbers::random_int(0, 2);
  spriteIndex_y = random_numbers::random_int(0, 3);
  alpha = 0.4f + (0.6f * temp); // Nawet dalekie płatki będą lekko widoczne

  flipAngle = 0.0f;
  flipSpeed = 0;

  if (random_numbers::random_int(0, 10) < 3)
    flipSpeed = random_numbers::random_int(0, 2);
}

// ----------------------------------------------------------------
void Snowflake::update(float deltaTime, SnowPile &pile) {
  // Ruch wahadłowy oparty o GetTime()
  position.x += sinf(static_cast<float>(GetTime()) * 2.0f + swayOffset) *
                35.0f * deltaTime;
  position.y += speed.y * deltaTime;
  rotation += rotSpeed * deltaTime;

  float size = 256.0f * scale;
  float halfSize = size / 2.0f;

  flipAngle += flipSpeed * deltaTime;

  // Reset po wyjściu za dolną krawędź
  if ((position.y - halfSize) > GetScreenHeight()) {
    // snow pile
    int snowAmount = (scale > 0.15f) ? 2 : 1;
    pile.addSnow(position.x, snowAmount);

    position.y = -halfSize;
    position.x =
        static_cast<float>(random_numbers::random_int(0, GetScreenWidth()));
  }
}

// ----------------------------------------------------------------
void Snowflake::draw(Texture2D &tex) const {
  float size = 256.0f * scale;
  float width3d = size * cosf(flipAngle);

  Rectangle source = {spriteIndex_x * 256.0f, spriteIndex_y * 256.0f, 256.0f,
                      256.0f};

  // Rectangle dest = {position.x, position.y, size, size};
  // Vector2 origin = {size / 2.0f, size / 2.0f}; // Obrót wokół środka

  Rectangle dest = {position.x, position.y, fabsf(width3d), size};
  Vector2 origin = {fabsf(width3d) / 2.0f, size / 2.0f}; // Obrót wokół środka
  DrawTexturePro(tex, source, dest, origin, rotation, Fade(WHITE, alpha));
}
