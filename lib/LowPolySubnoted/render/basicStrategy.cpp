#include "basicStrategy.h"

///////////////////* my extra (for TFT_eSPI (ripped of TFT_eSPI) ) /////////////

void  pushImageLine(int32_t x, int32_t y, int32_t w, uint16_t *_img, uint8_t *data)
{

    // Pointer within original image
    uint8_t *ptro = data + ((x + y * 256) << 1);
    // Pointer within sprite image
    uint8_t *ptrs = (uint8_t *)_img + ((x + y * SCRN_WIDTH) << 1);

    // while (h--)
    {
        memcpy(ptrs, ptro, (w<<1));
        ptro += 256<<1;
        ptrs += SCRN_WIDTH<<1;
    }
}

void pushImageTriangleToCanvas(int32_t x0,int32_t y0, int32_t x1,int32_t y1, int32_t x2,int32_t y2, \
                               uint8_t uvx0,uint8_t uvy0, uint8_t uvx1,uint8_t uvy1, uint8_t uvx2,uint8_t uvy2, \
                               uint16_t* _img, uint8_t* data)
{
    if (data == nullptr) return;  
    
    int32_t a, b, y, x, last;
    float w0, w1, w2, S;
    uint8_t *ptro, *ptrs;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        transpose(y0, y1); transpose(x0, x1);
        transpose(uvy0, uvy1); transpose(uvx0, uvx1);
    }
    if (y1 > y2) {
        transpose(y2, y1); transpose(x2, x1);
        transpose(uvy2, uvy1); transpose(uvx2, uvx1);
    }
    if (y0 > y1) {
        transpose(y0, y1); transpose(x0, x1);
        transpose(uvy0, uvy1); transpose(uvx0, uvx1);
    }

    S = ((y1 - y2) * (x0 - x2) + (x2 - x1) * (y0 - y2));

    if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if (x1 < a)      a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a)      a = x2;
        else if (x2 > b) b = x2;

        // drawFastHLine(a, y0, b - a + 1, color);
        // sprite.drawFastHLine(a, y0, b - a + 1, TFT_DARKGREY);

        ptro = data + ((x + y * 256) << 1);
        ptrs = (uint8_t *)_img + ((x + y * SCRN_WIDTH) << 1);

        memcpy(ptrs, ptro, 2);


        return;
    }

    int32_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if (y1 == y2) last = y1;  // Include y1 scanline
    else         last = y1 - 1; // Skip it

    for (y = y0; y <= last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;

        if (a > b) transpose(a, b);        
        // sprite.drawFastHLine(a, y, b - a + 1, TFT_DARKGREY);
        
        // pushImageLine(a, y, b - a + 1, _img, data);
        
        for (x = a; x <= b; x++)
        {
            // pushImageLine(x, y, 1, _img, data);

            w0 = ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) / S;
            w1 = ((y2 - y0) * (x - x2) + (x0 - x2) * (y - y2)) / S;
            w2 = 1 - w0 - w1;
            
            // ptro = data + ((x + y * 256) << 1);
            if (a==b) break;
            
            // ptro = data + ((uint8_t((uvx2-uvx0)*(x-minX)/(dX)) + uint8_t((uvy2-uvy0)*(y-y0)/(y2-y0)) * 256) << 1);
            ptro = data + ((uint8_t(w0*uvx0 + w1*uvx1 + w2*uvx2) + uint8_t(w0*uvy0 + w1*uvy1 + w2*uvy2) * 256) << 1);
            ptrs = (uint8_t *)_img + ((x + y * SCRN_WIDTH) << 1);

            memcpy(ptrs, ptro, 2);
        }
        
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;

        if (a > b) transpose(a, b);
        // sprite.drawFastHLine(a, y, b - a + 1, TFT_DARKGREY);

        // pushImageLine(a, y, b - a + 1, _img, data);

        for (x = a; x < b + 1; x++)
        {
            
            w0 = ((y1 - y2) * (x - x2) + (x2 - x1) * (y - y2)) / S;
            w1 = ((y2 - y0) * (x - x2) + (x0 - x2) * (y - y2)) / S;
            w2 = 1 - w0 - w1;
            // ptro = data + ((x + y * 256) << 1);
            // if (a==b) break;
            // ptro = data + ((uint8_t((uvx2-uvx0)*(x-minX)/(dX)) + uint8_t((uvy2-uvy0)*(y-y0)/(y2-y0)) * 256) << 1);
            ptro = data + ((uint8_t(w0*uvx0 + w1*uvx1 + w2*uvx2) + uint8_t(w0*uvy0 + w1*uvy1 + w2*uvy2) * 256) << 1);
            ptrs = (uint8_t *)_img + ((x + y * SCRN_WIDTH) << 1);

            memcpy(ptrs, ptro, 2);
        }

    }
}



void BasicRendererStrategy::renderScene(std::vector<Entity*>& entities, TFT_eSPI& tft, TFT_eSprite* canvas, uint16_t** cnvsPtr) 
{
    Debug::prerenderTimeSum += micros() - Debug::prerenderTime;

    for (int cnvsNum = 0; cnvsNum < SPLIT_SCREEN; cnvsNum++) 
    {
        Debug::renderTime = micros();
        canvas[cnvsNum].fillScreen(TFT_CYAN);

        //actual rendering
        for (uint8_t ent = 0; ent < entities.size(); ent++) //entities
        {
            for (uint8_t i = 0; i < entities[ent]->polySize; i++) //polygons
            {
                Vector verts[3] = { entities[ent]->vertices[entities[ent]->polygons[i].vertices[0]], 
                                    entities[ent]->vertices[entities[ent]->polygons[i].vertices[1]], 
                                    entities[ent]->vertices[entities[ent]->polygons[i].vertices[2]]};
                
                verts[0].toFOV_XY(FOV);
                verts[1].toFOV_XY(FOV);
                verts[2].toFOV_XY(FOV);
                
                Vector normal = Vector::Normal(verts[0], verts[1], verts[2]);
                
                if (normal.z < 0) continue;

                uint16_t color = TFT_WHITE;
                float shade = normal.ScalarProd(lightDirection)/3+0.5; //todo optimize to unitvector
                color = canvas[cnvsNum].alphaBlend(shade*255, color, TFT_CYAN);
                
                // canvas[cnvsNum].pushImage
                // canvas[cnvsNum].fillTriangle

                // pushImage(100,100, 100, 100, cnvsPtr[cnvsNum], cloudsTex);

                // canvas[cnvsNum].pushImage(0,0, 256, 256, cloudsTex);

                pushImageTriangleToCanvas(
                    verts[0].x, verts[0].y,
                    verts[1].x, verts[1].y,
                    verts[2].x, verts[2].y,
                    entities[ent]->polygons[i].uv[0][0],entities[ent]->polygons[i].uv[0][1],
                    entities[ent]->polygons[i].uv[1][0],entities[ent]->polygons[i].uv[1][1],
                    entities[ent]->polygons[i].uv[2][0],entities[ent]->polygons[i].uv[2][1],
                    cnvsPtr[cnvsNum],
                    entities[ent]->texture
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
        }

        Debug::renderTimeSum += micros() - Debug::renderTime;
        Debug::renderCallsCount++;
        tft.pushImageDMA(0, SCRN_HEIGHT/SPLIT_SCREEN*cnvsNum, SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN, cnvsPtr[cnvsNum]);
    }
}