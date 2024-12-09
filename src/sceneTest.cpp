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
        canvas->fillScreen(TFT_RED);
        canvas->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2, TFT_GREEN);
        tft->pushImageDMA(0,0, SCREEN_WIDTH, SCREEN_HEIGHT/SPLIT_SCREEN, *cnvsPtr);
    }
    //delay(10);
    //canvas1.fillSprite(TFT_RED+10);
    //while (tft.dmaBusy());
    //if (millis() - frameTimeStart > 1000)
    {
        canvas1->fillScreen(TFT_RED);
        tft->pushImageDMA(0, SCREEN_HEIGHT/SPLIT_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT/SPLIT_SCREEN, *cnvsPtr1);
    }
}

void Tscene::enter() {
}

void Tscene::exit() {
    // Clean up menu resources
}


//////////////private
void Tscene::addVertex(Vector v)
{
    vertices.push_back(v);
}


void Tscene::clearVertices()
{
    vertices.clear();
}