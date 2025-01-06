#ifndef DEBUG_H
#define DEBUG_H

// #include "devSetup.h"
#include <cstdint>

// #if DEBUG_MODE
class Debug{
public:
    static uint16_t frameCalls;
    static uint16_t physicsCalls;
    static unsigned long pushTime;
    static unsigned long pushTimeSum;
    static unsigned long renderTime;
    static unsigned long renderTimeSum;
    static unsigned long renderCallsCount;

    static unsigned long prerenderTime;


};



#endif //DEBUG_H