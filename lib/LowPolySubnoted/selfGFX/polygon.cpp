#include "polygon.h"

Polygon::Polygon() {}

Polygon::Polygon(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2) 
{
    setVertices(v0, v1, v2);
}

void Polygon::setVertices(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2)  
{
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
}

UnitVector Polygon::getNormal()
{
    return UnitVector(vertices[0], vertices[1], vertices[2]);//todo test

}