//
// Led light tube
// 3 channels
// TODO: investigate more channel modes
//

#pragma once

#include "DmxFixture.h"


class YcOnionEnergyTubePro : public DmxFixture {
    
public:
    ofParameter<float> dimmer;
    ofParameter<float> hue;
    ofParameter<float> saturation;
    
    ~YcOnionEnergyTubePro() {
    }
    
    YcOnionEnergyTubePro() {
        channels.resize(3);

        // smoothing
        // NOTE: channelsSmooth.size() must be = channels.size()
        // TODO: create a Channel class that replaces the raw vector<int> variable
        // so each channel directly supports smoothing without additional overhead
        // channelsSmooth.resize(channels.size());
        // for (int i = 0; i < channels.size(); i++) {
        //     smoothers.push_back( Smoother(channels[i], channelsSmooth[i]));
        //     // only smooth dimmer
        //     smoothers.back().bypass = (i != 0);
        // }
    }
    
    void update() override {
        channels[0] = dimmer * 255;
        channels[1] = hue * 255;
        channels[2] = saturation * 255;

        // smoothChannels();
    }
    
private:
    void initFixtureParameters() override {
        parameters.add(dimmer.set("dimmer", 1, 0, 1));
        parameters.add(hue.set("hue", 0, 0, 1));
        parameters.add(saturation.set("saturation", 1, 0, 1));
        parameters.add(smoothing.set("smoothing", 1, 0, 1));
    }
};
