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
}

void AdjTriparProfilePlus::update() {
    channels[0] = red * 255;          // red
    channels[1] = green * 255;        // green
    channels[2] = blue * 255;         // blue
    channels[3] = uv * 255;           // uv
    channels[4] = (strobe > 0.f) ? 64 + (31 * strobe) : 63; // strobe (64-95 = slow-fast)
    channels[5] = dimmer * 255;       // dimmer
}

void AdjTriparProfilePlus::initFixtureParameters() {
    //parameters.add( color.set("color", ofFloatColor(0,0.3,0,1), ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1)));
    parameters.add( red.set("red", 0, 0, 1));
    parameters.add( green.set("green", 0, 0, 1));
    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( uv.set("uv", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
}

void AdjTriparProfilePlus::initDrawing() {
    // TODO
}

void AdjTriparProfilePlus::draw() {
    // default unit is cm
    float radius = 9;
    float depth = 8;
    ofFloatColor c(red*dimmer, green*dimmer, blue*dimmer);
    ofFloatColor cUv(0.47f*uv*dimmer, 0.03f*uv*dimmer, 1.0f*uv*dimmer);
    
    ofPushStyle();
    ofPushMatrix();
    {
        ofMultMatrix(transform);
        
        ofDrawAxis(8);
        
        // back
        ofSetColor(ofColor::dimGrey);
        ofDrawCircle(0, 0, depth-0.01, radius);
        
        // front
        if (strobe > 0.f) {
            float blinkFreq = strobe * 50.f;
            float blink = 0.5f + sin(ofGetElapsedTimef() * blinkFreq) * 0.5f; //0..1
            blink = blink > 0.8f ? 1.f : 0.f;
            c.set(c.r * blink, c.g * blink, c.b * blink);
            cUv.set(cUv.r * blink, cUv.g * blink, cUv.b * blink);
        }
        ofSetColor(c);
        ofDrawCircle(0, 0, depth, radius-1);
        ofSetColor(cUv);
        ofDrawCircle(0, 0, depth+0.01, radius-7);
    }
    ofPopMatrix();
    ofPopStyle();
}
