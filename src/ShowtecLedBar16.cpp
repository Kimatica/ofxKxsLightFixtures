//
//  ShowtecLedBar.cpp
//  dmxAdjMegaTriparProfile
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//

#include "ShowtecLedBar16.h"


ShowtecLedBar16::~ShowtecLedBar16() { ofLog(OF_LOG_VERBOSE, "ShowtecLedBar16 destroyed"); }
    
ShowtecLedBar16::ShowtecLedBar16() {
    channels.resize(5);
    
    // smoothing
    channelsSmooth.resize(channels.size());
    for (int i = 0; i < channels.size(); i++) {
        smoothers.push_back( Smoother( channels[i], channelsSmooth[i]));
    }
    smoothers[4].bypass = true; // do not smooth strobe
}

void ShowtecLedBar16::update() {
    channels[0] = red * 255;       // red
    channels[1] = green * 255;     // green
    channels[2] = blue * 255;      // blue
    channels[3] = dimmer * 255;    // dimmer
    //channels[4] = (strobe < 1) ? 10 + strobe * 245 : 0;  // strobe
    channels[4] = 2 + ((255 - 2) * strobe);  // strobe (3-255 = slow-fast)
    
    smoothChannels();
}

void ShowtecLedBar16::initFixtureParameters() {
    //parameters.add( color.set("color", ofFloatColor(0,0.3,0,1), ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1)));
    parameters.add( red.set("red", 0, 0, 1));
    parameters.add( green.set("green", 0, 0, 1));
    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
    parameters.add( smoothing.set("smoothing", 1, 0, 1));
}

void ShowtecLedBar16::initDrawing() {
    // TODO
}

void ShowtecLedBar16::draw() {
    // default unit is cm
    float width = 100;
    float depth = 7;
    ofFloatColor c(red*dimmer, green*dimmer, blue*dimmer);
    
    ofPushStyle();
    ofPushMatrix();
    {
        ofMultMatrix(transform);
        
        ofDrawAxis(8);
        
        // back
        ofSetColor(ofColor::dimGrey);
        ofDrawBox(0, 0, 0, width, depth, depth);
        
        // front
        if (strobe > 0.f) {
            float blinkFreq = strobe * 50.f;
            float blink = 0.5f + sin(ofGetElapsedTimef() * blinkFreq) * 0.5f; //0..1
            blink = blink > 0.8f ? 1.f : 0.f;
            c.set(c.r * blink, c.g * blink, c.b * blink);
        }
        ofSetColor(c);
        ofDrawRectangle(-width*0.5+1, -depth*0.5+1, depth*0.5+0.01, width-2, depth-2);
    }
    ofPopMatrix();
    ofPopStyle();
}
