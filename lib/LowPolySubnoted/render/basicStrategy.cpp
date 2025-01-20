#include "basicStrategy.h"

///////////////////* my extra (for TFT_eSPI (ripped of TFT_eSPI) ) /////////////

uint16_t alphaBlend(uint8_t alpha, uint16_t fgc, uint16_t bgc)
{
  // Split out and blend 5-bit red and blue channels
  uint32_t rxb = bgc & 0xF81F;
  rxb += ((fgc & 0xF81F) - rxb) * (alpha >> 2) >> 6;
  // Split out and blend 6-bit green channel
  uint32_t xgx = bgc & 0x07E0;
  xgx += ((fgc & 0x07E0) - xgx) * alpha >> 8;
  // Recombine channels
  return (rxb & 0xF81F) | (xgx & 0x07E0);
}

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

void pushImageTriangleToCanvas(int16_t x0,int16_t y0, int16_t x1,int16_t y1, int16_t x2,int16_t y2, \
                               uint8_t uvx0,uint8_t uvy0, uint8_t uvx1,uint8_t uvy1, uint8_t uvx2,uint8_t uvy2, \
                               uint8_t light, uint16_t* _img, uint8_t* data)
{
    if (data == nullptr) return;  
    
    int16_t a, b, y, x, last, S;
    uint8_t w0, w1, w2;
    uint8_t *ptro, *ptrs;

    uint16_t color;

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

    int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

    
    S = (dy12 * dx02 - dx12 * dy02);
    if (S == 0) return;

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
            w0 = (-dy12 * (x - x2) + dx12 * (y - y2))*255 / S;
            w1 = ( dy02 * (x - x2) - dx02 * (y - y2))*255 / S;
            w2 = 255 - w0 - w1;
            
            if (light == 255)
            {
                ptro = data + ((uint8_t(w0*uvx0/255 + w1*uvx1/255 + w2*uvx2/255) + uint8_t(w0*uvy0/255 + w1*uvy1/255 + w2*uvy2/255) * 256) << 1);
                ptrs = (uint8_t *)_img + ((x + y * SCRN_WIDTH) << 1);

                memcpy(ptrs, ptro, 2);
            }
            else
            {
                ptro = data + ((uint8_t(w0*uvx0/255 + w1*uvx1/255 + w2*uvx2/255) + uint8_t(w0*uvy0/255 + w1*uvy1/255 + w2*uvy2/255) * 256) << 1);
                color = ptro[0]<<8 | ptro[1];
                
                color = alphaBlend(light, color, TFT_BLUE);

                color = (color >> 8) | (color << 8);
                _img[(x + y * SCRN_WIDTH)] = color;
            }
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
            w0 = (-dy12 * (x - x2) + dx12 * (y - y2))*255 / S;
            w1 = ( dy02 * (x - x2) - dx02 * (y - y2))*255 / S;
            w2 = 1 - w0 - w1;
            
            if (light == 255)
            {
                ptro = data + ((uint8_t(w0*uvx0/255 + w1*uvx1/255 + w2*uvx2/255) + uint8_t(w0*uvy0/255 + w1*uvy1/255 + w2*uvy2/255) * 256) << 1);
                ptrs = (uint8_t *)_img + ((x + y * SCRN_WIDTH) << 1);

                memcpy(ptrs, ptro, 2);
            }
            else
            {
                ptro = data + ((uint8_t(w0*uvx0/255 + w1*uvx1/255 + w2*uvx2/255) + uint8_t(w0*uvy0/255 + w1*uvy1/255 + w2*uvy2/255) * 256) << 1);
                color = ptro[0]<<8 | ptro[1];
                
                color = alphaBlend(light, color, TFT_BLUE);

                color = (color >> 8) | (color << 8);
                _img[(x + y * SCRN_WIDTH)] = color;
            }
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
                float shade = normal.ScalarProd(lightDirection)/2+0.5; //todo optimize to unitvector
                
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
                    uint8_t(shade*255),
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