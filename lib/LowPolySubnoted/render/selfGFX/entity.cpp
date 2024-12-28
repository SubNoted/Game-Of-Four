#include "entity.h"
#include <math.h>

uint16_t SCREEN_WIDTH;
uint16_t SCREEN_HEIGHT;

#define CENTR_X SCREEN_WIDTH/2
#define CENTR_Y SCREEN_HEIGHT/2

// TFT_eSprite* Entity::sprite;
// uint16_t Entity::SCREEN_WIDTH;
// uint16_t Entity::SCREEN_HEIGHT;
// uint16_t* Entity::BG_COL;
// float* Entity::FOV;
// float* Entity::last_FOV;

// Vector2 Entity::Camera = Vector2();
// Vector2 Entity::last_Camera = Vector2();

Entity* Entity::ALL_ENTITIES[64];
uint8_t Entity::ENTITIES_COUNT = 0;

// uint8_t Entity::datum = TC_DATUM;

//static
// void Entity::initALL(TFT_eSprite *s, uint16_t screen_width, uint16_t screen_height, float *fov, float *last_fov, uint16_t *bg_col)
// {
//     sprite = s;
//     BG_COL = bg_col;
//     FOV = fov;

//     last_FOV = last_fov;
    
//     SCREEN_WIDTH = screen_width;
//     SCREEN_HEIGHT = screen_height;
// }

// void Entity::init(TFT_eSprite *s, uint16_t screen_width, uint16_t screen_height, float *fov, float *last_fov, uint16_t *bg_col)
// {
//     // sprite = s;
//     // BG_COL = bg_col;
//     // FOV = fov;

//     // last_FOV = last_fov;
    
//     SCREEN_WIDTH = screen_width;
//     SCREEN_HEIGHT = screen_height;
//     reInit();

//     ALL_ENTITIES[ENTITIES_COUNT] = this;
//     ENTITIES_COUNT++;
// }


// void Entity::init()
// {
//     reInit();

//     ALL_ENTITIES[ENTITIES_COUNT] = this;
//     ENTITIES_COUNT++;
// }

// void Entity::reInit()
// {
//     last_O = Vector();
//     last_Size = Vector();
//     last_Angle = Vector();
//     this->last_Text[0].equals("");
//     this->last_Text[1].equals("");
//     this->last_Text[2].equals("");
//     this->Text[0] = String();
//     this->Text[1] = String();
//     this->Text[2] = String();
//     last_textSize = 2;
//     last_textWrap = true;
    
//     O = Vector();
//     Size = Vector();
//     Angle = Vector();
//     textOffSet = Vector();
//     /*this->Text[0].equals("");
//     this->Text[1].equals("");
//     this->Text[2].equals("");*/
//     textSize = 1;
//     textWrap = false;

//     Color = TFT_WHITE;
//     textColor = TFT_WHITE;
//     Update = true;
    
//     minp = Vector2();
//     maxp = Vector2();

//     V = Vector();
//     constA = Vector(0,0,0);
//     lightDirection = Vector(0, 0.5, 1);
// }
// void Entity::deleteEntity()
// {
//     //uint8_t newS = ENTITIES_COUNT - 1;
//     //Entity* ALL_ENTITIES[64]
// }


/////////static/////////////
// void Entity::setCameraPos(const Vector& v)
// {
//     Camera.Equals(v);
//     if (!Camera.isEqual(last_Camera))
//         for(int i = 0; i < ENTITIES_COUNT; i++)
//             ALL_ENTITIES[i]->Update = true;
// }
// void Entity::plusCameraPos(const Vector& v)
// {
//     Camera.Plus(v);
//     if (v.x != 0 || v.y != 0 || v.z != 0)
//         for(int i = 0; i < ENTITIES_COUNT; i++)
//             ALL_ENTITIES[i]->Update = true;
// }
// Vector2 Entity::getCameraPos()
// {
//     return Camera;
// }
// void Entity::endcameraFrame()
// {
//     last_Camera.Equals(Camera);
// }

