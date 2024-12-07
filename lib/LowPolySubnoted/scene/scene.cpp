#include "Scene.h"

// Define the static const members
const uint8_t Scene::SCREEN_WIDTH = 240;  // Replace with your actual values
const uint8_t Scene::SCREEN_HEIGHT = 240;
const uint8_t Scene::SPLIT_SCREEN = 2;

// Define the static member variables
TFT_eSprite* Scene::canvas = nullptr;
TFT_eSprite* Scene::canvas1 = nullptr;
uint16_t** Scene::cnvsPtr = nullptr;
uint16_t** Scene::cnvsPtr1 = nullptr;
TFT_eSPI* Scene::tft = nullptr;