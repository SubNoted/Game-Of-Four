#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "lowPoly.h"

class GraphicsRenderer {
public:

    GraphicsRenderer(TFT_eSPI* tft, TFT_eSprite* canvas, uint16_t** cnvsPtr);
    void renderScene(const std::vector<Polygon>& polygons, const std::vector<Vector>& vertices, 
                     const Vector& light, float FOV, uint16_t BG_COL);

private:
    TFT_eSPI* tft;
    TFT_eSprite* canvas;
    uint16_t** cnvsPtr;

    void renderPolygon(const Polygon& polygon, const std::vector<Vector>& vertices, 
                       const Vector& light, float FOV, uint16_t BG_COL, int cnvsNum);
};

#endif // GRAPHICS_RENDERER_H