void Entity::processAllEntities(float &t)
{
    for(int i = 0; i < ENTITIES_COUNT; i++)
        ALL_ENTITIES[i]->processPhysics(t);
}
void Entity::updateALL()
{
    for(int i = 0; i < ENTITIES_COUNT; i++)
        ALL_ENTITIES[i]->Update = true;
}
// void Entity::firstTouchAllEntities(const Vector2 &first_touch)
// {
//     for(int i = 0; i < ENTITIES_COUNT; i++)
//     {
//         if (ALL_ENTITIES[i]->O.isExist() && first_touch.x != 0 && first_touch.y != 0 && ALL_ENTITIES[i]->isTouched(first_touch))
//             ALL_ENTITIES[i]->firstTouched = true;
//         else
//             ALL_ENTITIES[i]->firstTouched = false;
//     }
// }
bool Entity::isFirstTouchedAnyEntity()
{
    for(int i = 0; i < ENTITIES_COUNT; i++)
        if(ALL_ENTITIES[i]->isFirstTouched())
            return true;
    return false;
}

// bool Entity::isFirstTouched()
// {
//     return firstTouched;
// }

// void Entity::reItitAll()
// {
//     Entity::setCameraPos(Vector());
//     for(int i = 0; i < ENTITIES_COUNT; i++)
//     {
//         ALL_ENTITIES[i]->reInit();
//         ALL_ENTITIES[i]->Update = true;
//     }
//     Entity::endcameraFrame();
// }

void Entity::deleteALL()
{
    for(int i = 0; i < ENTITIES_COUNT; i++)
    {
        //ALL_ENTITIES[i]->deleteEntity();
        //free(ALL_ENTITIES[i]);
    }
    Entity::ENTITIES_COUNT = 0;
}

void Entity::processPhysics(float &t)
{
    if (!this->O.isExist())
        return;
    this->V.x += this->constA.x*t/60;
    this->V.y += this->constA.y*t/60;
    this->V.z += this->constA.z*t/60;
    this->O.Plus(this->V);
    if (constA.z != 0 && this->O.z * this->constA.z > 0)
    {
        this->O.z = 0;
        this->V.z = 0;
    }
    if (this->O.isEqual(Vector(), 1))
        this->O.Equals(Vector());
    if (this->V.isEqual(Vector(), 1))
        this->V.Equals(Vector());
    else
        this->V.Multiply(0.98);
}

// bool Entity::isTouched(Vector2 touch)
// {
//     if (!touch.isExist())
//         return false;
//     if (touch.x >= minp.x - 10 + O.x - Camera.x && touch.x <= maxp.x + 10 + O.x - Camera.x 
//     && touch.y >= minp.y - 10 + O.y - Camera.y && touch.y <= maxp.y + 10 + O.y - Camera.y)
//     {
//         return true;
//     }
//     return false;
// }

Entity::Entity()
{
    this->vertices = nullptr;
    this->polygons = nullptr;
}

Entity::Entity(std::vector<Polygon>* polygons, std::vector<Vector>* vertices)
{
    this->vertices = vertices;
    this->polygons = polygons;
}


void Entity::init(std::vector<Polygon>* polygons, std::vector<Vector>* vertices)
{
    this->vertices = vertices;
    this->polygons = polygons;
}


