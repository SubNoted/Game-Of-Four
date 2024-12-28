#include "SceneManager.h"



void SceneManager::changeScene(std::shared_ptr<Scene> newScene) {
    if (currentScene) {
        currentScene->vertices.clear();
        currentScene->polygons.clear();
        currentScene->exit();

        last4deltaTime = millis();
    }
    currentScene = std::move(newScene);

    currentScene->vertices.reserve(8);
    currentScene->polygons.reserve(12);

    currentScene->setSceneManager(this);
    currentScene->enter();
}

void SceneManager::update() {
#if DEBUG_MODE
    physicsCalls++;
#endif

    deltaTime = millis() - last4deltaTime;
    if (deltaTime > 100)
        deltaTime = 100;
    last4deltaTime = millis();

    if (currentScene) {
        currentScene->update(deltaTime);
    }
}

void SceneManager::render() {
#if DEBUG_MODE
    Debug::debugPushCheck = micros();
#endif 


    //render
    if (currentScene) {
        renderer.renderScene(currentScene);
    }



#if DEBUG_MODE    
    Debug::debugPushCheck = micros() - Debug::debugPushCheck;

    frameCalls++;
    if (millis() - statusCheckTime > 1000)
    {        
        //log_d("Free heap: %d/%d %d%", ESP.getFreeHeap(), ESP.getHeapSize(), 100*ESP.getFreeHeap()/ESP.getHeapSize());
        log_d("FPS: %d", frameCalls);
        log_d("PhysCallsPS: %d", physicsCalls);
        log_d("Push time: %dmcs", Debug::debugPushCheck);
        log_d("Render time: %dmcs", Debug::debugRenderCheck);
        log_d("Vertecies size: %d", currentScene->vertices.size());
        log_d("Polygons size: %d \n", currentScene->polygons.size());
        // log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

        statusCheckTime = millis();
        frameCalls = 0;
        physicsCalls = 0;
        Debug::debugRenderCheck = 0;
    }
#endif 
}