#include <Arduino.h>

#include <memory>
#include <bits/unique_ptr.h>
#include "esp_task_wdt.h"

#include <lowPoly.h>

/////////scenes////////////
#include "sceneTest.h"//test scene


LowPoly lowPoly;
SceneManager sceneManager;


void core0(void * pvParameters);

////////////////SETUP/////////////////////////////////
void setup() 
{
    pinMode(12, ANALOG);

    ////esp32////
#ifdef ESP32_ON
    pinMode(34, INPUT_PULLDOWN); //left stick Y axis
    pinMode(4, INPUT_PULLDOWN); //left stick X axis
#elif defined(ESP32_S3_ON)
    //esp32-s3////
    pinMode(14, INPUT_PULLDOWN); //left stick Y axis
    pinMode(13, INPUT_PULLDOWN); //left stick X axis

    pinMode(4, INPUT_PULLDOWN); //right stick Y axis
    pinMode(5, INPUT_PULLDOWN); //right stick X axis
#endif


    randomSeed(analogRead(12));

	lowPoly.init();
    sceneManager.initRenderer();
    sceneManager.changeScene(std::shared_ptr<Tscene>(new Tscene()));//set test scene
    
    xTaskCreatePinnedToCore(core0, "Physics", 10000, NULL, tskIDLE_PRIORITY , NULL,  0); 

}

void loop() 
{
    sceneManager.render(); //current scene render loop
}

void core0(void * pvParameters){
    esp_task_wdt_add(nullptr);
    for (;;) {
        esp_task_wdt_reset();


        sceneManager.update(); //current scene update loop
    }
}