#include "SceneManager.h"


// Define the static member variables
TFT_eSprite* Scene::canvas = nullptr;
uint16_t** Scene::cnvsPtr = nullptr;
TFT_eSPI* Scene::tft = nullptr;


void SceneManager::init(TFT_eSprite* canvas, uint16_t** cnvsPtr, TFT_eSPI* tft)
{
    Scene::canvas = canvas;
    Scene::cnvsPtr = cnvsPtr;
    Scene::tft = tft;
    currentScene = nullptr;

    last4deltaTime = millis();
}


void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    if (currentScene) {
        currentScene->exit();
    }
    currentScene = std::move(newScene);
    currentScene->setSceneManager(this);
    currentScene->enter();
}

void SceneManager::update() {
#if DEBUG_MODE
    physicsCalls++;
#endif

    if (currentScene) {
        currentScene->update(deltaTime);
    }
}

void SceneManager::render() {
#if DEBUG_MODE
    debugTimeStart = micros();
#endif 

    fixedTime = millis()*60/1000; //float which every integer is 1/60 of second //todo remove it
    deltaTime = millis() - last4deltaTime;
    if (deltaTime > 100)
        deltaTime = 100;
    last4deltaTime = millis();

    //render
    if (currentScene) {
        currentScene->render();
    }

#if DEBUG_MODE    
    debugPushCheck = micros() - debugTimeStart;

    frameCalls++;
    if (millis() - statusCheckTime > 1000)
    {        
        //log_d("Free heap: %d/%d %d%", ESP.getFreeHeap(), ESP.getHeapSize(), 100*ESP.getFreeHeap()/ESP.getHeapSize());
        log_d("FPS: %d", frameCalls);
        log_d("PhysCallsPS: %d", physicsCalls);
        log_d("Push time: %dmcs\n", debugPushCheck);
        // log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

        statusCheckTime = millis();
        frameCalls = 0;
        physicsCalls = 0;
    }
#endif 
}