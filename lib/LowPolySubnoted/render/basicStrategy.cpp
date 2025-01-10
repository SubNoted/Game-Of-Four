#include "basicStrategy.h"

///////////////////* my extra (for TFT_eSPI) /////////////
// Clipping macro for pushImage
#define PI_CLIP                                        \
                                                       \
  int32_t dx = 0;                                      \
  int32_t dy = 0;                                      \
  int32_t dw = w;                                      \
  int32_t dh = h;                                      \
                                                       \
  if (dw < 1 || dh < 1) return;

void pushImageTriangleToSprite(int32_t x1,int32_t y1, int32_t x2,int32_t y2, int32_t x3,int32_t y3, uint32_t color)
{

}

void  pushImage(int32_t x, int32_t y, int32_t w, int32_t h, uint16_t *_img, uint16_t *data)
{
    if (data == nullptr) return;

    PI_CLIP;    

    // Pointer within original image
    uint8_t *ptro = (uint8_t *)data + ((dx + dy * w) << 1);
    // Pointer within sprite image
    uint8_t *ptrs = (uint8_t *)_img + ((x + y * SCRN_WIDTH) << 1);

    while (dh--)
    {
    memcpy(ptrs, ptro, dw<<1);
    ptro += w << 1;
    ptrs += SCRN_WIDTH << 1;
    }
}

// void fillTriangle ( int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
// {
//   int32_t a, b, y, last;

//   // Sort coordinates by Y order (y2 >= y1 >= y0)
//   if (y0 > y1) {
//     transpose(y0, y1); transpose(x0, x1);
//   }
//   if (y1 > y2) {
//     transpose(y2, y1); transpose(x2, x1);
//   }
//   if (y0 > y1) {
//     transpose(y0, y1); transpose(x0, x1);
//   }

//   if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
//     a = b = x0;
//     if (x1 < a)      a = x1;
//     else if (x1 > b) b = x1;
//     if (x2 < a)      a = x2;
//     else if (x2 > b) b = x2;
//     drawFastHLine(a, y0, b - a + 1, color);
//     return;
//   }

//   //begin_tft_write();          // Sprite class can use this function, avoiding begin_tft_write()
//   inTransaction = true;

//   int32_t
//   dx01 = x1 - x0,
//   dy01 = y1 - y0,
//   dx02 = x2 - x0,
//   dy02 = y2 - y0,
//   dx12 = x2 - x1,
//   dy12 = y2 - y1,
//   sa   = 0,
//   sb   = 0;

//   // For upper part of triangle, find scanline crossings for segments
//   // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
//   // is included here (and second loop will be skipped, avoiding a /0
//   // error there), otherwise scanline y1 is skipped here and handled
//   // in the second loop...which also avoids a /0 error here if y0=y1
//   // (flat-topped triangle).
//   if (y1 == y2) last = y1;  // Include y1 scanline
//   else         last = y1 - 1; // Skip it

//   for (y = y0; y <= last; y++) {
//     a   = x0 + sa / dy01;
//     b   = x0 + sb / dy02;
//     sa += dx01;
//     sb += dx02;

//     if (a > b) transpose(a, b);
//     drawFastHLine(a, y, b - a + 1, color);
//   }

//   // For lower part of triangle, find scanline crossings for segments
//   // 0-2 and 1-2.  This loop is skipped if y1=y2.
//   sa = dx12 * (y - y1);
//   sb = dx02 * (y - y0);
//   for (; y <= y2; y++) {
//     a   = x1 + sa / dy12;
//     b   = x0 + sb / dy02;
//     sa += dx12;
//     sb += dx02;

//     if (a > b) transpose(a, b);
//     drawFastHLine(a, y, b - a + 1, color);
//   }

//   inTransaction = lockTransaction;
//   end_tft_write();              // Does nothing if Sprite class uses this function
// }


void BasicRendererStrategy::renderScene(std::shared_ptr<Scene> scene, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) 
{
    Debug::prerenderTimeSum += micros() - Debug::prerenderTime;
    for (int cnvsNum = 0; cnvsNum < SPLIT_SCREEN; cnvsNum++) 
    {
        Debug::renderTime = micros();
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
            
            // canvas[cnvsNum].pushImage
            // canvas[cnvsNum].fillTriangle 

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

        Debug::renderTimeSum += micros() - Debug::renderTime;
        Debug::renderCallsCount++;
        tft.pushImageDMA(0, SCRN_HEIGHT/SPLIT_SCREEN*cnvsNum, SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN, cnvsPtr[cnvsNum]);
    }

}

void BasicRendererStrategy::renderPolygons(std::shared_ptr<Scene> scene, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) {
    
}