//
//  MovingHeadDMXControl.hpp
//  pointTracking
//
//  Created by Nestor Rubio Garcia on 13/04/2018.
//
//  ---
//  Fusion Spot MKII
//  8 channels DMX mode
//
//  This class provides a gui to control a MovingHeadDMX object,
//  simplifying the interface by using meaningfull names instead
//  of the cryptic DMX values.
//

#pragma once

#include "ofMain.h"
#include "MovingHead.h"
#include "ofxDmx.h"


class MovingHeadFusionMKII : public MovingHead {
    
public:
    enum Color { WHITE, LIGHT_BLUE, PINK, ORANGE, GREEN, BLUE, YELLOW, RED };
    enum Gobo { GOBO_OPEN, GOBO_2, GOBO_3, GOBO_4, GOBO_5, GOBO_6, GOBO_7, GOBO_8 };
    enum Function { NONE, BLACK_COLOR_CHANGE, BLACK_GOBO_CHANGE, RESET };
    
    MovingHeadFusionMKII();
    ~MovingHeadFusionMKII();
    
    void update() override;
    void draw() override;
    
    ofParameter<float> panTiltSpeed;
    ofParameter<float> shutter;
    //ofParameter<float> dimmer;
    ofParameterGroup groupColors;
    ofParameterGroup groupGobos;
    ofParameterGroup groupFunctions;
    
    void setColor(Color color);
    void setGobo(Gobo gobo);
    void setFunction(Function function);
    
private:
    void initPanTilt() override;
    void initFixtureMapping() override;
    void initFixtureParameters() override;
    //void initDrawing() override;
    
    std::map<string, int> colorsMap;
    std::map<string, int> gobosMap;
    std::map<string, int> functionsMap;
    
    void activateColor(string name);
    void activateGobo(string name);
    void activateFunction(string name);
    
    void onColorChange(ofAbstractParameter & parameter);
    void onGoboChange(ofAbstractParameter & parameter);
    void onFunctionChange(ofAbstractParameter & parameter);
    
    string getFixtureCurrentColor();
    string getFixtureCurrentGobo();
    string getFixtureCurrentFunction();
    
    // ------
    // methods for handling "radio button style" groups (only one param active)
    // TODO: move this to a GUI utils class
    
    void fillGroupFromMap(const std::map<string, int> &map, ofParameterGroup &group);
    void activateParameterInGroup(ofParameterGroup &group, string parameterName);
};
