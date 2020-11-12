//
//  StarvilleFloodPanel150.h
//  lightFixtures-osc
//
//  Created by Nestor Rubio Garcia on 26/09/2019.
//

#pragma once

#include "DmxFixture.h"


class StarvilleFloodPanel150 : public DmxFixture {
    
public:
    StarvilleFloodPanel150();
    ~StarvilleFloodPanel150();
    
    void update() override;
    void draw() override;
    
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    ofParameter<float> strobe; // 0 = no strobe, >0 = slow-fast
    
private:
    void initFixtureParameters() override;
    void initDrawing() override;
};
