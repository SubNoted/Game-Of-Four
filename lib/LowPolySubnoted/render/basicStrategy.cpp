#include "basicStrategy.h"

void BasicRendererStrategy::renderScene(std::shared_ptr<Scene> scene, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) 
{
    for (int cnvsNum = 0; cnvsNum < SPLIT_SCREEN; cnvsNum++) 
    {
        canvas[cnvsNum].fillScreen(TFT_CYAN);
        for (uint8_t i = 0; i < scene->polygons.size(); i++) 
        {
            Vector verts[3] = {scene->vertices[scene->polygons[i].vertices[0]], 
                       scene->vertices[scene->polygons[i].vertices[1]], 
                       scene->vertices[scene->polygons[i].vertices[2]]};
    
            verts[0].toFOV_XY(scene->FOV);
            verts[1].toFOV_XY(scene->FOV);
            verts[2].toFOV_XY(scene->FOV);
            
            Vector normal = Vector::Normal(verts[0], verts[1], verts[2]);
            if (normal.z < 0) continue;

            uint16_t color = TFT_WHITE;
            float shade = normal.ScalarProd(scene->lightDirection)/3+0.5;
            color = canvas[cnvsNum].alphaBlend(shade*255, color, TFT_CYAN);

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
        tft.pushImageDMA(0, SCRN_HEIGHT/SPLIT_SCREEN*cnvsNum, SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN, cnvsPtr[cnvsNum]);
    }

}

void BasicRendererStrategy::renderPolygons(std::shared_ptr<Scene> scene, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) {
    
}