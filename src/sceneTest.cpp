#include "sceneTest.h"

// uint16_t BG_COL = Scene::tft->color565(104,144,195); //test color

// UnitVector light = UnitVector(0,0,255);


float normalSin(float x)//from 0 to 1 on PI //todo to physics engine
{
    return pow(sin(x/2), 2);
}

Entity cube;
float size = 100, x = CENTR_X, y = CENTR_Y + 50;
float input_x = 0, input_y = 0;

void Tscene::update(uint32_t deltaTime) 
{
    // x = CENTR_X;
    // y = sin((float)millis()*0.003)*0.5-0.9;
    
    // // READY_TO_RENDER = true;
    
#ifdef ESP32_ON
    input_x = (float)(map(analogRead(34), 765, 3050, 0, 1000)-500)/1000;
    input_y = (float)(map(analogRead(4), 695, 3000, 0, 1000)-500)/1000;
#elif defined(ESP32_S3_ON)
    input_x = (float)(map(analogRead(5), 765, 3050, 0, 1000)-500)/1000;
    input_y = (float)(map(analogRead(4), 695, 3000, 0, 1000)-500)/1000;
#endif

    if (abs(input_x) > 0.045 || abs(input_y) > 0.045)
        cube.rotate(Vector(0,-0.005*deltaTime*input_x,-0.005*deltaTime*input_y));
    // cube.setRotation(Vector(0.002*millis(),0,y));
}

// void Tscene::render() 
// {
    // for (int cnvsNum = 0; cnvsNum < SPLIT_SCREEN; cnvsNum++) {
    //     canvas[cnvsNum].fillScreen(BG_COL);
    //     // canvas[cnvsNum].fillCircle(x, y, size, TFT_RED);
    //     for (int i = 0; i < polygons.size(); i++) 
    //     {
    //         Vector verts[3] = {vertecies[polygons[i].vertices[0]], 
    //             vertecies[polygons[i].vertices[1]], 
    //             vertecies[polygons[i].vertices[2]]
    //             };
    //         verts[0].toFOV_XY(FOV);
    //         verts[1].toFOV_XY(FOV);
    //         verts[2].toFOV_XY(FOV);
                
    //         Vector normal = Vector::Normal(verts[0], verts[1], verts[2]);//todo optimize
    //         if (normal.z < 0) continue;

    //         uint16_t color = TFT_WHITE;

    //         float shade = normal.ScalarProd(light)/3+0.5;//todo optimize to unitvector
    //         color = canvas[cnvsNum].alphaBlend(shade*255,color, BG_COL);


    //         canvas[cnvsNum].fillTriangle(
    //             verts[0].x, verts[0].y,
    //             verts[1].x, verts[1].y,
    //             verts[2].x, verts[2].y,
    //             color
    //             );
    //         canvas[cnvsNum].drawTriangle(
    //             verts[0].x, verts[0].y,
    //             verts[1].x, verts[1].y,
    //             verts[2].x, verts[2].y,
    //             TFT_DARKGREY
    //             );
    //     }
    //     tft->pushImageDMA(0,SCRN_HEIGHT/SPLIT_SCREEN*cnvsNum, SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN, cnvsPtr[cnvsNum]);
    // }
// }


void Tscene::enter() {
    
    // canvas[0].fillScreen(TFT_BLUE * 0.5);
    // canvas[1].fillScreen(TFT_BLUE * 0.5);

    cube.init(entities);
    cube.createCube(Vector(x, y, 100), Vector(size));
    //cube.setRotation(Vector(0,10,20));
}

void Tscene::exit() {
    // Clean up menu resources
}
