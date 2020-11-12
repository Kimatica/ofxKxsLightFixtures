#pragma once

#include "DmxFixture.h"


class Dimmer : public DmxFixture {
    
public:
    Dimmer();
    ~Dimmer();
    
    void update() override;
    void draw() override;
    
private:
    void initFixtureParameters() override;
    void initDrawing() override;
};

