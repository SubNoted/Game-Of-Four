#ifndef DEBUG_H
#define DEBUG_H

// #include "devSetup.h"
#include <cstdint>

// #if DEBUG_MODE
class Debug{
public:
    static uint8_t frameCalls;
    static uint8_t physicsCalls;
    static unsigned long debugPushCheck;
    static unsigned long debugRenderCheck;
};



#endif //DEBUG_H