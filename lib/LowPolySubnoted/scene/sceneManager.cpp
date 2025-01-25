#include "SceneManager.h"
#include "esp_task_wdt.h"

void updatePhysics(void * pvParameter) 
{
#if DEBUG_MODE
    Debug::physicsCalls++;
#endif
    SceneManager* sceneManager = (SceneManager*)pvParameter;

    uint32_t deltaTime, last4deltaTime = millis();

    for (;;) 
    {
        deltaTime = millis() - last4deltaTime;
        if (deltaTime > 100)
            deltaTime = 100;
        last4deltaTime = millis();

        if (sceneManager->currentScene) {
            sceneManager->currentScene->update(deltaTime);
        }
        vTaskDelay(1);
    }
}

void updateBuffer(void * pvParameter) 
{
    SceneManager* sceneManager = (SceneManager*)pvParameter;
    for (;;) 
    {
        for (uint16_t i = 0; i < sceneManager->currentScene->entities.size(); i++) 
        {
            // currentScene->entities
        }
        vTaskDelay(1);
    }   
}

void log_func(void * pvParameter) 
{
    for (;;) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        log_d("FPS: %d", Debug::frameCalls);
        log_d("PhysCallsPS: %d", Debug::physicsCalls);

        if (Debug::frameCalls > 0) 
        {
            log_d("Push time: %lumcs", Debug::pushTimeSum/Debug::frameCalls);
            // log_d("Render time: %dmcs", Debug::renderTimeSum/Debug::renderTimeCount);
            log_d("PreRender time: %dmcs", Debug::prerenderTimeSum/Debug::frameCalls);
            log_d("Render time: %dmcs", Debug::renderTimeSum/Debug::frameCalls);
        } 
        // log_d("Render calls: %d", Debug::renderTimeCount);
        
        log_d("Memory info\n\tPSRAM - \tTotal: %u,\tUsed: %u,\tFree: %u,\tBiggest free block: %u\n\tInternal - \tTotal: %u,\tUsed: %u,\tFree: %u,\tBiggest free block: %u\n\n\n", 
            heap_caps_get_total_size(MALLOC_CAP_SPIRAM),
            heap_caps_get_total_size(MALLOC_CAP_SPIRAM)-heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
            heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
            heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM),
            heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
            heap_caps_get_total_size(MALLOC_CAP_INTERNAL)-heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
            heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
            heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL)
        );
        Debug::frameCalls = 0;
        Debug::physicsCalls = 0;
        Debug::pushTimeSum = 0;
        Debug::renderTimeSum = 0;
        Debug::prerenderTimeSum = 0;
        Debug::renderCallsCount = 0;
        // esp_task_wdt_reset();
    }
}

void SceneManager::initRenderer()
{
    renderer.init();
    renderer.setStrategy(std::unique_ptr<IRendererStrategy>(new BasicRendererStrategy()));

    xTaskCreatePinnedToCore(updatePhysics, "updatePhysics", 2048, (this), 5, &updatePhysicsTaskHandle, 0);
    // xTaskCreatePinnedToCore(updateBuffer, "updateBuffer", 2048, (this), 4, &updatePhysicsTaskHandle, 0);
#if DEBUG_MODE
    xTaskCreatePinnedToCore(log_func, "log_func", 2048, NULL, 5, NULL, 0);
#endif 
}

void SceneManager::changeScene(std::shared_ptr<Scene> newScene) {
    if (currentScene) {
        currentScene->entities.clear();
        currentScene->exit();
    }
    currentScene = std::move(newScene);

    currentScene->entities.reserve(1);

    currentScene->setSceneManager(this);
    currentScene->enter();

    if (updateBufferTaskHandle != NULL)
    {
        vTaskDelete(updateBufferTaskHandle);
        updateBufferTaskHandle = NULL;
    }
    
}


void SceneManager::render() {
#if DEBUG_MODE
    Debug::pushTime = micros();
#endif 

    //render
    if (currentScene) {
        renderer.renderScene(currentScene->entities);
    }

#if DEBUG_MODE    
    Debug::pushTimeSum += micros() - Debug::pushTime;
#endif
}