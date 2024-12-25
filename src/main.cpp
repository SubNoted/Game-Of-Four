#include <Arduino.h>

#include <memory>
#include "esp_task_wdt.h"

#include <SPI.h>
#include <TFT_eSPI.h> 

#include <lowPoly.h>


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas[2] = {TFT_eSprite(&tft), TFT_eSprite(&tft)};
uint16_t* cnvsPtr[2];


/////////scenes////////////
#include "sceneTest.h"
#include <bits/unique_ptr.h>

SceneManager sceneManager;

float normalSin(float x)//from 0 to 1 on PI //todo to physics engine
{
    return pow(sin(x/2), 2);
}

void core0(void * pvParameters);

////////////////SETUP/////////////////////////////////
void setup() 
{
    pinMode(12, ANALOG);

    pinMode(34, INPUT_PULLDOWN); //vertical (3000 - 650)
    pinMode(4, INPUT_PULLDOWN); //horizontal (3050 - 720)
    pinMode(32, PULLDOWN);
    randomSeed(analogRead(12));

	
    log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    log_d("free heap: %d\n", ESP.getFreeHeap());

    if(psramFound())//todo find one
    {
        log_d("PSRAM Detected\n");
    }

    ////////////init////////////////////

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

    delay(500);

    //startscene
    sceneManager.init(canvas, cnvsPtr, &tft);
    sceneManager.changeScene(std::unique_ptr<Tscene>(new Tscene()));
    
    
    xTaskCreatePinnedToCore(core0, "Physics", 10000, NULL, tskIDLE_PRIORITY , NULL,  0); 

    tft.startWrite();
}

void drawFrame()
{
	//drawTxt(40 + sin((float)t/10)*20, 60 + cos((float)t/8)*20, /*encCounter*/num%360, 1, str);
	//drawTxt(110, 120, 0, 4, (String)num);
	
	//drawCircle(120 + 100*sin((float)t*PI/180), 120 - 100*cos((float)t*PI/180), 17, TFT_RED);
	//delay(20);
	//drawCircle(120 + 100*sin((float)t*PI/180), 120 - 100*cos((float)t*PI/180), 17, BG_COL);

    // cube.setColorDepth(8);
	// cube.createSprite(75*sqrt(3), 75*sqrt(3));
    // cube.fillSprite(TFT_BLACK);
    // drawCube(Vector(CENTR_X,CENTR_Y, sin(float(t-1)/5)*(20)), 75, Vector((t-1)*PI/240, (t-1)*PI/200, (t-1)*PI/150), BG_COL);//t*PI/45
    // drawCube(Vector(CENTR_X,CENTR_Y, sin(float(t)/5)*(20)), 75, Vector(t*PI/240, t*PI/200, t*PI/150), TFT_WHITE);//t*PI/45
    // cube.pushToSprite(&canvas[0], CENTR_X,CENTR_Y, TFT_BLACK);
    // cube.deleteSprite();

    // Cube.O.Plus((CENTR_X - Cube.O.x)*deltaTime/200, (CENTR_Y -  20 - Cube.O.y)*deltaTime/400);
    // Cube.setColor(tft.color565(170 + sin(fixedTime * PI/200)*85, 170 + sin(fixedTime * PI/200 - PI*2/3)*85, 170 + sin(fixedTime * PI/200 + PI*2/3)*85));
    // Cube.Angle.Equals(fixedTime*PI/240,fixedTime*PI/200, fixedTime*PI/150);
    // Cube.drawCube(40);

    //canvas.fillTriangle(CENTR_X - 100, CENTR_Y - 100, CENTR_X + 100, CENTR_Y - 100, CENTR_X + 100, CENTR_Y + 100, TFT_GREEN);
    
}

void loop() 
{
    //last_FOV = FOV;
    //render
    
    sceneManager.render(); //call of this func = +~2mcs

    //canvas[0].fillScreen(TFT_GREEN);
    //tft.pushImageDMA(200,200, SCRN_WIDTH, SCRN_HEIGHT/SPLIT_SCREEN, cnvsPtr[0]);

    //canvas[0].pushSprite(10,10);

    //log_d("ADC %d", analogRead(4));
    //Entity::processAllEntities(deltaTime);
}

void core0(void * pvParameters){
    esp_task_wdt_add(nullptr);
    for (;;) {
        esp_task_wdt_reset();
        sceneManager.update();
    }
}