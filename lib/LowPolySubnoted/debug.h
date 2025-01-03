#ifndef DEBUG_H
#define DEBUG_H

// #include "devSetup.h"
#include <cstdint>

// #if DEBUG_MODE
class Debug{
public:
    static uint16_t frameCalls;
    static uint16_t physicsCalls;
    static unsigned long debugPushCheck;
    static unsigned long debugRenderCheck;
    static unsigned long debugRenderCheckSum;
    static unsigned long debugRenderCheckCount;
};



#endif //DEBUG_H