
#pragma once

#include "ofMain.h"

class Smoother {
public:
    Smoother(int& _input, int& _output)
    : input(_input)
    , output(_output)
    , bypass(false)
    {}
    void update(float smoothing) {
        if (!bypass) {
            smooth += float(input - smooth) * smoothing;
            output = int(smooth);
        }
        else {
            output = input;
        }
    }
    bool bypass;
private:
    int& input;
    int& output;
    float smooth;
};


class DmxFixture {
    
public:
    DmxFixture();
    // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
    virtual ~DmxFixture();
    
    ofParameterGroup parameters;
    ofParameter<float> dimmer;
    ofParameter<float> smoothing;
    
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
    
    vector<int> channelsSmooth;
    vector<Smoother> smoothers;
    void smoothChannels();
    
    virtual void initFixtureParameters() = 0;
    virtual void initDrawing() = 0;
    
    ofMatrix4x4 transform;
};
