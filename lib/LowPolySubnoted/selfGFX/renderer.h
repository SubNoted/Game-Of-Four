#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "lowPoly.h"
#include "scene/settings.h"

class IRendererStrategy {
public:
    virtual ~IRendererStrategy() = default;
    virtual void renderScene(TFT_eSprite* canvas, uint16_t** cnvsPtr, TFT_eSPI* tft,
                             const std::vector<Polygon>& polygons, const std::vector<Vector>& vertices,
                             const Vector& light, float FOV, uint16_t BG_COL) = 0;
};

class BasicRendererStrategy : public IRendererStrategy {
public:
    void renderScene(TFT_eSprite* canvas, uint16_t** cnvsPtr, TFT_eSPI* tft,
                     const std::vector<Polygon>& polygons, const std::vector<Vector>& vertices,
                     const Vector& light, float FOV, uint16_t BG_COL) override {
        // Implement basic rendering logic here
    }
    void renderPolygon(const Polygon& polygon, const std::vector<Vector>& vertices, 
                       const Vector& light, float FOV, uint16_t BG_COL, int cnvsNum);
};


class GraphicsRenderer {
public:



    GraphicsRenderer(TFT_eSPI* tft, TFT_eSprite* canvas, uint16_t** cnvsPtr, std::unique_ptr<IRendererStrategy> strategy);
    // void renderScene(const std::vector<Polygon>& polygons, const std::vector<Vector>& vertices, 
    //                  const Vector& light, float FOV, uint16_t BG_COL);
                       
    void renderScene(const std::vector<Polygon>& polygons, const std::vector<Vector>& vertices,
                     const Vector& light, float FOV, uint16_t BG_COL) {
        strategy->renderScene(canvas, cnvsPtr, tft, polygons, vertices, light, FOV, BG_COL);
    }
    
    void setStrategy(std::unique_ptr<IRendererStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

private:
    TFT_eSPI* tft;
    TFT_eSprite* canvas;
    uint16_t** cnvsPtr;

    std::unique_ptr<IRendererStrategy> strategy;

};

#endif // GRAPHICS_RENDERER_H