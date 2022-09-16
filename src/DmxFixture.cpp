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
    // providing better performance
    parameters.setName(name);
    
    initFixtureParameters();
    initDrawing();
}

const vector<int> & DmxFixture::getChannels() {
    if (channelsSmooth.size() == 0) {
        return channels;
    } else {
        return channelsSmooth;
    }
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

void DmxFixture::setGridPosition(glm::vec2 pos)
{
    gridPosition = pos;
}

const glm::vec2 DmxFixture::getGridPosition()
{
    return gridPosition;
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

void DmxFixture::smoothChannels() {
//    for (int i = 0; i < channels.size(); i++) {
//        int& target = channels[i];
//        float& buffer = smoothingBuffer[i];
//        buffer += float(target - buffer) * smoothing;
//        channelsSmooth[i] = buffer;
//    }
    for(auto& smoother : smoothers) {
        smoother.update(smoothing);
    }
}
