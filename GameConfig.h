#pragma once
#include <string>

// UI params

const unsigned int X_FIELD_SIZE = 16;
const unsigned int Y_FIELD_SIZE = 16;
const unsigned int CELL_SIZE = 40;
const int STATUS_BAR_HIGHT = CELL_SIZE * 1;
const int BORDER_THICKNESS = CELL_SIZE / 4;
const unsigned int X_WINDOW_SIZE = X_FIELD_SIZE * CELL_SIZE + BORDER_THICKNESS * 2;
const unsigned int Y_WINDOW_SIZE = Y_FIELD_SIZE * CELL_SIZE + BORDER_THICKNESS * 2 + STATUS_BAR_HIGHT;

// Graphics

const std::string SPRITESHEET_PATH = "snake-graphics.png";
const unsigned int SPRITE_SIZE = 64;

// Movement

const std::int8_t DIRECT_UP = 1;
const std::int8_t DIRECT_RIGHT = 2;
const std::int8_t DIRECT_DOWN = 3;
const std::int8_t DIRECT_LEFT = 4;