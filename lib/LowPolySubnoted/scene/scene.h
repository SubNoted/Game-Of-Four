#ifndef SCENE_H
#define SCENE_H

#include "lowPoly.h"
#include <vector>

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

    
    ////////////for all scenes///////////////
    static TFT_eSprite* canvas;

    //pointer to pointer lol
    static uint16_t** cnvsPtr;
    
    static TFT_eSPI* tft;

    static const uint8_t SCREEN_HEIGHT = 240;
    static const uint8_t SCREEN_WIDTH = 240;
    static const uint8_t SPLIT_SCREEN = 2;

    static std::vector<Vector> vertecies;
    static std::vector<Vector> polygons;        
};

#endif