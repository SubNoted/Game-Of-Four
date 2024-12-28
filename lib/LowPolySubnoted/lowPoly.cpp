#include "lowPoly.h"

void LowPoly::init()
{
#if DEBUG_MODE
    log_d("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT): %d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    log_d("free heap: %d\n", ESP.getFreeHeap());

    
    if(psramFound())
    {
        log_d("PSRAM Detected\n");
    }

#endif
}