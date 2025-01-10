#ifndef BASIC_RENDER_STRATEGY
#define BASIC_RENDER_STRATEGY

#include "renderer.h"
#include "debug.h"

class BasicRendererStrategy : public IRendererStrategy {
public:
    void renderScene(std::vector<Entity*>& entities, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) override;
    void renderPolygons(std::vector<Entity*>& entities, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr); 

    Vector lightDirection;
    float FOV = Settings::fov;
};

#endif // BASIC_RENDER_STRATEGY