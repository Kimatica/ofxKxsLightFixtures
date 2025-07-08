//
//  MovingHeadDMXControl.cpp
//  pointTracking
//
//  Created by Nestor Rubio Garcia on 13/04/2018.
//

#include "MovingHeadFusionMKII.h"

MovingHeadFusionMKII::~MovingHeadFusionMKII() { ofLog(OF_LOG_VERBOSE, "MovingHeadFusionMKII destroyed"); }

MovingHeadFusionMKII::MovingHeadFusionMKII() {
    channels.resize(8);
}

void MovingHeadFusionMKII::initPanTilt() {
    // TODO: init with actual values
    panTilt.setRadius(10);
    panTilt.setPanOffset(0, 18, 0);
    panTilt.setTiltOffset(0, 0, 0);
}

void MovingHeadFusionMKII::initFixtureMapping() {
    AngleDMXMapping panMin(-90, 212);
    AngleDMXMapping panMax(90, 128);
    AngleDMXMapping panZero(0, 170);    // middle_of_range = min + (max - min) / 2
    AngleDMXMapping tiltMin(-90, 128);
    AngleDMXMapping tiltMax(0, 7);
    AngleDMXMapping tiltZero(0, 7);     // begining_of_range = min
    
    setPanMapping(panMin, panMax, panZero);
    setTiltMapping(tiltMin, tiltMax, tiltZero);
}

void MovingHeadFusionMKII::initFixtureParameters() {
    MovingHead::initFixtureParameters();
    
    // --
    // dmx maps
    colorsMap["white"] = 7;
    colorsMap["light_blue"] = 14;
    colorsMap["pink"] = 21;
    colorsMap["orange"] = 28;
    colorsMap["green"] = 35;
    colorsMap["blue"] = 42;
    colorsMap["yellow"] = 49;
    colorsMap["red"] = 56;
    
    gobosMap["open"] = 7;
    gobosMap["2"] = 15;
    gobosMap["3"] = 23;
    gobosMap["4"] = 31;
    gobosMap["5"] = 39;
    gobosMap["6"] = 47;
    gobosMap["7"] = 55;
    gobosMap["8"] = 63;
    
    functionsMap["null"] = 0;
    functionsMap["black_color_change"] = 99;
    functionsMap["black_gobo_change"] = 119;
    functionsMap["reset"] = 209;
    
    // dmx default values for "radio style" 
    channels[2] = colorsMap["green"];
    channels[3] = gobosMap["open"];
    channels[6] = functionsMap["null"];
    
    // --
    // parameters
    shutter.set("shutter", 1, 0, 1);
    panTiltSpeed.set("move_speed", 1, 0, 1);
    dimmer.set("dimmer", 1, 0, 1);
    
    groupColors.setName("color");
    fillGroupFromMap(colorsMap, groupColors);
    groupColors.get(getFixtureCurrentColor()).cast<bool>().set(true);
    ofAddListener(groupColors.parameterChangedE(), this, &MovingHeadFusionMKII::onColorChange);
    
    groupGobos.setName("gobo");
    fillGroupFromMap(gobosMap, groupGobos);
    groupGobos.get(getFixtureCurrentGobo()).cast<bool>().set(true);
    ofAddListener(groupGobos.parameterChangedE(), this, &MovingHeadFusionMKII::onGoboChange);
    
    groupFunctions.setName("function");
    fillGroupFromMap(functionsMap, groupFunctions);
    groupFunctions.get(getFixtureCurrentFunction()).cast<bool>().set(true);
    ofAddListener(groupFunctions.parameterChangedE(), this, &MovingHeadFusionMKII::onFunctionChange);
    
    // --
    // add parameters
    parameters.add(panTiltSpeed);
    parameters.add(dimmer);
    parameters.add(shutter);
    parameters.add(groupColors);
    parameters.add(groupGobos);
    parameters.add(groupFunctions);
}