void Entity::createCube(Vector o, Vector size)
{
    //todo deinit if exists
    this->O.Equals(o);
    this->Size.Equals(size);
    this->Update = true;

//          4----------5         
//        /          / |        
//     /          /    |         
//   0----------1      |         
//   |      7   |      6      
//   |          |    /           
//   |          | /          
//   3----------2     

    verStartNum = vertices->size();
    verSize = 8;

    vertices->push_back(Vector(O.x - Size.x/2, O.y + Size.y/2, O.z + Size.z/2));//0
    vertices->push_back(Vector(O.x + Size.x/2, O.y + Size.y/2, O.z + Size.z/2));//1
    vertices->push_back(Vector(O.x + Size.x/2, O.y - Size.y/2, O.z + Size.z/2));//2
    vertices->push_back(Vector(O.x - Size.x/2, O.y - Size.y/2, O.z + Size.z/2));//3

    vertices->push_back(Vector(O.x - Size.x/2, O.y + Size.y/2, O.z - Size.z/2));//4
    vertices->push_back(Vector(O.x + Size.x/2, O.y + Size.y/2, O.z - Size.z/2));//5
    vertices->push_back(Vector(O.x + Size.x/2, O.y - Size.y/2, O.z - Size.z/2));//6
    vertices->push_back(Vector(O.x - Size.x/2, O.y - Size.y/2, O.z - Size.z/2));//7

    //0-1-2-3
    polygons->push_back(Polygon(verStartNum, verStartNum + 1, verStartNum + 2));
    polygons->push_back(Polygon(verStartNum, verStartNum + 2, verStartNum + 3));

    for (int i = 0; i < 4; i++)
    {
        polygons->push_back(Polygon(verStartNum + i, verStartNum + 4 + (i + 1) % 4, verStartNum + (i+1)%4));
        polygons->push_back(Polygon(verStartNum + i, verStartNum + 4 + i, verStartNum + 4 + (i + 1) % 4));
    }

    //4-5-6-7
    polygons->push_back(Polygon(verStartNum+4, verStartNum + 6, verStartNum + 5));
    polygons->push_back(Polygon(verStartNum+4, verStartNum + 7, verStartNum + 6));

}


void Entity::setCube()
{
    (*vertices)[0] = (Vector(O.x - Size.x/2, O.y + Size.y/2, O.z + Size.z/2));//0
    (*vertices)[1] = (Vector(O.x + Size.x/2, O.y + Size.y/2, O.z + Size.z/2));//1
    (*vertices)[2] = (Vector(O.x + Size.x/2, O.y - Size.y/2, O.z + Size.z/2));//2
    (*vertices)[3] = (Vector(O.x - Size.x/2, O.y - Size.y/2, O.z + Size.z/2));//3

    (*vertices)[4] = (Vector(O.x - Size.x/2, O.y + Size.y/2, O.z - Size.z/2));//4
    (*vertices)[5] = (Vector(O.x + Size.x/2, O.y + Size.y/2, O.z - Size.z/2));//5
    (*vertices)[6] = (Vector(O.x + Size.x/2, O.y - Size.y/2, O.z - Size.z/2));//6
    (*vertices)[7] = (Vector(O.x - Size.x/2, O.y - Size.y/2, O.z - Size.z/2));//7

}

