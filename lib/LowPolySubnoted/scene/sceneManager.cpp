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

std::vector<Vector> Scene::vertecies = std::vector<Vector>();
std::vector<Polygon> Scene::polygons = std::vector<Polygon>();

void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    if (currentScene) {
        Scene::vertecies.clear();
        currentScene->exit();
    }
    currentScene = std::move(newScene);

    Scene::vertecies.reserve(8);
    Scene::polygons.reserve(12);

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
    debugTimeStart = micros();
#endif 


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
        log_d("Push time: %dmcs", debugPushCheck);
        log_d("Vertecies size: %d", Scene::vertecies.size());
        log_d("Polygons size: %d \n", Scene::polygons.size());
        // log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

        statusCheckTime = millis();
        frameCalls = 0;
        physicsCalls = 0;
    }
#endif 
}