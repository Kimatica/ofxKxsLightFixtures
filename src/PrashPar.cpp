#include "PrashPar.h"


PrashPar::~PrashPar() { ofLog(OF_LOG_VERBOSE, "PrashPar destroyed"); }

PrashPar::PrashPar() {
    channels.resize(10);
    
    // smoothing
    channelsSmooth.resize(channels.size());
    for (int i = 0; i < channels.size(); i++) {
        smoothers.push_back( Smoother( channels[i], channelsSmooth[i]));
    }
    smoothers[7].bypass = true; // do not smooth strobe
}

void PrashPar::update() {
    channels[0] = dimmer * 255;             // dimmer
    channels[1] = red * 255;                // red
    channels[2] = green * 255;              // green
    channels[3] = blue * 255;               // blue
    channels[4] = 0;                        // white
    channels[5] = 0;                        // amber
    channels[6] = uv * 255;                 // uv
    channels[7] = 5 + ((255-5) * strobe);   // strobe (5-255 - slow>fast)
    channels[8] = 0;
    channels[9] = 0;
    
    smoothChannels();
}

void PrashPar::initFixtureParameters() {
    parameters.add( red.set("red", 0, 0, 1));
    parameters.add( green.set("green", 0, 0, 1));
    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( uv.set("uv", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
    parameters.add( smoothing.set("smoothing", 1, 0, 1));
}