void Entity::setPosition(Vector v)
{
    if (v.isEqual(O))
        return;
    this->O.Equals(v);
    Update = true;
}
Vector Entity::getPosition()
{
    return this->O;
}
void Entity::setSize(Vector v)
{
    if (v.isEqual(Size))
        return;
    this->Size.Equals(v);
    Update = true;
}
Vector Entity::getSize()
{
    return this->Size;
}
void Entity::setRotation(Vector v)
{    
    (*vertices)[0] = (Vector(O.x - Size.x/2, O.y + Size.y/2, O.z + Size.z/2).Rotate(v, O));//0
    (*vertices)[1] = (Vector(O.x + Size.x/2, O.y + Size.y/2, O.z + Size.z/2).Rotate(v, O));//1
    (*vertices)[2] = (Vector(O.x + Size.x/2, O.y - Size.y/2, O.z + Size.z/2).Rotate(v, O));//2
    (*vertices)[3] = (Vector(O.x - Size.x/2, O.y - Size.y/2, O.z + Size.z/2).Rotate(v, O));//3

    (*vertices)[4] = (Vector(O.x - Size.x/2, O.y + Size.y/2, O.z - Size.z/2).Rotate(v, O));//4
    (*vertices)[5] = (Vector(O.x + Size.x/2, O.y + Size.y/2, O.z - Size.z/2).Rotate(v, O));//5
    (*vertices)[6] = (Vector(O.x + Size.x/2, O.y - Size.y/2, O.z - Size.z/2).Rotate(v, O));//6
    (*vertices)[7] = (Vector(O.x - Size.x/2, O.y - Size.y/2, O.z - Size.z/2).Rotate(v, O));//7
}
void Entity::rotate(Vector v)
{
    // if (v.isEqual(Angle))
    //     return;
    // this->Angle.Equals(v);
    // Update = true;

    for (int i = verStartNum; i < verSize; i++)
    {
        (*vertices)[i].Rotate(v, O);
    }
}
Vector Entity::getAngle()
{
    return this->Angle;
}
void Entity::setColor(uint16_t c)
{
    if (c == Color)
        return;
    Color = c;
    Update = true;
}
uint16_t Entity::getColor()
{
    return Color;
}
// void Entity::setTextSize(float x)
// {
//     if (x == textSize)
//         return;
//     textSize = x;
//     Update = true;
// }
// float Entity::getTextSize()
// {
//     return textSize;
// }
// void Entity::setText(String s, uint8_t n)
// {
//     if(s != Text[n])
//     {
//         Text[n] = s;
//         Update = true;
//     }
// }
// String Entity::getText(uint8_t n)
// {
//     return Text[n];
// }
// void Entity::setTextOffSet(Vector2& v)
// {
//     if(v.isEqual(textOffSet))
//         return;
//     textOffSet.Equals(v);
//     Update = true;
// }
// void Entity::setTextOffSet(const int16_t& x, const int16_t& y)
// {
//     if(x == this->textOffSet.x && y == this->textOffSet.y)
//         return;
//     textOffSet.Equals(x ,y);
//     Update = true;
// }
// Vector2 Entity::getTextOffSet()
// {
//     return textOffSet;
// }
// void Entity::setTextWrap(bool b)
// {
//     if (b == textWrap)
//         return;
//     textWrap = b;
//     Update = true;
// }
// bool Entity::getTextWrap()
// {
//     return textWrap;
// }
// void Entity::setTextColor(uint16_t c)
// {
//     if (textColor == c)
//         return;
//     textColor = c;
//     Update = true;
// }
// uint16_t Entity::getTextColor()
// {
//     return textColor;
// }

//////////////private////////////
// void Entity::createSprite(uint16_t x, uint16_t y)
// {
//     //sprite->setColorDepth(d);
// 	sprite->createSprite(x, y);
//     sprite->fillScreen(TFT_TRANSPARENT);
// 	sprite->setSwapBytes(true);

//     sprite->setTextDatum(datum);
// }
// bool Entity::isToUpdate()
// {
//     if (this->O.y - this->Size.y*2 > Camera.y + SCREEN_HEIGHT || this->O.y + this->Size.y*2 < Camera.y || this->O.x - this->Size.x*2 > Camera.x + SCREEN_WIDTH || this->O.x + this->Size.x*2 < Camera.x)
//         return false;
//     if (this->O.z > 1500 || this->O.z < -1500)
//         return false;
//     if (Update || !O.isEqual(last_O) || !Size.isEqual(last_Size) || !Angle.isEqual(last_Angle) 
//     || Text[0] != last_Text[0] || Text[1] != last_Text[1] || Text[2] != last_Text[2] || textSize != last_textSize || textWrap != last_textWrap)
//         return true;
//     return false;
// }
// void Entity::endDraw()
// {
//     last_O.Equals(O);
//     last_Size.Equals(Size);
//     last_Angle.Equals(Angle);
//     last_Text[0] = Text[0];
//     last_Text[1] = Text[1];
//     last_Text[2] = Text[2];
//     last_textOffSet = textOffSet;
//     last_textSize = textSize;
//     last_textWrap = textWrap;
//     this->Update = false;
// }

