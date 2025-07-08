//
// AmericanDJ Mega Tripar Profile (RGB)
// 6 channel mode
//

#pragma once

#include "DmxFixture.h"

class UVPanel : public DmxFixture {
    
public:
    UVPanel();
    ~UVPanel();
    
    void update() override;
    
    //ofParameter<ofFloatColor> color;    // r, g, b, dimmer
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    //ofParameter<float> dimmer;
    ofParameter<float> uv;
    ofParameter<float> strobe;
    
private:
    void initFixtureParameters() override;
};

