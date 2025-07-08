#pragma once
#include "DmxFixture.h"

class MiniPar : public DmxFixture {
public:
    ofParameter<float> red;
    ofParameter<float> green;
    ofParameter<float> blue;
    ofParameter<float> white;

    ~MiniPar() {
    }

    MiniPar() {
        channels.resize(4);
    }
    
    void update() override {
        channels[0] = red * 255;
        channels[1] = green * 255;
        channels[2] = blue * 255;
        channels[3] = white * 255;
    }

private:

    void initFixtureParameters() override {
        parameters.add(red.set("red", 0, 0, 1));
        parameters.add(green.set("green", 0, 0, 1));
        parameters.add(blue.set("blue", 0, 0, 1));
        parameters.add(white.set("white", 0, 0, 1));

		parametersColor.add(red, green, blue, white);
    }
};