// void Entity::drawCubeFaces(Vector* p, const uint32_t c, bool light)
// {
//     uint32_t col = c;
//     float shade;
//     Vector normal;
//     for(int i=0;i<4;i++)
//     {
//         //facing camera (normal.z < 0)
//         col = c;
//         normal = Vector::Normal(p[i], p[(i+1)%4], p[(i+1)%4+4]);
//         if (light)
//         {
//             shade = (normal.ScalarProd(this->lightDirection)/3)+0.5;
//             col = sprite->alphaBlend(shade*255,col, TFT_BLACK);
//         }
//         if (normal.z > 0)
//         {
//             if (O.z > 500 && O.z < 1500)
//                 col = sprite->alphaBlend(255 - (O.z - 500)/4,col, *BG_COL);
//             else if (O.z >= 1500)
//                 col = *BG_COL;
//             sprite->fillTriangle(p[i].x, p[i].y, p[(i+1)%4].x, p[(i+1)%4].y, p[(i+1)%4+4].x, p[(i+1)%4+4].y, col);
//             sprite->fillTriangle(p[i].x, p[i].y, p[i+4].x,p[i+4].y, p[(i+1)%4+4].x, p[(i+1)%4+4].y, col);
//         }
//     }
//     col = c;
//     normal = Vector::Normal(p[1], p[0], p[2]);
//     if (light)
//     {
//         shade = (normal.ScalarProd(this->lightDirection)/3)+0.5;
//         col = sprite->alphaBlend(shade*255,col, TFT_BLACK);
//     }
//     if (normal.z > 0)
//     {
//         if (O.z > 500 && O.z < 1500)
//             col = sprite->alphaBlend(255 - (O.z - 500)/4,col, *BG_COL);
//         else if (O.z >= 1500)
//             col = *BG_COL;
//         sprite->fillTriangle(p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y, col);
//         sprite->fillTriangle(p[0].x, p[0].y, p[3].x, p[3].y, p[2].x, p[2].y, col);
//     }
    
//     col = c;
//     normal = Vector::Normal(p[5], p[6], p[4]);
//     if (light)
//     {
//         shade = (normal.ScalarProd(this->lightDirection)/3)+0.5;
//         col = sprite->alphaBlend(shade*255,col, TFT_BLACK);
//     }
//     if (normal.z > 0)
//     {
//         if (O.z > 500 && O.z < 1500)
//             col = sprite->alphaBlend(255 - (O.z - 500)/4,col, *BG_COL);
//         else if (O.z >= 1500)
//             col = *BG_COL;
//         sprite->fillTriangle(p[4].x, p[4].y, p[5].x, p[5].y, p[6].x, p[6].y, col);
//         sprite->fillTriangle(p[4].x, p[4].y, p[7].x, p[7].y, p[6].x, p[6].y, col);
//     }
// }

void Entity::drawCube()
{
    drawCube(Size.x);
}
void Entity::drawCube(float a)
{
    this->Size.x = a;
    this->Size.y = a;
    this->Size.z = a;
    drawParallelepiped();
}
void Entity::drawParallelepiped(Vector v)
{
    this->Size.x = v.x;
    this->Size.y = v.y;
    this->Size.z = v.z;
    drawParallelepiped();
}

// void Entity::drawParallelepiped()
// {
//     if (!isToUpdate())
//         return;

//     Vector o = O.Delta(Camera.x, Camera.y);
//     Vector last_o = last_O.Delta(last_Camera.x, last_Camera.y);
//     o.Round();
//     last_o.Round();

//     //split render to 2 sprites
//     bool split = abs(o.x - last_o.x) > 200 || abs(o.y - last_o.y) > 200;

//     const uint16_t n = 8;
    
//     minp.Equals(999,999), maxp.Equals(-999,-999);   
                                        
