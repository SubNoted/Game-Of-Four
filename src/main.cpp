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

    // pinMode(34, INPUT_PULLDOWN);
    pinMode(4, INPUT_PULLDOWN);
    // pinMode(32, PULLDOWN);
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