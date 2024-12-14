#include "sceneTest.h"

void Tscene::update(float deltaTime) 
{
    int a = 0;
}

void Tscene::render() 
{
    
    //canvas.pushSprite(0, 0);
    //while (tft.dmaBusy());
    //if (millis() - debugTimeStart > 1000)
    {
        //canvas->fillScreen(TFT_RED);
        canvas[0].fillScreen(TFT_GREEN);
        tft->pushImageDMA(0,0, SCREEN_WIDTH, SCREEN_HEIGHT/SPLIT_SCREEN, cnvsPtr[0]);
    }
    //delay(10);
    //canvas1.fillSprite(TFT_RED+10);
    //while (tft.dmaBusy());
    //if (millis() - frameTimeStart > 1000)
    {
        canvas[1].fillScreen(TFT_ORANGE);
        tft->pushImageDMA(0, SCREEN_HEIGHT/SPLIT_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT/SPLIT_SCREEN, cnvsPtr[1]);
    }
    //log_d("render\n");
}

void Tscene::enter() {
}

void Tscene::exit() {
    // Clean up menu resources
}


//////////////private
