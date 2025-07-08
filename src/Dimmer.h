#pragma once

#include "DmxFixture.h"


class Dimmer : public DmxFixture {
    
public:
    Dimmer();
    ~Dimmer();
    
    void update() override;
    
private:
    void initFixtureParameters() override;
};

