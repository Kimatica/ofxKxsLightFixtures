//
// Chauvet ColorbandPix
// 7 channels mode
//

#pragma once

#include "ofMain.h"
#include "DmxFixture.h"


class ChauvetColorBandPix : public DmxFixture {
    
public:
    ChauvetColorBandPix();
    ~ChauvetColorBandPix();
    
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
