#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include "scene.h"

class SceneManager {
public:
    void init(TFT_eSprite* canvas, TFT_eSprite* canvas1, uint16_t** cnvsPtr, uint16_t** cnvsPtr1, TFT_eSPI* tft);
    void changeScene(std::unique_ptr<Scene> newScene);
    void update(float deltaTime);
    void render();
    void exit();

private:
    std::unique_ptr<Scene> currentScene;
};

#endif // SCENE_MANAGER_H
