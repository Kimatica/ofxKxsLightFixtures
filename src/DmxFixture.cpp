//
//  DmxFixture.cpp
//  dmxAdjMegaTriparProfile
//
//  Created by Nestor Rubio Garcia on 17/04/2018.
//

#include "DmxFixture.h"


DmxFixture::~DmxFixture() { ofLog(OF_LOG_VERBOSE, "DmxFixture destroyed"); }

DmxFixture::DmxFixture() { }

void DmxFixture::setup(int address, string name) {
    this->address = address;
    
    // NOTE: osc IS NOT case sensitive.
    // TODO: create a scaped version of the name.
    // As a rule of thumb, only scaped addresses are sent from remote sender,
    // this avoids having to deal with scaping strings when osc is updated
    // and provodes better performance
    parameters.setName(name);
    
    initFixtureParameters();
    initDrawing();
}

const vector<int> & DmxFixture::getChannels() {
    return channels;
}

const int DmxFixture::getNumChannels() {
    return channels.size();
}

const string DmxFixture::getName() {
    return parameters.getName();
}

const int DmxFixture::getAddress() {
    return address;
}

void DmxFixture::setTransform(ofVec3f position, float angle, ofVec3f rotAxis) {
    ofMatrix4x4 translation = ofMatrix4x4::newTranslationMatrix(position);
    ofMatrix4x4 rotation = ofMatrix4x4::newRotationMatrix(angle, rotAxis);
    transform = rotation * translation; // (oF premult) transformations happen from left to right
}

void DmxFixture::setTransform(ofMatrix4x4 transform) {
    this->transform = transform;
}

const ofMatrix4x4& DmxFixture::getTransform() {
    return transform;
}