void MovingHeadFusionMKII::update() {
    // update pan tilt dmx values
    MovingHead::update();
    
    channels[0] = pan_dmx;                      // pan
    channels[1] = tilt_dmx;                     // tilt
    //channels[2]                               // color
    //channels[3]                               // gobo
    channels[4] = 16 + shutter * (132 - 16);    // shutter
    channels[5] = (1.f - panTiltSpeed) * 255;   // pan/tilt speed
    //channels[6]                               // function
    channels[7] = dimmer * 255;                 // dimmer
}

void MovingHeadFusionMKII::activateColor(string name) {
    channels[2] = colorsMap[name];
    activateParameterInGroup(groupColors, name);
}

void MovingHeadFusionMKII::activateGobo(string name) {
    channels[3] = gobosMap[name];
    activateParameterInGroup(groupGobos, name);
}

void MovingHeadFusionMKII::activateFunction(string name) {
    channels[6] = functionsMap[name];
    activateParameterInGroup(groupFunctions, name);
}

void MovingHeadFusionMKII::setColor(Color color) {
    switch (color) {
        case WHITE: activateColor("white"); break;
        case LIGHT_BLUE: activateColor("light_blue"); break;
        case PINK: activateColor("pink"); break;
        case ORANGE: activateColor("orange"); break;
        case GREEN: activateColor("green"); break;
        case BLUE: activateColor("blue"); break;
        case YELLOW: activateColor("yellow"); break;
        case RED: activateColor("red"); break;
        default: break;
    }
}

void MovingHeadFusionMKII::setGobo(Gobo gobo) {
    switch (gobo) {
        case GOBO_OPEN: activateGobo("open"); break;
        case GOBO_2: activateGobo("2"); break;
        case GOBO_3: activateGobo("3"); break;
        case GOBO_4: activateGobo("4"); break;
        case GOBO_5: activateGobo("5"); break;
        case GOBO_6: activateGobo("6"); break;
        case GOBO_7: activateGobo("7"); break;
        case GOBO_8: activateGobo("8"); break;
        default: break;
    }
}

void MovingHeadFusionMKII::setFunction(Function function) {
    switch (function) {
        case NONE: activateFunction("null"); break;
        case BLACK_COLOR_CHANGE: activateFunction("black_color_change"); break;
        case BLACK_GOBO_CHANGE: activateFunction("black_gobo_change"); break;
        case RESET: activateFunction("reset"); break;
        default: break;
    }
}

void MovingHeadFusionMKII::onColorChange(ofAbstractParameter &changed) {
    activateColor(changed.getName());
}

void MovingHeadFusionMKII::onGoboChange(ofAbstractParameter &changed) {
    activateGobo(changed.getName());
}

void MovingHeadFusionMKII::onFunctionChange(ofAbstractParameter &changed) {
    activateFunction(changed.getName());
}

string MovingHeadFusionMKII::getFixtureCurrentColor() {
    for (auto& color : colorsMap) {
        if (color.second == channels[2]) {
            return color.first;
        }
    }
}

string MovingHeadFusionMKII::getFixtureCurrentGobo() {
    for (auto& gobo : gobosMap) {
        if (gobo.second == channels[3]) {
            return gobo.first;
        }
    }
}

string MovingHeadFusionMKII::getFixtureCurrentFunction() {
    for (auto& function : functionsMap) {
        if (function.second == channels[6]) {
            return function.first;
        }
    }
}

// ---------------------------
// radio button style parameter group
// ---------------------------

void MovingHeadFusionMKII::fillGroupFromMap(const std::map<string, int> &map, ofParameterGroup &group) {
    for (auto& item : map) {
        ofParameter<bool> param(item.first, false);
        group.add(param);
    }
}

void MovingHeadFusionMKII::activateParameterInGroup(ofParameterGroup &group, string parameterName) {
    for (auto& parameter : group) {
        if (parameter->getName() == parameterName) {
            // enable without triggering
            parameter->cast<bool>().disableEvents();
            parameter->cast<bool>().set(true);
        } else {
            // disable without triggering events
            parameter->cast<bool>().disableEvents();
            parameter->cast<bool>().set(false);
            parameter->cast<bool>().enableEvents();
        }
    }
    // we need to do this to refresh the drawing due to a bug in ofxGui
    //gui.setPosition(gui.getPosition());
}
