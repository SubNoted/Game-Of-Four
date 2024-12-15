#ifndef SCENE_H
#define SCENE_H

#include "lowPoly.h"
#include <vector>

class SceneManager; // Forward declaration

class Scene {
public:

    virtual ~Scene() {}
    virtual void update(uint32_t deltaTime) = 0;
    virtual void render() = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;

    static TFT_eSPI* tft;

    static std::vector<Vector> vertecies;
    static std::vector<Polygon> polygons;
    
protected:


    SceneManager* sceneManager;

    friend class SceneManager;
    void setSceneManager(SceneManager* manager) { sceneManager = manager; }

    
    ////////////for all scenes///////////////
    static TFT_eSprite* canvas;

    //pointer to pointer lol
    static uint16_t** cnvsPtr;
    



    static bool READY_TO_RENDER;     
};

#endif