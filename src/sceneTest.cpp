#include "sceneTest.h"

#include <blazeModel/blazeModel.h>

// #include <cloudsTex.h>

// uint16_t BG_COL = Scene::tft->color565(104,144,195); //test color

// UnitVector light = UnitVector(0,0,255);


float normalSin(float x)//from 0 to 1 on PI //todo to physics engine
{
    return pow(sin(x/2), 2);
}

Entity cube;
float size = 150, x = CENTR_X, y = CENTR_Y + 50;
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

void Tscene::enter() {

    cube.init(entities);
    cube.createModel(blazeModel_PARAMETRS);
    cube.Size = 25;
    cube.O.Equals(120,270,60);
    cube.setRotation(Vector(PI,0,0));

    // cube.createCube(Vector(x, y, 100), Vector(size));

    //texture
    // cube.texture = cloudsTex; //alloc ram memory for texture
    // cube.textureHeight = 256;
    // cube.textureWidth = 256;

}

void Tscene::exit() {
    // Clean up menu resources
}
