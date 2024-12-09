#ifndef _TSCENE_
#define _TSCENE_

#include <lowPoly.h>
#include <vector>
//#include <LowPoly.h>


class Tscene : public Scene {
private:
    std::vector<Vector> vertices;

    void addVertex(Vector v);
    void clearVertices();
    
public:
    void update(float deltaTime) override;
    void render() override;
    void enter() override;
    void exit() override;
};

#endif