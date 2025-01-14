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

void Polygon::setUV(uint8_t uvx0,uint8_t uvy0, uint8_t uvx1,uint8_t uvy1, uint8_t uvx2,uint8_t uvy2)
{
    uv[0][0] = uvx0;
    uv[0][1] = uvy0;
    uv[1][0] = uvx1;
    uv[1][1] = uvy1;
    uv[2][0] = uvx2;
    uv[2][1] = uvy2;
}

//////////////////SmoothPolygon////////////////////////////////

SmoothPolygon::SmoothPolygon() {}

SmoothPolygon::SmoothPolygon(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2) 
{
    setVertices(v0, v1, v2);
}

void SmoothPolygon::setVertices(const uint16_t& v0, const uint16_t& v1, const uint16_t& v2)  
{
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
}
void SmoothPolygon::setVertexNormals(const UnitVector& n0, const UnitVector& n1, const UnitVector& n2)
{
    vertexNormals[0] = n0;
    vertexNormals[1] = n1;
    vertexNormals[2] = n2;
}

UnitVector SmoothPolygon::getNormal(const Vector& v) //todo get normal of pixel on polygon
{
    return UnitVector(vertices[0], vertices[1], vertices[2]);//todo change

}