//         //          4----------5         
//         //        /          / |        
//         //     /          /    |         
//         //   0----------1      |         
//         //   |      7   |      6      
//         //   |          |    /           
//         //   |          | /          
//         //   3----------2                
                                        
//     Vector last_p[n];
//     last_p[0].Equals(-last_Size.x/2, -last_Size.y/2, last_Size.z/2);
//     last_p[1].Equals(last_Size.x/2, -last_Size.y/2, last_Size.z/2);
//     last_p[2].Equals(last_Size.x/2, last_Size.y/2, last_Size.z/2);
//     last_p[3].Equals(-last_Size.x/2, last_Size.y/2, last_Size.z/2);
//     last_p[4].Equals(-last_Size.x/2, -last_Size.y/2, -last_Size.z/2);
//     last_p[5].Equals(last_Size.x/2, -last_Size.y/2, -last_Size.z/2);
//     last_p[6].Equals(last_Size.x/2, last_Size.y/2, -last_Size.z/2);
//     last_p[7].Equals(-last_Size.x/2, last_Size.y/2, -last_Size.z/2);
    
//     for (int i = 0; i < n; i++)
//     {
//         last_p[i].Rotate(last_Angle);
//         last_p[i].Round();
//         toFOV_XY(&last_p[i], *last_FOV, last_o, o);
//         last_p[i].Round();

//         if(last_p[i].x < minp.x)
//             minp.x = last_p[i].x;
//         else if(last_p[i].x > maxp.x)
//             maxp.x = last_p[i].x;
//         if(last_p[i].y < minp.y)
//             minp.y = last_p[i].y;
//         else if(last_p[i].y > maxp.y)
//             maxp.y = last_p[i].y;
//     }

//     // if (split)
//     // {
//     //     this->createSprite(abs(maxp.x - minp.x) + 1, abs(maxp.y - minp.y) + 1);
//     //     this->sprite->setOrigin(-minp.x, -minp.y);
        
//     //     sprite->setTextWrap(last_textWrap);
//     //     Vector pos = Vector(last_textOffSet.x, last_textOffSet.y, -last_Size.z/2);
//     //     toFOV_XY(&pos, *last_FOV, last_o, o);
//     //     for(uint8_t i = 0; i < 3; i++)
//     //     {
//     //         pos.y += 15*(last_textSize + 1)*(int)(i>0);
//     //         print(last_Text[i], pos, (1-last_o.z/200)*(last_textSize), *BG_COL);
//     //     }
//     //     /*this->print(last_Text[0], Vector2(pos), (1-last_o.z/200)*last_textSize, *BG_COL);
//     //     this->print(last_Text[1], Vector2(pos.x, pos.y + 15*(last_textSize + 1)), (1-last_o.z/200)*last_textSize, *BG_COL);
//     //     this->print(last_Text[2], Vector2(pos.x, pos.y + 30*(last_textSize + 1)), (1-last_o.z/200)*last_textSize, *BG_COL);
//     //     */drawCubeFaces(last_p, *BG_COL, false);

//     //     sprite->pushSprite(o.x + minp.x, o.y + minp.y, TFT_TRANSPARENT);
//     //     sprite->deleteSprite();
//     //     minp.Equals(999,999), maxp.Equals(-999,-999);
//     // }

//     Vector p[n];
//     p[0].Equals(-Size.x/2, -Size.y/2, Size.z/2);
//     p[1].Equals(Size.x/2, -Size.y/2, Size.z/2);
//     p[2].Equals(Size.x/2, Size.y/2, Size.z/2);
//     p[3].Equals(-Size.x/2, Size.y/2, Size.z/2);
//     p[4].Equals(-Size.x/2, -Size.y/2, -Size.z/2);
//     p[5].Equals(Size.x/2, -Size.y/2, -Size.z/2);
//     p[6].Equals(Size.x/2, Size.y/2, -Size.z/2);
//     p[7].Equals(-Size.x/2, Size.y/2, -Size.z/2);
    
