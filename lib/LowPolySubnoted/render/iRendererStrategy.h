#ifndef I_RENDER_STRATEGY_H
#define I_RENDER_STRATEGY_H


#include <TFT_eSPI.h> 
#include "selfGFX/polygon.h"
#include "scene/scene.h"

class IRendererStrategy {
public:
    virtual ~IRendererStrategy() = default;
    virtual void renderScene(std::shared_ptr<Scene> scene, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) = 0;
};

#endif // I_RENDER_STRATEGY_H