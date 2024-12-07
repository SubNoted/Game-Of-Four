#ifndef SCENE_H
#define SCENE_H

#include "TFT_eSPI.h"

class SceneManager; // Forward declaration

class Scene {
public:

    virtual ~Scene() {}
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;

protected:
    SceneManager* sceneManager;

    friend class SceneManager;
    void setSceneManager(SceneManager* manager) { sceneManager = manager; }

    
    static TFT_eSprite* canvas;
    static TFT_eSprite* canvas1;

    //pointer to pointer lol
    static uint16_t** cnvsPtr;
    static uint16_t** cnvsPtr1;
    
    static TFT_eSPI* tft;

    static const uint8_t SCREEN_HEIGHT;
    static const uint8_t SCREEN_WIDTH;
    static const uint8_t SPLIT_SCREEN;
};

#endif