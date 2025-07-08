
// --
// Led flat par RGBAW+UV
// 10 channels mode
//

#pragma once

#include "DmxFixture.h"


class PrashPar : public DmxFixture {
    
public:
    PrashPar();
    ~PrashPar();
    
    void update() override;
    
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    ofParameter<float> white;
    ofParameter<float> amber;
    ofParameter<float> uv;
    ofParameter<float> strobe;
    
private:
    void initFixtureParameters() override;
};

