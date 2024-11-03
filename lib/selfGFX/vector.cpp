#include "vector.h"
#include <math.h>

float hypotenuse(float a, float b)
{
    return sqrt(a*a + b*b);
} 
float alpha(float y, float x)
{
    return (atan(y/x) + (x<0 ? M_PI : 0));
}

Vector::Vector(void)
{
    x = 0;
    y = 0;
    z = 0;
}
Vector::Vector(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
Vector::Vector(float x, float y)
{
    this->x = x;
    this->y = y;
}

bool Vector::isEqual(Vector v)
{
    if (this->x == v.x && this->y == v.y && this->z == v.z)
        return true;
    return false;
}

bool Vector::isEqual(Vector v, float r)
{
    if (abs(this->x - v.x) < r && abs(this->y - v.y) < r && abs(this->z - v.z) < r)
        return true;
    return false;
}

bool Vector::isExist()
{
    if (this->x != 0 || this->z != 0 || this->y != 0)
        return true;
    return false;
}

float Vector::L(void)
{
    return sqrt(x*x + y*y + z*z);
}
float Vector::L(Vector v)
{
    return sqrt(pow(this->x-v.x, 2) + pow(this->y-v.y, 2) + pow(this->z-v.z, 2));
}
float Vector::L(float x, float y, float z)
{
    return sqrt(pow(this->x-x, 2) + pow(this->y-y, 2) + pow(this->z-z, 2));
}
float Vector::L(float x, float y)
{
    return sqrt(pow(this->x-x, 2) + pow(this->y-y, 2));
}

Vector Vector::Summ(Vector s)
{
    return Vector(this->x+s.x, this->y+s.y, this->z+s.z);
}
Vector Vector::Delta(Vector d)
{
    return Vector((this->x-d.x), (this->y-d.y), (this->z-d.z));
}
Vector Vector::Delta(float x, float y)
{
    return Vector((this->x-x), (this->y-y), this->z);
}

void Vector::Plus(Vector v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}
void Vector::Plus(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
}
void Vector::Plus(float x, float y)
{
    this->x += x;
    this->y += y;
}

void Vector::Minus(Vector v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
}
void Vector::Minus(float x, float y, float z)
{
    this->x -= x;
    this->y -= y;
    this->z -= z;
}
void Vector::Minus(float x, float y)
{
    this->x -= x;
    this->y -= y;
}

void Vector::Multiply(Vector v)
{
    this->x *= v.x;
    this->y *= v.y;
    this->z *= v.z;
}
void Vector::Multiply(float x, float y, float z)
{
    this->x *= x;
    this->y *= y;
    this->z *= z;
}
void Vector::Multiply(float x, float y)
{
    this->x *= x;
    this->y *= y;
}

void Vector::Multiply(float a)
{
    this->x *= a;
    this->y *= a;
    this->z *= a;
}

void Vector::Equals(Vector v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}
void Vector::Equals(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
void Vector::Equals(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector::toOneVector()
{
    float m = 1;
    if (abs(this->x) > m)
        m = abs(this->x);
    if (abs(this->y) > m)
        m = abs(this->y);
    if (abs(this->z) > m)
        m = abs(this->z);
        
    this->x = this->x/m;
    this->y = this->y/m;
    this->z = this->z/m;
}

float Vector::ScalarProd(Vector v)
{
    Vector v0 = Vector(*this);
    v0.toOneVector();
    v.toOneVector();
    return (v0.x*v.x + v0.y*v.y + v0.z*v.z);
}

void Vector::setRotation(Vector d)
{
    this->Equals(this->L(), 0, 0);
    this->Equals(
        this->x * cos(d.x) - this->y * sin(d.x),
        this->x * sin(d.x) + this->y * cos(d.x),
        this->z
    );
    
    this->Equals(
        this->x * cos(d.y) - this->z * sin(d.y),
        this->y,
        this->x * sin(d.y) + this->z * cos(d.y)
    );
    
    this->Equals(
        this->x,
        this->z * sin(d.z) + this->y * cos(d.z),
        this->z * cos(d.z) - this->y * sin(d.z)
    );
}

void Vector::Rotate(Vector d)
{
    this->Equals(
        this->x * cos(d.x) - this->y * sin(d.x),
        this->x * sin(d.x) + this->y * cos(d.x),
        this->z
    );
    
    this->Equals(
        this->x * cos(d.y) - this->z * sin(d.y),
        this->y,
        this->x * sin(d.y) + this->z * cos(d.y)
    );
    
    this->Equals(
        this->x,
        this->z * sin(d.z) + this->y * cos(d.z),
        this->z * cos(d.z) - this->y * sin(d.z)
    );
}

void Vector::Reverse()
{
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

void Vector::Round()
{
    this->x = (int)this->x;
    this->y = (int)this->y;
    this->z = (int)this->z;
}

void Vector::Reset()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector Vector::Normal(Vector& a, Vector& b, Vector& c)
{
    Vector ab = b.Delta(a), ac = c.Delta(a);
    return Vector(ab.y * ac.z - ab.z * ac.y, ab.z * ac.x - ab.x * ac.z, ab.x * ac.y - ab.y * ac.x);
}

////////////////////////////////////////////VECTOR2/////////////////////////////////////////////////////

Vector2::Vector2(void)
{
    x = 0;
    y = 0;
}
Vector2::Vector2(Vector v)
{
    this->x = v.x;
    this->y = v.y;
}
Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}
Vector Vector2::toVector3()
{
    return Vector(this->x, this->y);
}

bool Vector2::isEqual(Vector2 v)
{
    if (this->x == v.x && this->y == v.y)
        return true;
    return false;
}

bool Vector2::isEqual(Vector2 v, float r)
{
    if (abs(this->x - v.x) < r && abs(this->y - v.y) < r)
        return true;
    return false;
}

bool Vector2::isExist()
{
    if (this->x != 0 || this->y != 0)
        return true;
    return false;
}

float Vector2::L(void)
{
    return sqrt(x*x + y*y);
}
float Vector2::L(Vector2 v)
{
    return sqrt(pow(this->x-v.x, 2) + pow(this->y-v.y, 2));
}
float Vector2::L(float x, float y)
{
    return sqrt(pow(this->x-x, 2) + pow(this->y-y, 2));
}

Vector2 Vector2::Summ(Vector2 s)
{
    return Vector2(this->x+s.x, this->y+s.y);
}
Vector2 Vector2::Summ(Vector s)
{
    return Vector2(this->x+s.x, this->y+s.y);
}
Vector2 Vector2::Delta(Vector2 s)
{
    return Vector2(this->x-s.x, this->y-s.y);
}
Vector2 Vector2::Delta(Vector s)
{
    return Vector2(this->x-s.x, this->y-s.y);
}

void Vector2::Plus(Vector2 v)
{
    this->x += v.x;
    this->y += v.y;
}
void Vector2::Plus(float x, float y)
{
    this->x += x;
    this->y += y;
}

void Vector2::Minus(Vector2 v)
{
    this->x -= v.x;
    this->y -= v.y;
}
void Vector2::Minus(float x, float y)
{
    this->x -= x;
    this->y -= y;
}

void Vector2::Multiply(Vector2 v)
{
    this->x *= v.x;
    this->y *= v.y;
}
void Vector2::Multiply(float x, float y)
{
    this->x *= x;
    this->y *= y;
}

void Vector2::Equals(Vector2 v)
{
    this->x = v.x;
    this->y = v.y;
}
void Vector2::Equals(Vector v)
{
    this->x = v.x;
    this->y = v.y;
}
void Vector2::Equals(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector2::Rotate(float d)
{
    this->Equals(
        this->x * cos(d) - this->y * sin(d),
        this->x * sin(d) + this->y * cos(d)
    );
}

void Vector2::Round()
{
    this->x = (int)this->x;
    this->y = (int)this->y;
}

void Vector2::Reset()
{
    this->x = 0;
    this->y = 0;
}

////////////////////////////////////////////BOUNDING2/////////////////////////////////////////////////////

Bounding2::Bounding2()
{
    this->upper = false;
    this->k = 0;
    this->c = 0;
}
Bounding2::Bounding2(Vector2 p0, Vector2 p1, Vector2 v)
{
    if (p1.x == p0.x)
        p1.x++;
    this->k = (p1.y - p0.y)/(p1.x - p0.x);
    this->c = p0.y - this->k*p0.x;
    
    this->upper = (v.y > this->k * v.x + this->c);
}

Vector2 Bounding2::intersection(Bounding2 b)
{
    int x = (b.c - this->c)/(this->k - b.k);
    return Vector2(x, x*this->k + this->c);
}

bool Bounding2::isInBounds(Vector2& v)
{
    return  (v.y > this->k * v.x + this->c) == this->upper;
}
bool Bounding2::isInBounds(float x, float y)
{
    return  (y > this->k * x + this->c) == this->upper;
}

void Bounding2::Reset()
{
    this->upper = false;
    this->k = 0;
    this->c = 0;
}