//
//  worldCreator.cpp
//  Sap
//
//  Created by Martin Fasterholdt on 14/02/15.
//
//

#include "worldCreator.h"

WorldCreator::WorldCreator()
{
     metaballGenerator = new MetaballGenerator();
}

World *WorldCreator::createWorld(int locationInput)
{    
    //Handle Location
    int location;
    
    if(locationInput <= 0)
        location = round(ofRandom(0, 999999999)); //Travel to random location
    else
        location = locationInput; //Travel to known location

    ofSeedRandom(location);
    printf("travel to location : %i \n", location);

    //Settings
    float maxSize = 3000;
    float minSize = 500;
    ///TODO create comfortable worlds with 10% large deviation
    float minArea = minSize * minSize;
    float maxArea = maxSize * maxSize;
    
    float minDensity = 0.3;
    minDensity = 1;
    float maxDensity = 1;
    
    //Preparation
    ofVec2f screenSize = Settings::getScreenSize();
    ofFbo frameBuffer;
    ofPixels pixels;
    
    ///TODO consider tool to just randomize one element
    
    //Create World
    ofVec3f groundColor = getRandomColor();

    ofVec3f surfaceColor = groundColor; ///Allow different ground color
    surfaceColor /= ofRandom(4, 5);

    float worldWidth = ofRandom(minSize, maxSize);
    float worldHeight = ofRandom( MAX(worldWidth / 2, minSize), MIN(worldWidth * 2, maxSize));
    
    ofVec2f worldSize(worldWidth, worldHeight);
    frameBuffer.allocate(worldSize.x, worldSize.y, GL_RGBA);

    float area = ofLerp(minArea, maxArea, worldSize.x * worldSize.y);
    float density = ofRandom(minDensity, maxDensity);

    //World outline
    ofTexture outlineTexture = metaballGenerator->generate(worldSize, area, density);
    
    //Surface
    frameBuffer.begin();
        ofClear(255,255,255,0);
    
        if(!surfaceShader.isLoaded())
            surfaceShader.load("surfaceShader");
    
        surfaceShader.begin();
    
        surfaceShader.setUniformTexture("imageMask", outlineTexture, 0);
        surfaceShader.setUniform3fv("randomColor", &surfaceColor[0]);

        ofRect(0,0,worldSize.x, worldSize.y);
    
        surfaceShader.end();
    frameBuffer.end();
    
    ofImage imageSurface;
    imageSurface.allocate(worldSize.x, worldSize.y, OF_IMAGE_COLOR_ALPHA);
    frameBuffer.readToPixels(pixels);
    imageSurface.setFromPixels(pixels);

    //Rocks
    float sharpness = ofRandom(2.0f, 2.25f);
    float randomTime = ofRandom(0, 1000); ///Event very high time to pixelate 100000 and above

    float rockDensity = ofRandom(0, 0.12f);
    if(ofRandom(1) > 0.85f)
        rockDensity = ofRandom(0, 0.3f);
    
    ofVec2f rockDetailSize;
    rockDetailSize.x = ofRandom(550, 700);
    if(ofRandom(1) > 0.9f)
        rockDetailSize.x = ofRandom(700, 3000);
    
    float rockDetailRatio = ofRandom(0.7f, 0.8f);
    if(ofRandom(1) > 0.9f)
        rockDetailRatio = ofRandom(0.5f, 1.75f);
    
    rockDetailSize.y = rockDetailSize.x * rockDetailRatio;
    
    frameBuffer.begin();
        ofClear(255,255,255, 0);
    
        if(!groundShader.isLoaded())
            groundShader.load("groundKamenShader");

        groundShader.begin();

        groundShader.setUniform1f("time", randomTime); //shader.setUniform1f("time", ofGetFrameNum() * 0.0005);
        groundShader.setUniform1f("sharpness", sharpness);
        groundShader.setUniform1f("density", rockDensity);
    
        ///TODO blend between multiple colors
        groundShader.setUniform3fv("randomColor", &groundColor[0]);
        groundShader.setUniformTexture("imageMask", outlineTexture, 0);
    
        groundShader.setUniform2f("detailSize", rockDetailSize.x, rockDetailSize.y);
        groundShader.setUniform2f("worldSize", worldSize.x, worldSize.y);
        groundShader.setUniform2f("screenSize", screenSize.x, screenSize.y); //shader.setUniform1f("time", ofGetFrameNum() * 0.0005);
    
        ofRect(0,0, worldSize.x, worldSize.y);
    
        groundShader.end();
    frameBuffer.end();

    ofImage imageRocks;
    imageRocks.allocate(worldSize.x, worldSize.y, OF_IMAGE_COLOR_ALPHA);
    frameBuffer.readToPixels(pixels);
    imageRocks.setFromPixels(pixels);
    
    World *world = new World(imageRocks, imageSurface, location);
    
    return world;
}

ofVec3f WorldCreator::getRandomColor()
{
    /*if(groundColors.empty())
    {
        groundColors.push_back(ofVec3f(0.112818, 0.128799, 0.726646));
        groundColors.push_back(ofVec3f(0.112818, 0.128799, 0.726646));
        groundColors.push_back(ofVec3f(0.188, 0.343, 0.133));
        groundColors.push_back(ofVec3f(0.337168, 0.782652, 0.031841));
        groundColors.push_back(ofVec3f(0.080275, 0.189667, 0.735532));
        groundColors.push_back(ofVec3f(0.872, 0.037, 0.25));
        groundColors.push_back(ofVec3f(0.75, 0.75, 0.75));
        groundColors.push_back(ofVec3f(0.035920, 0.699656, 0.116564));
        groundColors.push_back(ofVec3f(0.581039, 0.521520, 0.186455));
        groundColors.push_back(ofVec3f(0.028492, 0.868792, 0.791858));
        groundColors.push_back(ofVec3f(0.467784, 0.047525, 0.746419));
        groundColors.push_back(ofVec3f(0.199442, 0.024695, 0.052515));
    }

    int i = floor(ofRandom(0, groundColors.size() - 0.01f));*/
    //return groundColors[i];
    
    ///TODO consider range control, Hue, Saturation, Brightness
    
    //printf("color inden %i \n", colorIndex);
    ofVec3f randomColor(ofRandom(1),ofRandom(1),ofRandom(1));
    return randomColor;
//    return ofColor(ofRandom(1), ofRandom(1), ofRandom(1));
}