//     for (int i =0; i<n;i++)
//     {
//         p[i].Rotate(Angle);
//         p[i].Round();
//         toFOV_XY(&p[i], *FOV, o);
//         p[i].Round();

//         if(p[i].x < minp.x)
//             minp.x = p[i].x;
//         else if(p[i].x > maxp.x)
//             maxp.x = p[i].x;
//         if(p[i].y < minp.y)
//             minp.y = p[i].y;
//         else if(p[i].y > maxp.y)
//             maxp.y = p[i].y;
//     }
    
//     //draw
//     //this->createSprite(abs(maxp.x - minp.x) + 1, abs(maxp.y - minp.y) + 1);
//     this->sprite->setOrigin(-minp.x, -minp.y);

//     if (!split)
//     {
//         sprite->setTextWrap(last_textWrap);
//         Vector pos = Vector(last_textOffSet.x, last_textOffSet.y, -last_Size.z/2);
//         toFOV_XY(&pos, *last_FOV, last_o, o);
//         for(uint8_t i = 0; i < 3; i++)
//         {
//             pos.y += 15*(textSize + 1)*(int)(i>0);
//             print(last_Text[i], pos, (1-last_o.z/200)*(last_textSize), *BG_COL);
//         }
//         drawCubeFaces(last_p, *BG_COL, false);
//     }
//     drawCubeFaces(p, Color, true);
//     sprite->setTextWrap(textWrap);
//     Vector pos = Vector(textOffSet.x, textOffSet.y, -Size.z/2);
//     toFOV_XY(&pos, *FOV, o);
//     for(uint8_t i = 0; i < 3; i++)
//     {
//         pos.y += 15*(textSize + 1)*(int)(i>0);
//         print(Text[i], pos, (1-o.z/200)*(textSize), textColor);
//     }
//     /*this->print(Text[0], Vector2(pos.x, pos.y), (1-o.z/200)*textSize, textColor);
//     this->print(Text[1], Vector2(pos.x, pos.y + 15*(textSize + 1)), (1-o.z/200)*textSize, textColor);
//     this->print(Text[2], Vector2(pos.x, pos.y + 30*(textSize + 1)), (1-o.z/200)*textSize, textColor);*/
        
//     //sprite->pushSprite(o.x + minp.x, o.y + minp.y, TFT_TRANSPARENT);
//     //sprite->deleteSprite();

//     endDraw();
// }

// void Entity::print(String s, Vector2 pos, float z, uint32_t c)
// {
//     if (s == "")
//         return;
//     this->sprite->setTextColor(c);
//     if (z == 0)
//     {
//         sprite->setTextSize(1);
//         this->sprite->drawString(s, pos.x, pos.y, 1);
//         return;
//     }
//     uint8_t font = 1;
//     sprite->setTextSize((int)z + 1);
//     sprite->drawString(s, pos.x + int((z - int(z))*2) * (int)(z + 1), pos.y, font);
//     sprite->drawString(s, pos.x - int((z - int(z))*2) * (int)(z + 1), pos.y, font);
//     sprite->drawString(s, pos.x, pos.y + int((z - int(z))*2) * (int)(z + 1), font);
//     sprite->drawString(s, pos.x, pos.y - int((z - int(z))*2) * (int)(z + 1), font);
    
// }

// void Entity::drawString()
// {
//     if (!isToUpdate())
//         return;

//     Vector o = O.Delta(Camera.x, Camera.y);
//     Vector last_o = last_O.Delta(last_Camera.x, last_Camera.y);
//     o.Round();
//     last_o.Round();
//     Size.Round();
//     int deltaX = (int)(o.x - last_o.x);
//     int deltaY = (int)(o.y - last_o.y);

//     //split render to 2 sprites
//     bool split = abs(deltaX) > Size.x || abs(deltaY) > Size.y;
//     if (split)
//     {
//         createSprite(last_Size.x, last_Size.y);
//         sprite->setOrigin(last_Size.x/2, 0);
        
