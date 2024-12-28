#ifndef SCENE_H
#define SCENE_H

// #include "lowPoly.h"
#include <vector>
// #include <selfGFX/renderer.h>


// #include "selfGFX/vector.h"
#include "render/selfGFX/Entity.h"
#include "settings.h"

class SceneManager; // Forward declaration

class Scene {
public:

    virtual ~Scene() {}
    virtual void update(uint32_t deltaTime) = 0;
    virtual void enter() = 0;
    virtual void exit() = 0;

    
    std::vector<Vector> vertices = std::vector<Vector>();
    std::vector<Polygon> polygons = std::vector<Polygon>();

    Vector lightDirection = Vector(0,-0.5,1); //todo in UnitVector

    
    float FOV = Settings::fov;


    
    
protected:

    SceneManager* sceneManager;
    friend class SceneManager;
    void setSceneManager(SceneManager* manager) { sceneManager = manager; }
  
};

#endif