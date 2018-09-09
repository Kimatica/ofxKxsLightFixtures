//
//  UVPanel.cpp
//  dmxUVPanel
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//

#include "UVPanel.h"

UVPanel::~UVPanel() { ofLog(OF_LOG_VERBOSE, "UVPanel destroyed"); }

UVPanel::UVPanel() {
    channels.resize(3);
}

void UVPanel::update() {
//    channels[0] = red * 255;              // red
//    channels[1] = green * 255;            // green
//    channels[2] = blue * 255;             // blue
    channels[0] = 0;                        // function
    channels[1] = strobe * 255;             // strobe (0-255 = slow-fast)
    channels[2] = 255 - (dimmer * 254);   // dimmer (255 - 0)
}

void UVPanel::initFixtureParameters() {
    //parameters.add( color.set("color", ofFloatColor(0,0.3,0,1), ofFloatColor(0,0,0,0), ofFloatColor(1,1,1,1)));
//    parameters.add( red.set("red", 0, 0, 1));
//    parameters.add( green.set("green", 0, 0, 1));
//    parameters.add( blue.set("blue", 0, 0, 1));
    parameters.add( dimmer.set("dimmer", 1, 0, 1));
    parameters.add( strobe.set("strobe", 0, 0, 1));
}

void UVPanel::initDrawing() {
    // TODO
}

void UVPanel::draw() {
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