//         sprite->fillSprite(*BG_COL);
//         //sprite->setTextWrap(last_textWrap);
//         //Vector pos = Vector(last_textOffSet.x /*- (last_o.x - o.x)*/, last_textOffSet.y /*- (last_o.y - o.y)*/);
//         //for(uint8_t i = 0; i < 3; i++)
//         {
//             //pos.y += 15*last_textSize*i;
//             //print(last_Text[i], pos, (1-last_o.z/200)*last_textSize, *BG_COL);
//         }
        
//         sprite->pushSprite(last_o.x - last_Size.x/2, last_o.y - last_Size.y/2, TFT_TRANSPARENT);
//         sprite->deleteSprite();
//     }  

//     //draw
//     createSprite(Size.x + abs(deltaX), Size.y + abs(deltaY));
//     if (deltaX < 0)
//         deltaX = 0;
//     if (deltaY < 0)
//         deltaY = 0;
//     sprite->setOrigin(Size.x/2 + deltaX, deltaY);
//     if (!split)
//     {
//         sprite->fillSprite(*BG_COL);
//         /*sprite->setTextWrap(last_textWrap);
        
//         Vector pos = Vector(last_textOffSet.x + int(last_o.x - o.x), last_textOffSet.y + int(last_o.y - o.y));
//         for(uint8_t i = 0; i < 3; i++)
//         {
//             pos.y += 15*last_textSize*(int)(i>0);
//             print(last_Text[i], pos, (1-last_o.z/200)*last_textSize, *BG_COL);
//         }*/
//     }
//     sprite->setTextWrap(textWrap);
//     Vector pos = Vector(textOffSet.x, textOffSet.y);
//     //toFOV_XY(&pos, *FOV, o);
//     for(uint8_t i = 0; i < 3; i++)
//     {
//         pos.y += 15*textSize*(int)(i>0);
//         print(Text[i], pos, (1-o.z/200)*textSize, textColor);
//     }
//     sprite->pushSprite(o.x - (Size.x/2) - deltaX, o.y - (Size.y/2) - deltaY, TFT_TRANSPARENT);
//     sprite->deleteSprite();

//     endDraw();
// }

// void Entity::drawCircle()
// {
//     if (!isToUpdate())
//         return;

//     Vector o = O.Delta(Camera.x, Camera.y);
//     Vector last_o = last_O.Delta(last_Camera.x, last_Camera.y);
//     o.Round();
//     last_o.Round();
//     Size.Round();
//     int deltaX = (int)(o.x - last_o.x);
//     int deltaY = (int)(o.y - last_o.y);

//     bool split = abs(deltaX) > Size.x || abs(deltaY) > Size.y;
//     if (split)
//     {
//         createSprite(last_Size.x, last_Size.x);
//         sprite->setOrigin(last_Size.x/2, last_Size.x/2);
        
//         sprite->fillSprite(*BG_COL);
        
//         sprite->pushSprite(last_o.x - last_Size.x/2, last_o.y - last_Size.x/2, TFT_TRANSPARENT);
//         sprite->deleteSprite();
//     }

//     //draw
//     createSprite(Size.x + abs(deltaX), Size.y + abs(deltaY));
//     if (deltaX < 0)
//         deltaX = 0;
//     if (deltaY < 0)
//         deltaY = 0;
//     sprite->setOrigin(Size.x/2 + deltaX, deltaY);
//     if (!split)
//         sprite->fillSprite(*BG_COL);

//     Vector pos = Vector(textOffSet.x, textOffSet.y);
//     toFOV_XY(&pos, *FOV, o);
//     sprite->fillCircle(0,0,Size.x/2, Color);

//     sprite->pushSprite(O.x - (Size.x/2), O.y - (Size.x/2), TFT_TRANSPARENT);
//     sprite->deleteSprite();
//     endDraw();
// }