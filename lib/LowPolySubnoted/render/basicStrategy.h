#ifndef BASIC_RENDER_STRATEGY
#define BASIC_RENDER_STRATEGY

#include "renderer.h"
#include "debug.h"

class BasicRendererStrategy : public IRendererStrategy {
public:
    void renderScene(std::shared_ptr<Scene> scene, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) override;
    void renderPolygons(std::shared_ptr<Scene> scene, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr); 
};

#endif // BASIC_RENDER_STRATEGY