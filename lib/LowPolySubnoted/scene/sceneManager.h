#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


#include <memory>
#include "scene.h"

class SceneManager {
public:
    static void init(TFT_eSprite* canvas, uint16_t** cnvsPtr, TFT_eSPI* tft);
    void changeScene(std::unique_ptr<Scene> newScene);
    void update();
    void render();
    void exit();

private:


    ////////tools/////////
    uint32_t last4deltaTime = 0;
    uint32_t deltaTime = 0;
    

#if DEBUG_MODE
    uint8_t frameCalls = 0, physicsCalls = 0;

    unsigned long statusCheckTime = 0, clearTime = 0;

    unsigned long debugTimeStart = 0, debugPushCheck = 0, debugRenderCheck = 0; 
    unsigned long frameTimeStart = 0;
#endif // DEBUG_MODE
    

    std::unique_ptr<Scene> currentScene = nullptr;
};

#endif // SCENE_MANAGER_H
