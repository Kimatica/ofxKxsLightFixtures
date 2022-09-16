#include "ApeLabsCans.h"
#include "Grid.h"

ApeLabsLightCan::ApeLabsLightCan()
{
    channels.resize(4);

    // smoothing
    channelsSmooth.resize(channels.size());
    for (int i = 0; i < channels.size(); i++) {
        smoothers.push_back(Smoother(channels[i], channelsSmooth[i]));
    }
}

ApeLabsLightCan::~ApeLabsLightCan()
{
    ofLog(OF_LOG_VERBOSE, "ApeLabsCans destroyed");
}

void ApeLabsLightCan::update()
{
    ofColor rgbwCol = RGBToRGBW(dimmer * red * 255, dimmer * green * 255, dimmer * blue * 255);

    white = rgbwCol.a / 255.0f;

    channels[0] = rgbwCol.r; // red
    channels[1] = rgbwCol.g; // green
    channels[2] = rgbwCol.b; // blue
    channels[3] = rgbwCol.a; // white

    smoothChannels();
}

void ApeLabsLightCan::update(Grid& grid)
{
    ofColor gridCol = grid.getColorAtPosition(gridPosition);

    ofColor rgbwCol = RGBToRGBW(dimmer * gridCol.r, dimmer * gridCol.g, dimmer * gridCol.b);

    red = rgbwCol.r / 255.0f + rgbwCol.a / 255.0f;
    green = rgbwCol.g / 255.0f + rgbwCol.a / 255.0f;
    blue = rgbwCol.b / 255.0f + rgbwCol.a / 255.0f;
    white = rgbwCol.a / 255.0f;

    dimmer = grid.dimmer;

    channels[0] = rgbwCol.r;    // red
    channels[1] = rgbwCol.g; // green
    channels[2] = rgbwCol.b;  // blue
    channels[3] = rgbwCol.a;  // blue

    smoothChannels();
}

void ApeLabsLightCan::draw()
{
    // default unit is cm
    float radius = 9;
    float depth = 8;
    ofFloatColor c(red * dimmer, green * dimmer, blue * dimmer);

    ofPushStyle();
    ofPushMatrix();
    {
        ofMultMatrix(transform);

        ofDrawAxis(8);

        // back
        ofSetColor(ofColor::dimGrey);
        ofDrawCircle(0, 0, depth - 0.01, radius);

        // front
        //if (strobe > 0.f) {
        //    float blinkFreq = strobe * 50.f;
        //    float blink = 0.5f + sin(ofGetElapsedTimef() * blinkFreq) * 0.5f; //0..1
        //    blink = blink > 0.8f ? 1.f : 0.f;
        //    c.set(c.r * blink, c.g * blink, c.b * blink);
        //}

        ofSetColor(c);
        ofDrawCircle(0, 0, depth, radius - 1);
    }
    ofPopMatrix();
    ofPopStyle();
}

ofColor ApeLabsLightCan::RGBToRGBW(float r, float g, float b)
{
    //Get the maximum between R, G, and B
    float tM = glm::max(r, glm::max(g, b));

    //If the maximum value is 0, immediately return pure black.
    if (tM == 0)
    {
        return ofColor(0,0,0,0);
    }

    //This section serves to figure out what the color with 100% hue is
    float multiplier = 255.0f / tM;
    float hR = r * multiplier;
    float hG = g * multiplier;
    float hB = b * multiplier;

    //This calculates the Whiteness (not strictly speaking Luminance) of the color
    float M = glm::max(hR, glm::max(hG, hB));
    float m = glm::min(hR, glm::min(hG, hB));
    float Luminance = ((M + m) / 2.0f - 127.5f) * (255.0f / 127.5f) / multiplier;

    //Calculate the output values
    int Wo = static_cast<int32_t>(Luminance);
    int Bo = static_cast<int32_t>(b - Luminance);
    int Ro = static_cast<int32_t>(r - Luminance);
    int Go = static_cast<int32_t>(g - Luminance);

    //Trim them so that they are all between 0 and 255
    if (Wo < 0) Wo = 0;
    if (Bo < 0) Bo = 0;
    if (Ro < 0) Ro = 0;
    if (Go < 0) Go = 0;
    if (Wo > 255) Wo = 255;
    if (Bo > 255) Bo = 255;
    if (Ro > 255) Ro = 255;
    if (Go > 255) Go = 255;

    return ofColor(Ro,Go, Bo,Wo );
}

void ApeLabsLightCan::initFixtureParameters()
{
    parameters.add(red.set("red", 1, 0, 1));
    parameters.add(green.set("green", 1, 0, 1));
    parameters.add(blue.set("blue", 1, 0, 1));
    parameters.add(white.set("white", 1, 0, 1));
    parameters.add(dimmer.set("dimmer", 1, 0, 1));

    smoothing.set("smoothing", 1, 0, 1);
}

void ApeLabsLightCan::initDrawing()
{
}