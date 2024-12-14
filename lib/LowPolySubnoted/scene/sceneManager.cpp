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
    if (currentScene) {
        physicsCalls++;
        currentScene->update(deltaTime);
    }
}

void SceneManager::render() {
    
    // fixedTime = millis()*60/1000; //float which every integer is 1/60 of second
    // deltaTime = millis() - last4deltaTime;

    
    // if (deltaTime > 100)
    //     deltaTime = 100;
    // last4deltaTime = millis();

    if (currentScene) {
        currentScene->render();
    }

    
}