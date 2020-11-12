//
//  AdjTriparProfile.cpp
//  dmxAdjMegaTriparProfile
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//

#include "AdjTriparProfile.h"


AdjTriparProfile::~AdjTriparProfile() { ofLog(OF_LOG_VERBOSE, "AdjTriparProfile destroyed"); }

AdjTriparProfile::AdjTriparProfile() {
    channels.resize(6);
    
    // smoothing
    channelsSmooth.resize(channels.size());
    for (int i = 0; i < channels.size(); i++) {
        smoothers.push_back( Smoother( channels[i], channelsSmooth[i]));
    }
    smoothers[4].bypass = true; // do not smooth strobe
}

void AdjTriparProfile::update() {
    channels[0] = red * 255;                  // red
    channels[1] = green * 255;                // green
    channels[2] = blue * 255;                 // blue
    channels[3] = 0;                          // colorMacro
    channels[4] = 15 + ((255 - 15) * strobe); // strobe (16-255 = slow-fast)
    channels[5] = dimmer * 255;               // dimmer
    
    smoothChannels();
}

void AdjTriparProfile::initFixtureParameters() {
    //parameters.add( color.set("color", ofFloatColor(0,0.3,0,1), ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1)));
    parameters.add( red.set("red", 0, 0, 1));
    parameters.add( green.set("green", 0, 0, 1));
    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
    //parameters.add( smoothing.set("smoothing", 1, 0, 1));
}

void AdjTriparProfile::initDrawing() {
    // TODO
}

void AdjTriparProfile::draw() {
    // default unit is cm
    float radius = 9;
    float depth = 8;
    ofFloatColor c(red*dimmer, green*dimmer, blue*dimmer);
    
    ofPushStyle();
    ofPushMatrix();
    {
        ofMultMatrix(transform);
        
        ofDrawAxis(8);
        
        // back
        ofSetColor(ofColor::dimGrey);
        ofDrawCircle(0, 0, depth - 0.01, radius);
        
        // front
        if (strobe > 0.f) {
            float blinkFreq = strobe * 50.f;
            float blink = 0.5f + sin(ofGetElapsedTimef() * blinkFreq) * 0.5f; //0..1
            blink = blink > 0.8f ? 1.f : 0.f;
            c.set(c.r * blink, c.g * blink, c.b * blink);
        }
        ofSetColor(c);
        ofDrawCircle(0, 0, depth, radius-1);
    }
    ofPopMatrix();
    ofPopStyle();
}
