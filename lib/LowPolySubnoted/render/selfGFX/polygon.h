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
    uint8_t uv[3][2];
    
    Polygon(void);
    Polygon(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2);
    void setVertices(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2);
    void draw();
};
class SmoothPolygon
{
private:

public:
    uint16_t vertices[3]; //number of vertices in scene


    UnitVector normal;
    std::array<UnitVector, 3> vertexNormals;
    
    SmoothPolygon(void);
    SmoothPolygon(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2);
    void setVertices(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2);
    void setVertexNormals(const UnitVector& n0, const UnitVector& n1, const UnitVector& n2);
    UnitVector getNormal(const Vector& v);
};


#endif