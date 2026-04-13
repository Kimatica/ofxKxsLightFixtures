//
// Equinox UV Power Flood
// 8 channels
//

#pragma once

#include "DmxFixture.h"


class EquinoxUVPowerFlood : public DmxFixture {
    
public:
    ofParameter<float> dimmer; // master
    ofParameter<float> strobe; // slow-fast
    ofParameter<float> dimmerRow1;
    ofParameter<float> dimmerRow2;
    ofParameter<float> dimmerRow3;
    ofParameter<float> dimmerRow4;
    
    ~EquinoxUVPowerFlood() {
    }
    
    EquinoxUVPowerFlood() {
        channels.resize(8);

        // smoothing
        // NOTE: channelsSmooth.size() must be = channels.size()
        // TODO: create a Channel class that replaces the raw vector<int> variable
        // so each channel directly supports smoothing without additional overhead
        channelsSmooth.resize(channels.size());
        for (int i = 0; i < channels.size(); i++) {
            smoothers.push_back( Smoother(channels[i], channelsSmooth[i]));
            // only smooth global dimmer
            smoothers.back().bypass = (i != 0);
        }
    }
    
    void update() override {
        channels[0] = dimmer * 255; // global
        channels[1] = strobe * 255;
        channels[2] = 0; // auto (000-125) sound active (126-255)
        channels[3] = 0; // speed slow-fast
        channels[4] = dimmerRow1 * 255;
        channels[5] = dimmerRow2 * 255;
        channels[6] = dimmerRow3 * 255;
        channels[7] = dimmerRow4 * 255;

        smoothChannels();
    }
    
private:
    void initFixtureParameters() override {
        parameters.add(dimmer.set("dimmer", 1, 0, 1));
        parameters.add(strobe.set("strobe", 0, 0, 1));
        parameters.add(dimmerRow1.set("dimmerRow1", 1, 0, 1));
        parameters.add(dimmerRow2.set("dimmerRow2", 1, 0, 1));
        parameters.add(dimmerRow3.set("dimmerRow3", 2, 0, 1));
        parameters.add(dimmerRow4.set("dimmerRow4", 1, 0, 1));

        smoothing.set("smoothing", 1, 0, 1);
    }
};
