//
//  DmxFixture
//  dmxAdjMegaTriparProfile
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//

#pragma once

#include "ofMain.h"

class DmxFixture {
    
public:
    DmxFixture();
    // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
    virtual ~DmxFixture();
    
    ofParameterGroup parameters;
    ofParameter<float> dimmer;
    
    virtual void setup(int address, string name);
    virtual void update() = 0;
    virtual void draw() = 0;
    
    const vector<int> & getChannels();
    const int getNumChannels();
    const string getName();
    const int getAddress();
    
    void setTransform(ofVec3f position, float angle, ofVec3f rotAxis);
    void setTransform(ofMatrix4x4 transform);
    
    const ofMatrix4x4& getTransform();
    
protected:
    int address;
    vector<int> channels;
    
    virtual void initFixtureParameters() = 0;
    virtual void initDrawing() = 0;
    
    ofMatrix4x4 transform;
};
