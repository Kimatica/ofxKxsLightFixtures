//
// Showtec LED Light Bar 16 Mega Tripar Profile (RGB)
// 5 channel mode (2c_5)
//

#pragma once

#include "ofMain.h"
#include "DmxFixture.h"


class ShowtecLedBar16 : public DmxFixture {
    
public:
    ShowtecLedBar16();
    ~ShowtecLedBar16();
    
    void update() override;

    //ofParameter<ofFloatColor> color; // r, g, b, dimmer
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    //ofParameter<float> dimmer;
    ofParameter<float> strobe;
    
private:    
    void initFixtureParameters() override;
};
