#include <Arduino.h>

#include <memory>

#include <SPI.h>
#include <TFT_eSPI.h> 

#include <lowPoly.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define CENTR_X SCREEN_WIDTH/2
#define CENTR_Y SCREEN_HEIGHT/2

#define SCREEN_ROTATION 0 //default: landscape
#define SPLIT_SCREEN 2

float FOV = PI/2, last_FOV = 0;


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);
TFT_eSprite canvas1 = TFT_eSprite(&tft);
uint16_t* cnvsPtr = nullptr;
uint16_t* cnvsPtr1 = nullptr;


uint16_t BG_COL = tft.color565(194,144,195); //test color

/////////scenes////////////
#include "sceneTest.h"
#include <bits/unique_ptr.h>

/*static*/ SceneManager sceneManager;

////////tools/////////
unsigned long statusCheckTime = 0, fixedTime = 0, clearTime = 0, last4deltaTime = 0;
//unsigned long 
float deltaTime = 0;
String str = "lol";
#define MAX_CONSL 6
#define isDEBUG_MODE true

uint8_t frames = 0, physicsCalls = 0, i = 0;
float normalSin(float x)//from 0 to 1 on PI //todo to physics engine
{
    return pow(sin(x/2), 2);
}

void core0(void * pvParameters);

////////////////SETUP/////////////////////////////////
void setup() 
{
    randomSeed(analogRead(23));
	
    log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    log_d("free heap: %d\n", ESP.getFreeHeap());

    if(psramFound())//todo find one
    {
        log_d("PSRAM Detected\n");
    }

    ////////////init////////////////////

	tft.init();
    tft.initDMA();
	tft.setRotation(SCREEN_ROTATION);
	//tft.fillScreen(tft.color565(255,220,220));
	//tft.fillScreen(BG_COL);
	tft.fillScreen(TFT_RED);
    tft.setSwapBytes(false);

    // Entity::initALL(&sprite, SCREEN_WIDTH, SCREEN_HEIGHT, &FOV, &last_FOV, &BG_COL);
    // Cube.init();
    
    last4deltaTime = millis();

    // Cube.O.Equals(SCREEN_WIDTH/2, -50, -160);
    // Cube.constA.z = 3;

    canvas.setColorDepth(16); 
    canvas1.setColorDepth(16); 
	cnvsPtr = (uint16_t*)canvas.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT/SPLIT_SCREEN);
	cnvsPtr1 = (uint16_t*)canvas1.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT/SPLIT_SCREEN);
    canvas.fillScreen(TFT_RED);
    canvas1.fillScreen(TFT_RED);
	canvas.setSwapBytes(true);
	canvas1.setSwapBytes(true);
    
    canvas1.setViewport(0, -SCREEN_HEIGHT/SPLIT_SCREEN, SCREEN_WIDTH, SCREEN_HEIGHT);

    xTaskCreatePinnedToCore(core0, "Physics", 10000, NULL, 1, NULL,  0); 
    delay(500);

    //startscene
    sceneManager.init(&canvas, &canvas1, &cnvsPtr, &cnvsPtr1, &tft);
    sceneManager.changeScene(std::unique_ptr<Tscene>(new Tscene()));
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
    // cube.pushToSprite(&canvas, CENTR_X,CENTR_Y, TFT_BLACK);
    // cube.deleteSprite();

    // Cube.O.Plus((CENTR_X - Cube.O.x)*deltaTime/200, (CENTR_Y -  20 - Cube.O.y)*deltaTime/400);
    // Cube.setColor(tft.color565(170 + sin(fixedTime * PI/200)*85, 170 + sin(fixedTime * PI/200 - PI*2/3)*85, 170 + sin(fixedTime * PI/200 + PI*2/3)*85));
    // Cube.Angle.Equals(fixedTime*PI/240,fixedTime*PI/200, fixedTime*PI/150);
    // Cube.drawCube(40);

    //canvas.fillTriangle(CENTR_X - 100, CENTR_Y - 100, CENTR_X + 100, CENTR_Y - 100, CENTR_X + 100, CENTR_Y + 100, TFT_GREEN);
    
}

unsigned long debugTimeStart = 0, debugPushCheck = 0, debugRenderCheck = 0; 
unsigned long frameTimeStart = 0;
void loop() 
{
    {
        fixedTime = millis()*60/1000; //float which every integer is 1/60 of second
        last_FOV = FOV;
        deltaTime = millis() - last4deltaTime;
        if (deltaTime > 100)
            deltaTime = 100;
        last4deltaTime = millis();


        //render
        
        debugTimeStart = micros();
        sceneManager.render();
        debugPushCheck = micros() - debugTimeStart;
        //Entity::processAllEntities(deltaTime);

    /////debug

        frames++;
        if (millis() - statusCheckTime > 1000)
        {        
            //log_d("Free heap: %d/%d %d%", ESP.getFreeHeap(), ESP.getHeapSize(), 100*ESP.getFreeHeap()/ESP.getHeapSize());
            log_d("FPS: %d\n", frames);
            log_d("PhysCallsPS: %d\n", physicsCalls);
            log_d("Push time: %dms\n", debugPushCheck);
            // log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

            statusCheckTime = millis();
            frames = 0;
            physicsCalls = 0;
        }
    }
}

void core0(void * pvParameters){
    while(1){
        physicsCalls++;
        sceneManager.update(deltaTime);
        delay(1000);
        log_d("00");
    }
}