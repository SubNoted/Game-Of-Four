#include "renderer.h"

GraphicsRenderer::GraphicsRenderer(TFT_eSPI* tft, TFT_eSprite* canvas, uint16_t** cnvsPtr)
    : tft(tft), canvas(canvas), cnvsPtr(cnvsPtr) {}


void GraphicsRenderer::renderScene(const std::vector<Polygon>& polygons, const std::vector<Vector>& vertices, 
                                   const Vector& light, float FOV, uint16_t BG_COL) {
    for (int cnvsNum = 0; cnvsNum < SPLIT_SCREEN; cnvsNum++) {
        canvas[cnvsNum].fillScreen(BG_COL);
        for (const auto& polygon : polygons) {
            renderPolygon(polygon, vertices, light, FOV, BG_COL, cnvsNum);
        }
        tft->pushImageDMA(0, SCRN_HEIGHT/SPLIT_SCREEN*cnvsNum, SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN, cnvsPtr[cnvsNum]);
    }
}

void GraphicsRenderer::renderPolygon(const Polygon& polygon, const std::vector<Vector>& vertices, 
                                     const Vector& light, float FOV, uint16_t BG_COL, int cnvsNum) {
    Vector verts[3] = {vertices[polygon.vertices[0]], 
                       vertices[polygon.vertices[1]], 
                       vertices[polygon.vertices[2]]};
    
    for (auto& vert : verts) {
        vert.toFOV_XY(FOV);
    }
    
    Vector normal = Vector::Normal(verts[0], verts[1], verts[2]);
    if (normal.z < 0) return;

    uint16_t color = TFT_WHITE;
    float shade = normal.ScalarProd(light)/3+0.5;
    color = canvas[cnvsNum].alphaBlend(shade*255, color, BG_COL);

    canvas[cnvsNum].fillTriangle(
        verts[0].x, verts[0].y,
        verts[1].x, verts[1].y,
        verts[2].x, verts[2].y,
        color
    );
#if DEBUG_MODE
    canvas[cnvsNum].drawTriangle(
        verts[0].x, verts[0].y,
        verts[1].x, verts[1].y,
        verts[2].x, verts[2].y,
        TFT_DARKGREY
    );
#endif
}