#ifndef DEV_SETUP_H
#define DEV_SETUP_H

#include <Arduino.h>

//////////////////display info/////////////////
#define SCRN_WIDTH 240
#define SCRN_HEIGHT 280

#define CENTR_X SCRN_WIDTH / 2
#define CENTR_Y SCRN_HEIGHT / 2

#define SCRN_ROTATION 0 // 0: landscape
#define SPLIT_SCREEN 2

#define DEFAULT_FOV PI*0.5
#define DEFAULT_RENDER_DISTANCE 100 //todo think about metrics

/////////////////////saves//////////////////////
struct saveFile 
{
    //change as you wish
    char userName[16] = "NOMEMO";
    
    uint8_t difficulty = 0;

    uint8_t stage = 0;
    uint8_t progress = 0;
};

#endif