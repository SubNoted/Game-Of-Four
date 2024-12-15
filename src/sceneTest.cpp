#include "sceneTest.h"
#include <displayInfo.h>

uint16_t BG_COL = Scene::tft->color565(104,144,195); //test color


Vector light = Vector(0,-0.5,1);
// UnitVector light = UnitVector(0,0,255);




float size = 50, x = 0, y = 0;
void Tscene::update(uint32_t deltaTime) 
{
    x = CENTR_X;
    y = sin((float)millis()*0.003)*0.5-0.9;
    
    READY_TO_RENDER = true;
}

void Tscene::render() 
{
    for (int cnvsNum = 0; cnvsNum < SPLIT_SCREEN; cnvsNum++) {
        canvas[cnvsNum].fillScreen(BG_COL);
        canvas[cnvsNum].fillCircle(x, y, size, TFT_RED);
        
        tft->pushImageDMA(0,SCREEN_HEIGHT/SPLIT_SCREEN*cnvsNum, SCREEN_WIDTH, SCREEN_HEIGHT/SPLIT_SCREEN, cnvsPtr[cnvsNum]);
    }
}


void Tscene::enter() {
    
    // circle.setColorDepth(16);
    // circle.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT/2);
    // circle.fillScreen(TFT_TRANSPARENT);
    // circle.setSwapBytes(true);
    
    canvas[0].fillScreen(TFT_BLUE * 0.5);
    canvas[1].fillScreen(TFT_BLUE * 0.5);
}

void Tscene::exit() {
    // Clean up menu resources
}


//////////////private
