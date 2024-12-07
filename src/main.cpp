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

float FOV = PI/2, last_FOV = 0;


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);
TFT_eSprite canvas1 = TFT_eSprite(&tft);
uint16_t* cnvsPnr = nullptr;
uint16_t* cnvsPnr1 = nullptr;


uint16_t BG_COL = tft.color565(194,144,195); //test color

////////tools/////////
unsigned long framecheck = 0, fixedTime = 0, clearTime = 0, last4deltaTime = 0;
float deltatime = 0;
String str = "lol";
#define MAX_CONSL 6
#define isDEBUG_MODE true

uint8_t f = 0, tps = 0, i = 0;
float normalSin(float x)//from 0 to 1 on PI //todo to physics engine
{
    return pow(sin(x/2), 2);
}

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
	tft.fillScreen(TFT_WHITE);
    tft.setSwapBytes(true);

    // Entity::initALL(&sprite, SCREEN_WIDTH, SCREEN_HEIGHT, &FOV, &last_FOV, &BG_COL);
    // Cube.init();
    
    last4deltaTime = millis();

    // Cube.O.Equals(SCREEN_WIDTH/2, -50, -160);
    // Cube.constA.z = 3;

    canvas.setColorDepth(16); 
    canvas1.setColorDepth(16); 
	cnvsPnr = (uint16_t*)canvas.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT-20);
	cnvsPnr1 = (uint16_t*)canvas1.createSprite(SCREEN_WIDTH, 20);
    canvas.fillScreen(TFT_BLACK);
	canvas.setSwapBytes(true);
	canvas1.setSwapBytes(true);

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
    // cube.pushToSprite(&canvas, CENTR_X,CENTR_Y, TFT_BLACK);
    // cube.deleteSprite();

    // Cube.O.Plus((CENTR_X - Cube.O.x)*deltatime/200, (CENTR_Y -  20 - Cube.O.y)*deltatime/400);
    // Cube.setColor(tft.color565(170 + sin(fixedTime * PI/200)*85, 170 + sin(fixedTime * PI/200 - PI*2/3)*85, 170 + sin(fixedTime * PI/200 + PI*2/3)*85));
    // Cube.Angle.Equals(fixedTime*PI/240,fixedTime*PI/200, fixedTime*PI/150);
    // Cube.drawCube(40);

    //canvas.fillTriangle(CENTR_X - 100, CENTR_Y - 100, CENTR_X + 100, CENTR_Y - 100, CENTR_X + 100, CENTR_Y + 100, TFT_GREEN);
    
}

unsigned long debugTimeStart = 0, debugPushCheck = 0, debugRenderCheck = 0; 
void loop() 
{
    fixedTime = millis()*60/1000; //float which every integer is 1/60 of second
    last_FOV = FOV;
    deltatime = millis() - last4deltaTime;
    if (deltatime > 100)
        deltatime = 100;
    last4deltaTime = millis();


    //render
    debugTimeStart = millis();
    canvas1.fillSprite(TFT_RED);

    canvas.fillSprite(TFT_RED);
    drawFrame();
    //delay(10);
    debugRenderCheck = millis() - debugTimeStart;
    
    debugTimeStart = millis();
    //canvas.pushSprite(0, 0);
    //while (tft.dmaBusy());
        tft.pushImageDMA(0,0, SCREEN_WIDTH, SCREEN_HEIGHT-20, cnvsPnr);
    //while (tft.dmaBusy());
        tft.pushImageDMA(0, 0, SCREEN_WIDTH, 20, cnvsPnr1);
    debugPushCheck = millis() - debugTimeStart;

    //Entity::processAllEntities(deltatime);

/////debug

    f++;
	if (millis() - framecheck > 1000)
	{        
        //log_d("Free heap: %d/%d %d%", ESP.getFreeHeap(), ESP.getHeapSize(), 100*ESP.getFreeHeap()/ESP.getHeapSize());
        log_d("FPS: %d\n", f);
        log_d("Push time: %dms\n", debugPushCheck);
        // log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

		framecheck = millis();
		f = 0;
	}
}