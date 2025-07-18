//
// AmericanDJ Mega Tripar Profile PLUS (RGB+UV)
// 6 channel mode
//

#pragma once

#include "DmxFixture.h"


class AdjTriparProfilePlus : public DmxFixture {
    
public:
    AdjTriparProfilePlus();
    ~AdjTriparProfilePlus();
    
    void update() override;
    
    //ofParameter<ofFloatColor> color; // r, g, b, dimmer
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    //ofParameter<float> dimmer;
    ofParameter<float> uv;
    ofParameter<float> strobe;
    
private:    
    void initFixtureParameters() override;
};

