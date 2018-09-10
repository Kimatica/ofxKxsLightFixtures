//
//  PrashPar.cpp
//  dmxAdjMegaTriparProfile
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//

#include "PrashPar.h"


PrashPar::~PrashPar() { ofLog(OF_LOG_VERBOSE, "PrashPar destroyed"); }

PrashPar::PrashPar() {
    channels.resize(10);
}

void PrashPar::update() {
    channels[0] = dimmer * 255;             // dimmer
    channels[1] = red * 255;                // red
    channels[2] = green * 255;              // green
    channels[3] = blue * 255;               // blue
    channels[4] = 0;                        // white
    channels[5] = 0;                        // amber
    channels[6] = uv * 255;                 // blue
    channels[7] = 5 + ((255-5) * strobe);   // strobe (5-255 - slow>fast)
    channels[8] = 0;
    channels[9] = 0;
}

void PrashPar::initFixtureParameters() {
    parameters.add( red.set("red", 0, 0, 1));
    parameters.add( green.set("green", 0, 0, 1));
    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( uv.set("uv", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
}

void PrashPar::initDrawing() {
    // TODO
}

void PrashPar::draw() {
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

