#include "renderer.h"

void GraphicsRenderer::init()
{
    tft.init();
    tft.initDMA();
	tft.setRotation(SCRN_ROTATION);

	tft.fillScreen(TFT_RED);
    tft.setSwapBytes(false);

    canvas[0].setColorDepth(16); 
    canvas[1].setColorDepth(16); 
	cnvsPtr[0] = (uint16_t*)canvas[0].createSprite(SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN);
	cnvsPtr[1] = (uint16_t*)canvas[1].createSprite(SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN);
	canvas[0].setSwapBytes(true);
	canvas[1].setSwapBytes(true);
    canvas[1].setViewport(0, -SCRN_HEIGHT/SPLIT_SCREEN, SCRN_WIDTH, SCRN_HEIGHT);
    
    tft.startWrite();
    
}

void GraphicsRenderer::renderScene(std::shared_ptr<Scene> scene)
{
    strategy->renderScene(scene, tft, canvas, cnvsPtr);    
}
