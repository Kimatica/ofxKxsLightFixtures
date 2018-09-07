//
//  MovingHead.cpp
//  virtualFixture
//
//  Created by Nestor Rubio Garcia on 06/04/2018.
//

#include "MovingHead.h"


MovingHead::~MovingHead() { ofLog(OF_LOG_VERBOSE, "MovingHead destroyed"); }

MovingHead::MovingHead() { }

void MovingHead::setup(int address, string name) {
    DmxFixture::setup(address, name);
    
    initFixtureMapping();
    initPanTilt();
}

void MovingHead::initFixtureParameters() {
    parameters.add(panTilt.anglePan);
    parameters.add(panTilt.angleTilt);
}

void MovingHead::initFixtureMapping() {
    // nothing
}

void MovingHead::initPanTilt() {
    panTilt.setRadius(15);
    panTilt.setPanOffset(0,0,0);
    panTilt.setTiltOffset(0,0,0);
}

void MovingHead::setPanMapping(AngleDMXMapping min, AngleDMXMapping max, AngleDMXMapping zero) {
    panTilt.setPanRange(min.angle, max.angle, zero.angle);
    
    panMin_dmx = min.dmx;
    panMax_dmx = max.dmx;
    panZero_dmx = zero.dmx;
}

void MovingHead::setTiltMapping(AngleDMXMapping min, AngleDMXMapping max, AngleDMXMapping zero) {
    panTilt.setTiltRange(min.angle, max.angle, zero.angle);
    
    tiltMin_dmx = min.dmx;
    tiltMax_dmx = max.dmx;
    tiltZero_dmx = zero.dmx;
}

void MovingHead::update() {
    panTilt.update();
    
    pan_dmx = panZero_dmx + (panMax_dmx - panMin_dmx) * panTilt.getPanPct();
    tilt_dmx = tiltZero_dmx + (tiltMax_dmx - tiltMin_dmx) * panTilt.getTiltPct();
}

void MovingHead::setTransform(ofVec3f position, float angle, ofVec3f rotAxis) {
    ofMatrix4x4 translation = ofMatrix4x4::newTranslationMatrix(position);
    ofMatrix4x4 rotation = ofMatrix4x4::newRotationMatrix(angle, rotAxis);
    panTilt.setTransform(rotation * translation); // (oF premult) transformations happen from left to right
}

void MovingHead::setTransform(ofMatrix4x4 transform) {
    panTilt.setTransform(transform);
}

const ofMatrix4x4& MovingHead::getTransform() {
    return panTilt.getTransform();
}

void MovingHead::draw() {
    panTilt.draw();
}

void MovingHead::initDrawing() {
    // nothing
}

string MovingHead::getMappingInfoString() {
    string str;
    str += "           Angle    DMX \n";
    str += "Pan min:   ";
    str += ofToString(panTilt.getPanMin(), 0, 4, ' ') + "  |  " + ofToString(panMin_dmx) + "\n";
    str += "Pan max:   ";
    str += ofToString(panTilt.getPanMax(), 0, 4, ' ') + "  |  " + ofToString(panMax_dmx) + "\n";
    str += "Pan zero:  ";
    str += ofToString(panTilt.getPanZero(), 0, 4, ' ') + "  |  " + ofToString(panZero_dmx) + "\n";
    str += "Tilt min:  ";
    str += ofToString(panTilt.getTiltMin(), 0, 4, ' ') + "  |  " + ofToString(tiltMin_dmx) + "\n";
    str += "Tilt max:  ";
    str += ofToString(panTilt.getTiltMax(), 0, 4, ' ') + "  |  " + ofToString(tiltMax_dmx) + "\n";
    str += "Tilt zero: ";
    str += ofToString(panTilt.getTiltZero(), 0, 4, ' ') + "  |  " + ofToString(tiltZero_dmx) + "\n";
    return str;
}
