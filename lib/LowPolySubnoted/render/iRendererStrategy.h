#ifndef I_RENDER_STRATEGY_H
#define I_RENDER_STRATEGY_H


#include <TFT_eSPI.h> 
#include <vector>

#include "selfGFX/entity.h"

class IRendererStrategy {
public:
    virtual ~IRendererStrategy() = default;
    virtual void renderScene(std::vector<Entity*>& entities, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) = 0;
};

#endif // I_RENDER_STRATEGY_H