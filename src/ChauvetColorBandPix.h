//
//  ShowtecLedBar.hpp
//  dmxAdjMegaTriparProfile
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//
// --
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
    void draw() override;

    //ofParameter<ofFloatColor> color; // r, g, b, dimmer
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    //ofParameter<float> dimmer;
    ofParameter<float> strobe;
    
private:    
    void initFixtureParameters() override;
    void initDrawing() override;
};
