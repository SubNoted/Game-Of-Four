#include "debug.h"

uint16_t Debug::frameCalls = 0;
uint16_t Debug::physicsCalls = 0;
unsigned long Debug::debugPushCheck = 0;
unsigned long Debug::debugRenderCheck = 0;
unsigned long Debug::debugRenderCheckSum = 0;
unsigned long Debug::debugRenderCheckCount = 0;