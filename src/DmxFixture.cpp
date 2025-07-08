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
