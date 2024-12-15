#include "sceneTest.h"
#include <displayInfo.h>

uint16_t BG_COL = Scene::tft->color565(104,144,195); //test color


Vector light = Vector(0,-0.5,1);
// UnitVector light = UnitVector(0,0,255);



Entity cube;
float size = 100, x = CENTR_X, y = CENTR_Y;
float FOV = PI/2;

void Tscene::update(uint32_t deltaTime) 
{
    x = CENTR_X;
    y = sin((float)millis()*0.003)*0.5-0.9;
    
    // READY_TO_RENDER = true;
    
    //cube.rotate(Vector(0.002*deltaTime,0.002*deltaTime,0));
    cube.setRotation(Vector(0.002*millis(),0,y));
}

void Tscene::render() 
{
    for (int cnvsNum = 0; cnvsNum < SPLIT_SCREEN; cnvsNum++) {
        canvas[cnvsNum].fillScreen(BG_COL);
        // canvas[cnvsNum].fillCircle(x, y, size, TFT_RED);
        for (int i = 0; i < polygons.size(); i++) 
        {
            Vector verts[3] = {vertecies[polygons[i].vertices[0]], 
                vertecies[polygons[i].vertices[1]], 
                vertecies[polygons[i].vertices[2]]
                };
            verts[0].toFOV_XY(FOV);
            verts[1].toFOV_XY(FOV);
            verts[2].toFOV_XY(FOV);
                
            Vector normal = Vector::Normal(verts[0], verts[1], verts[2]);//todo optimize
            if (normal.z < 0) continue;

            uint16_t color = TFT_WHITE;

            float shade = normal.ScalarProd(light)/3+0.5;//todo optimize to unitvector
            color = canvas[cnvsNum].alphaBlend(shade*255,color, BG_COL);


            canvas[cnvsNum].fillTriangle(
                verts[0].x, verts[0].y,
                verts[1].x, verts[1].y,
                verts[2].x, verts[2].y,
                color
                );
            canvas[cnvsNum].drawTriangle(
                verts[0].x, verts[0].y,
                verts[1].x, verts[1].y,
                verts[2].x, verts[2].y,
                TFT_DARKGREY
                );
        }
        tft->pushImageDMA(0,SCRN_HEIGHT/SPLIT_SCREEN*cnvsNum, SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN, cnvsPtr[cnvsNum]);
    }
}


void Tscene::enter() {    
    canvas[0].fillScreen(TFT_BLUE * 0.5);
    canvas[1].fillScreen(TFT_BLUE * 0.5);

    cube.initCube(Vector(x, y, 100), Vector(size));
    //cube.setRotation(Vector(0,10,20));
}

void Tscene::exit() {
    // Clean up menu resources
}
