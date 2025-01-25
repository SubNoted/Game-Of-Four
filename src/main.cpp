#include <Arduino.h>

#include <memory>
#include <bits/unique_ptr.h>
#include "esp_task_wdt.h"

#include <lowPoly.h>

/////////scenes////////////
#include "sceneTest.h"//test scene

// #include "cloudsTex.h"


LowPoly lowPoly;
SceneManager sceneManager;


void core0(void * pvParameters);

////////////////SETUP/////////////////////////////////
void setup() 
{
// log_d("image size %d", sizeof(cloudsTex));
 uint32_t size_flash_chip;
esp_flash_get_size(NULL, &size_flash_chip);
log_d("flash size %d", size_flash_chip);

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
}

void loop() 
{
    sceneManager.render(); //current scene render loop
}