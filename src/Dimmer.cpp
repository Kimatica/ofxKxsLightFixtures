
#include "Dimmer.h"


#include "Dimmer.h"


Dimmer::~Dimmer() { ofLog(OF_LOG_VERBOSE, "Dimmer destroyed"); }

Dimmer::Dimmer() {
    channels.resize(1);
    
    // smoothing
    channelsSmooth.resize(channels.size());
    smoothers.push_back( Smoother( channels[0], channelsSmooth[0]));
}

void Dimmer::update() {    
    channels[0] = dimmer * 255;
    
    smoothChannels();
}

void Dimmer::initFixtureParameters() {
    //parameters.add( color.set("color", ofFloatColor(0,0.3,0,1), ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1)));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( smoothing.set("smoothing", 1, 0, 1));
}
