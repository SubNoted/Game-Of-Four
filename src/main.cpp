#include <Arduino.h>

#include <SPI.h>
#include <TFT_eSPI.h> 
#include "entity.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define CENTR_X SCREEN_WIDTH/2
#define CENTR_Y SCREEN_HEIGHT/2

#define SCREEN_ROTATION 0 //default: landscape
#define isSPLIT_SCREEN false //use split screen algorithm? //in best cases gives only 24 fps
#define SCREEN_SPLIT 2 //to save RAM
float FOV = PI/2, last_FOV = 0;


TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);
TFT_eSprite txt = TFT_eSprite(&tft);
TFT_eSprite cir = TFT_eSprite(&tft);

TFT_eSprite sprite = TFT_eSprite(&tft);

uint16_t* cnvsPnr = nullptr;


uint16_t BG_COL = tft.color565(194,144,195);
// #define BG_COL TFT_BLUE//tft.color565(255,220,220)

//////////

//////////

#define isSTARS false
#define MAX_STARS 16
typedef struct Particle {
    uint16_t x, y, z, size, rotation;
    uint8_t phase = 0;
    const uint8_t maxPhase = 180;
    bool set = false;
    TFT_eSprite spr = TFT_eSprite(&tft);
} Particle;
#if isSTARS
Particle star[MAX_STARS];
#endif

////////tools/////////
unsigned long framecheck = 0, fixedTime = 0, clearTime = 0, last4deltaTime = 0;
float deltatime = 0;
String str = "lol";
#define MAX_CONSL 6
#define isDEBUG_MODE true

uint8_t f = 0, tps = 0, i = 0;
float normalSin(float x)//from 0 to 1 on PI
{
    return pow(sin(x/2), 2);
}

///////////////ENTITIES/////////////////
#define MAX_UI 8
Entity Cube;

////////////////SETUP/////////////////////////////////
void setup() 
{
    randomSeed(analogRead(23));
	
    log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    log_d("free heap: %d\n", ESP.getFreeHeap());

    if(psramFound())
    {
        log_d("PSRAM Detected\n");
    }

    ////////////init////////////////////

	tft.init();
    tft.initDMA();
	tft.setRotation(SCREEN_ROTATION);
	//tft.fillScreen(tft.color565(255,220,220));
	tft.fillScreen(BG_COL);
    tft.setSwapBytes(true);

//screen sprite to split
// #if isSPLIT_SCREEN
// 	canvas.setColorDepth(16);
// 	canvas.createSprite(SCREEN_WIDTH/SCREEN_SPLIT, SCREEN_HEIGHT);
//     canvas.fillScreen(TFT_BLACK);
// 	canvas.setSwapBytes(true);
// #endif

    Entity::initALL(&sprite, SCREEN_WIDTH, SCREEN_HEIGHT, &FOV, &last_FOV, &BG_COL);
    Cube.init();
    
    last4deltaTime = millis();

    Cube.O.Equals(SCREEN_WIDTH/2, -50, -160);
    Cube.constA.z = 3;

    canvas.setColorDepth(16); 
	cnvsPnr = (uint16_t*)canvas.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT - 5);
    canvas.fillScreen(TFT_BLACK);
	canvas.setSwapBytes(true);
	//canvas.pushImage(0, 0, 120, 120, Ducksser, TFT_BLACK);
    //tft.pushImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, clouds);
    //canvas.pushSprite(0,0, TFT_BLACK);

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
    
#if isSTARS
    for(i = 0; i < MAX_STARS; i++)
        if (star[i].phase > 0)
        {
            star[i].spr.fillSprite(TFT_BLUE);
            if (star[i].phase == 1 || star[i].x == 0 || star[i].y == 0)
            {
                star[i].spr.pushSprite(star[i].x, star[i].y);
                star[i].spr.deleteSprite();
            }
            star[i].phase--;
            star[i].x--;
            star[i].y--;
            star[i].z = pow(sin((float)star[i].phase*PI/star[i].maxPhase), 2)*star[i].size;
            star[i].spr.fillCircle(star[i].size*2, star[i].size*2, star[i].z, TFT_WHITE);
            //star[i].spr.setPivot(star[i].x, star[i].y);
            //star[i].spr.pushImage(0, 0, 33, 33, starImage);
            star[i].spr.pushSprite(star[i].x, star[i].y);
            //star[i].spr.pushRotated(&canvas, star[i].phase);
        }
#endif
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


//spawn particles every 30 frames
#if isSTARS
    if(t%30==0)
        for(i = 0; i < MAX_STARS; i++)
            if (star[i].phase == 0)
            {
                star[i].phase = star[i].maxPhase;
                star[i].size = random(4,10);
                star[i].spr.setColorDepth(8);
	            star[i].spr.setSwapBytes(true);
                star[i].spr.createSprite(star[i].size*4, star[i].size*4);
                //star[i].spr.createSprite(35, 35);
                star[i].x = random(SCREEN_WIDTH/2) + (i%2)*SCREEN_WIDTH/2;
                star[i].y = random(SCREEN_HEIGHT/2) + ((int)(i/2)%2)*SCREEN_HEIGHT/2;
                break;
            }
#endif
    
	//digitalWrite(PC13, ts.touched());
    /*str = "";
	if (Serial.available()) {
		str = Serial.readStringUntil('\n'); // Чтение команды из последовательного порта
		//processCommand(command); // Обработка полученной команды
		str.trim();
        debugtxt[5] = str;
	}
    str = "";*/
	
	//tft.pushImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, clouds);
	//analogWrite(PA11, sin((float)t/20)*sin((float)t/20)*255);


//split frame algoritm
#if isSPLIT_SCREEN
    for (i = 0; i<SCREEN_SPLIT; i++)
    {
	    canvas.fillSprite(TFT_RED);
        //scrn.pushImage(-SCREEN_WIDTH/SCREEN_SPLIT * i, 0, SCREEN_WIDTH, SCREEN_HEIGHT, clouds);
	    //drawFrame();
        //canvas.pushSprite(SCREEN_WIDTH/SCREEN_SPLIT * i, 45, TFT_BLACK);
        tft.pushImageDMA8bit(0,SCREEN_HEIGHT/2 * i, SCREEN_WIDTH, SCREEN_HEIGHT/2, cnvsPnr);
    }
#else

    debugTimeStart = millis();
    canvas.fillSprite(TFT_RED);
    drawFrame();
    //delay(10);
    debugRenderCheck = millis() - debugTimeStart;
    
    debugTimeStart = millis();
    canvas.pushSprite(0, 0);
    //tft.pushImageDMA(0,0, SCREEN_WIDTH, SCREEN_HEIGHT - 5, cnvsPnr);
    debugPushCheck = millis() - debugTimeStart;
#endif
    Entity::processAllEntities(deltatime);

/////debug

    f++;
	if (millis() - framecheck > 1000)
	{        
        // log_d("Free heap: %d/%d %d%", ESP.getFreeHeap(), ESP.getHeapSize(), 100*ESP.getFreeHeap()/ESP.getHeapSize());
        // log_d("FPS: %d\n", f);
        // log_d("Push time: %dms\n", debugPushCheck);
        // log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));

		framecheck = millis();
		f = 0;
	}
}