//
//  AdjTriparProfile.hpp
//  dmxAdjMegaTriparProfile
//
//  Created by Terry Clark on 11/09/2022.
//
// --
// ApeLabs Cans (RGBW)
// 4/8 channel mode
//

#pragma once

#include "DmxFixture.h"


class ApeLabsLightCan : public DmxFixture {

public:
    ApeLabsLightCan();
    ~ApeLabsLightCan();

    void update() override;
    void update(Grid& grid) override;
    void draw() override;

    ofColor RGBToRGBW(float r, float g, float b);
   

    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    ofParameter<float> white;

private:
    void initFixtureParameters() override;
    void initDrawing() override;
};
