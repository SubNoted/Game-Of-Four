#include "renderer.h"
#include "debug.h"

void GraphicsRenderer::init()
{
    tft.init();
    tft.initDMA();
	tft.setRotation(SCRN_ROTATION);

	tft.fillScreen(TFT_RED);
    tft.setSwapBytes(false);

    for (int8_t i = 0; i < SPLIT_SCREEN; i++)
    {
        canvas[i].setColorDepth(16);
        cnvsPtr[i] = (uint16_t*)canvas[i].createSprite(SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN);
        canvas[i].setSwapBytes(true);
        canvas[i].setViewport(0, -SCRN_HEIGHT/SPLIT_SCREEN*i, SCRN_WIDTH, SCRN_HEIGHT);
    }
    
    tft.startWrite();
    
}

void GraphicsRenderer::renderScene(std::shared_ptr<Scene> scene)
{
    if (tft.dmaBusy())
        return;
    
    Debug::frameCalls++;
    strategy->renderScene(scene, tft, canvas, cnvsPtr);
}
