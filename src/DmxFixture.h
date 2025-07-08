
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
	virtual ~DmxFixture();
    
    ofParameterGroup parameters;
	ofParameterGroup parametersColor;
    ofParameter<float> dimmer;
    ofParameter<float> smoothing; // TODO: remove, smoothing should be in group controller
    
    virtual void setup(int address, string name);
    virtual void update() = 0;
    
    const vector<int> & getChannels();
    const int getNumChannels();
    const string getName();
    const int getAddress();
    
protected:
    int address;
    vector<int> channels;
    
    vector<int> channelsSmooth;
    vector<Smoother> smoothers;
    void smoothChannels();
    
    virtual void initFixtureParameters() = 0;
    
    ofMatrix4x4 transform;
};
