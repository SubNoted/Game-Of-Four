#include <Arduino.h>

#include <memory>
#include "esp_task_wdt.h"

#include <SPI.h>
#include <TFT_eSPI.h> 

#include <lowPoly.h>

/////////scenes////////////
#include "sceneTest.h"
#include <bits/unique_ptr.h>

LowPoly lowPoly;
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
	

    if(psramFound())//todo find one
    {
        log_d("PSRAM Detected\n");
    }

    ////////////init////////////////////

	lowPoly.init();
    
    //startscene
    sceneManager.changeScene(std::unique_ptr<Tscene>(new Tscene()));
    
    xTaskCreatePinnedToCore(core0, "Physics", 10000, NULL, tskIDLE_PRIORITY , NULL,  0); 

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