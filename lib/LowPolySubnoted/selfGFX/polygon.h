#ifndef _POLYGON_
#define _POLYGON_

#include "vector.h"
// #include <scene/scene.h>
#include <vector>

class Polygon
{
private:

public:
    uint16_t vertices[3]; //number of vertices in scene

    UnitVector getNormal();

    UnitVector normal;
    
    Polygon(void);
    Polygon(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2);
    void setVertices(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2);
    void draw();
};



#endif