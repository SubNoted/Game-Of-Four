#ifndef _TSCENE_
#define _TSCENE_

#include <lowPoly.h>

class Tscene : public Scene {
private:

    
public:
    void update(float deltaTime) override;
    void render() override;
    void enter() override;
    void exit() override;
};

#endif