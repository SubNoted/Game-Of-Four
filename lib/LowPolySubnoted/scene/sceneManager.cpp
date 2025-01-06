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
    Debug::physicsCalls++;
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
    Debug::pushTime = micros();
#endif 


    //render
    if (currentScene) {
        renderer.renderScene(currentScene);
    }



#if DEBUG_MODE    
    Debug::pushTimeSum += micros() - Debug::pushTime;

    if (millis() - statusCheckTime > 1000)
    {        
        //log_d("Free heap: %d/%d %d%", ESP.getFreeHeap(), ESP.getHeapSize(), 100*ESP.getFreeHeap()/ESP.getHeapSize());
        log_d("FPS: %d", Debug::frameCalls);
        log_d("PhysCallsPS: %d", Debug::physicsCalls);
        log_d("Push time: %lumcs", Debug::pushTimeSum/Debug::frameCalls);
        // log_d("Render time: %dmcs", Debug::renderTimeSum/Debug::renderTimeCount);
        log_d("Render time: %dmcs", Debug::renderTimeSum/Debug::frameCalls);
        // log_d("Render calls: %d", Debug::renderTimeCount);
        log_d("Vertecies size: %d", currentScene->vertices.size());
        log_d("Polygons size: %d \n", currentScene->polygons.size());
        
        log_d("Memory info\n\tPSRAM - \tTotal: %u,\tUsed: %u,\tFree: %u,\tBiggest free block: %u\n\tInternal - \tTotal: %u,\tUsed: %u,\tFree: %u,\tBiggest free block: %u\n\n\n", 
            heap_caps_get_total_size(MALLOC_CAP_SPIRAM),
            heap_caps_get_total_size(MALLOC_CAP_SPIRAM)-heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
            heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
            heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM),
            heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
            heap_caps_get_total_size(MALLOC_CAP_INTERNAL)-heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
            heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
            heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));

        statusCheckTime = millis();
        Debug::frameCalls = 0;
        Debug::physicsCalls = 0;
        Debug::pushTimeSum = 0;
        Debug::renderTimeSum = 0;
        Debug::renderCallsCount = 0;
    }
#endif
}