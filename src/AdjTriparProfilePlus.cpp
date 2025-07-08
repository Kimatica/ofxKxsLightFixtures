//
//  AdjTriparProfilePlus.cpp
//  dmxAdjMegaTriparProfile
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//

#include "AdjTriparProfilePlus.h"


AdjTriparProfilePlus::~AdjTriparProfilePlus() { ofLog(OF_LOG_VERBOSE, "AdjTriparProfilePlus destroyed"); }

AdjTriparProfilePlus::AdjTriparProfilePlus() {
    channels.resize(6);
    
    // smoothing
    channelsSmooth.resize(channels.size());
    for (int i = 0; i < channels.size(); i++) {
        smoothers.push_back( Smoother( channels[i], channelsSmooth[i]));
    }
    smoothers[4].bypass = true; // do not smooth strobe
}

void AdjTriparProfilePlus::update() {
    channels[0] = red * 255;          // red
    channels[1] = green * 255;        // green
    channels[2] = blue * 255;         // blue
    channels[3] = uv * 255;           // uv
    channels[4] = (strobe > 0.f) ? 64 + (31 * strobe) : 63; // strobe (64-95 = slow-fast)
    channels[5] = dimmer * 255;       // dimmer
    
    smoothChannels();
}

void AdjTriparProfilePlus::initFixtureParameters() {
    //parameters.add( color.set("color", ofFloatColor(0,0.3,0,1), ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1)));
    parameters.add( red.set("red", 0, 0, 1));
    parameters.add( green.set("green", 0, 0, 1));
    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( uv.set("uv", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
    parameters.add( smoothing.set("smoothing", 1, 0, 1));
}
