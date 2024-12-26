#include "lowPoly.h"

void LowPoly::init()
{
#if DEBUG_MODE
    log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    log_d("free heap: %d\n", ESP.getFreeHeap());
#endif

    tft.init();
    tft.initDMA();
	tft.setRotation(SCRN_ROTATION);
	//tft.fillScreen(tft.color565(255,220,220));
	//tft.fillScreen(BG_COL);

	tft.fillScreen(TFT_RED);
    //delay(300);
    tft.setSwapBytes(false);
    // Entity::initALL(&sprite, SCRN_WIDTH, SCRN_HEIGHT, &FOV, &last_FOV, &BG_COL);
    // Cube.init();
    

    // Cube.O.Equals(SCRN_WIDTH/2, -50, -160);
    // Cube.constA.z = 3;

    canvas[0].setColorDepth(16); 
    canvas[1].setColorDepth(16); 
	cnvsPtr[0] = (uint16_t*)canvas[0].createSprite(SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN);
	cnvsPtr[1] = (uint16_t*)canvas[1].createSprite(SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN);
	canvas[0].setSwapBytes(true);
	canvas[1].setSwapBytes(true);
    
    canvas[1].setViewport(0, -SCRN_HEIGHT/SPLIT_SCREEN, SCRN_WIDTH, SCRN_HEIGHT);

    
    SceneManager::init(canvas, cnvsPtr, &tft);
    
    tft.startWrite();
}