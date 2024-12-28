#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H


#include <memory>
#include "scene.h"

#include <render/renderer.h>
#include <render/basicStrategy.h>

class SceneManager {
public:

    // static void init();
    
    void initRenderer(){
        renderer.init();
        renderer.setStrategy(std::unique_ptr<IRendererStrategy>(new BasicRendererStrategy()));
    };

    void changeScene(std::shared_ptr<Scene> newScene);
    void update();
    void render();
    void exit();


private:

    GraphicsRenderer renderer;

    ////////tools/////////
    uint32_t last4deltaTime = 0;
    uint32_t deltaTime = 0;


#if DEBUG_MODE
    uint8_t frameCalls = 0, physicsCalls = 0;

    unsigned long statusCheckTime = 0, clearTime = 0;

    unsigned long debugTimeStart = 0, debugPushCheck = 0, debugRenderCheck = 0; 
    unsigned long frameTimeStart = 0;
#endif // DEBUG_MODE


    std::shared_ptr<Scene> currentScene = nullptr;
};


#endif // SCENE_MANAGER_H
