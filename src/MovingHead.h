//
//  MovingHead.hpp
//  virtualFixture
//
//  Created by Nestor Rubio Garcia on 06/04/2018.
//
//  ---
//  Fusion Spot MKII
//  8 channels DMX mode
//

#pragma once

#include "ofMain.h"
#include "PanTilt.h"
#include "DmxFixture.h"


class AngleDMXMapping {
public:
    float angle;
    int dmx;
    AngleDMXMapping(float angle, int dmx) {
        this->angle = angle;
        this->dmx = dmx;
    }
};


class MovingHead : public DmxFixture {
    
public:
    MovingHead();
    ~MovingHead();
    
    void setup(int address, string name) override;
    void update() override;
    void draw() override;
    
    // angle to dmx
    void setTiltMapping(AngleDMXMapping min, AngleDMXMapping max, AngleDMXMapping zero);
    void setPanMapping(AngleDMXMapping min, AngleDMXMapping max, AngleDMXMapping zero);
    
    // hide these methods from DmxFixture (hacky but works for the time being
    void setTransform(ofVec3f position, float angle, ofVec3f rotAxis);
    void setTransform(ofMatrix4x4 transform);
    const ofMatrix4x4& getTransform();
    
    string getMappingInfoString();
    
protected:
    PanTilt panTilt;
    
    // current pan/tilt dmx
    int pan_dmx;
    int tilt_dmx;
    
    // ranges dmx
    int panMin_dmx;
    int panMax_dmx;
    int panZero_dmx;
    int tiltMin_dmx;
    int tiltMax_dmx;
    int tiltZero_dmx;
    
    virtual void initPanTilt();
    virtual void initFixtureMapping();  // mapping between angles and dmx values
    void initFixtureParameters() override;
    void initDrawing() override;
};
