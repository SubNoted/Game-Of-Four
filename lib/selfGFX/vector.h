class Vector
{
    public:
    float x, y, z;
    Vector(void);
    Vector(float x, float y, float z);
    Vector(float x, float y);

    bool isEqual(Vector v),
        isEqual(Vector v, float r),
        isExist();

    float L(void),
        L(Vector v),
        L(float x, float y, float z),
        L(float x, float y);

    Vector Summ(Vector s);
    Vector Delta(Vector s);
    Vector Delta(float x, float y);

    void Plus(Vector v),
        Plus(float x, float y, float z),
        Plus(float x, float y);

    void Minus(Vector v),
        Minus(float x, float y, float z),
        Minus(float x, float y);

    void Multiply(Vector v),
        Multiply(float x, float y, float z),
        Multiply(float x, float y),
        Multiply(float a);

    void Equals(Vector v),
        Equals(float x, float y, float z),
        Equals(float x, float y);

    void toOneVector();

    float ScalarProd(Vector v);

    void setRotation(Vector alp);
    void Rotate(Vector alp);
    void Reverse();
    void Round();
    void Reset();

    static Vector Normal(Vector& a, Vector& b, Vector& c);
};

class Vector2
{
    public:
    float x, y;
    Vector2(void);
    Vector2(Vector v);
    Vector2(float x, float y);
    Vector toVector3();

    bool isEqual(Vector2 v),
        isEqual(Vector2 v, float r);

    bool isExist();

    float L(void),
        L(Vector2 v),
        L(float x, float y);

    Vector2 Summ(Vector2 s);
    Vector2 Summ(Vector s);
    Vector2 Delta(Vector2 s);
    Vector2 Delta(Vector s);

    void Plus(Vector2 v),
        Plus(float x, float y);

    void Minus(Vector2 v),
        Minus(float x, float y);

    void Multiply(Vector2 v),
        Multiply(float x, float y);

    void Equals(Vector2 v),
        Equals(Vector v),
        Equals(float x, float y);

        
    void Rotate(float alp);
    void Round();
    void Reset();
};

class Bounding2
{
    public:
    bool upper;
    float k, c;

    Bounding2(void);
    Bounding2(Vector2 p0, Vector2 p1, Vector2 v);

    Vector2 intersection(Bounding2 b);

    bool isInBounds(Vector2& v);
    bool isInBounds(float x, float y);

    void Reset();
};
