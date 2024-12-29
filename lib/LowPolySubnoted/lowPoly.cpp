#include "lowPoly.h"

void LowPoly::init()
{
#if DEBUG_MODE
    log_d("Memory info (before initialization)\nPSRAM - \tTotal: %u,\tFree: %u,\tBiggest free block: %u\nInternal  - \tTotal: %u,\tFree: %u,\tBiggest free block: %u\n", 
        heap_caps_get_total_size(MALLOC_CAP_SPIRAM),
        heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
        heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM),
        heap_caps_get_total_size(MALLOC_CAP_INTERNAL),
        heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
        heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));

#endif
}