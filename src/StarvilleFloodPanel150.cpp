#include "StarvilleFloodPanel150.h"


StarvilleFloodPanel150::~StarvilleFloodPanel150() { ofLog(OF_LOG_VERBOSE, "StarvilleFloodPanel150 destroyed"); }

StarvilleFloodPanel150::StarvilleFloodPanel150() {
    channels.resize(8);
    
    // smoothing
    channelsSmooth.resize(channels.size());
    for (int i = 0; i < channels.size(); i++) {
        smoothers.push_back( Smoother( channels[i], channelsSmooth[i]));
    }
    smoothers[4].bypass = true; // do not smooth strobe
}

void StarvilleFloodPanel150::update() {
    channels[0] = dimmer * 255;             // dimmer
    channels[1] = red * 255;                // red
    channels[2] = green * 255;              // green
    channels[3] = blue * 255;               // blue
    channels[4] = 9 + ((255 - 9) * strobe); // strobe (10-255 = slow-fast)
    channels[5] = 0;                        // color mode
    channels[6] = 0;
    channels[7] = 0;
    
    smoothChannels();
}

void StarvilleFloodPanel150::initFixtureParameters() {
    parameters.add( red.set("red", 0, 0, 1));
    parameters.add( green.set("green", 0, 0, 1));
    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 0, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
}
