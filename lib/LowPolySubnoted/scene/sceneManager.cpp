#include "SceneManager.h"

void SceneManager::init(TFT_eSprite* canvas, TFT_eSprite* canvas1, uint16_t** cnvsPtr, uint16_t** cnvsPtr1, TFT_eSPI* tft)
{
    Scene::canvas = canvas;
    Scene::canvas1 = canvas1;
    Scene::cnvsPtr = cnvsPtr;
    Scene::cnvsPtr1 = cnvsPtr1;
    Scene::tft = tft;
    currentScene = nullptr;
}


void SceneManager::changeScene(std::unique_ptr<Scene> newScene) {
    if (currentScene) {
        currentScene->exit();
    }
    currentScene = std::move(newScene);
    currentScene->setSceneManager(this);
    currentScene->enter();
}

void SceneManager::update(float deltaTime) {
    if (currentScene) {
        currentScene->update(deltaTime);
    }
}

void SceneManager::render() {
    if (currentScene) {
        currentScene->render();
    }
}