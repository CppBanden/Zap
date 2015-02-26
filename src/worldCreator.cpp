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

bool first = true;

void WorldCreator::showShader(int locationInput)
{
    ofVec2f worldSize = getWorldSize();
    
    ofTexture outlineTexture = metaballGenerator->generate();
    float randomTime = ofRandom(0, 1000);
    
    ofFbo frameBuffer;
    
    frameBuffer.allocate(worldSize.x, worldSize.y, GL_RGBA);
    frameBuffer.begin();
        ofClear(255,255,255, 0);
        if(!groundShader.isLoaded())
            groundShader.load("groundKamenShader");
    
        groundShader.begin();
        groundShader.setUniform1f("time", randomTime); //shader.setUniform1f("time", ofGetFrameNum() * 0.0005);
        groundShader.setUniformTexture("imageMask", outlineTexture, 0);

        ofRect(0,0, worldSize.x, worldSize.y);
    
        groundShader.end();
    frameBuffer.end();
//    frameBuffer.getTextureReference().draw(0,0);
    
    ofTexture frameBufferTexture = frameBuffer.getTextureReference();
    ofPixels pixels;
    frameBuffer.readToPixels(pixels);
    
    //ofPixels pixels;
    //outlineTexture.readToPixels(pixels);
    
    ofImage newImage;
    newImage.allocate(worldSize.x, worldSize.y, OF_IMAGE_COLOR_ALPHA);
    newImage.setFromPixels(pixels);
    

    Level *level = new Level(newImage, 0);
    
    level->image.draw(0, 0);
}

Level *WorldCreator::createWorld(int locationInput)
{
    //Handle Location
    int location;
    
    if(locationInput <= 0)
        location = round(ofRandom(0, 999999999)); //Travel to random location
    else
        location = locationInput; //Travel to known location

    ofSeedRandom(location);
    printf("travel to location : %i \n", location);
    
    //Create World
    ofVec3f groundColor = getRandomColor();
    float randomTime = ofRandom(0, 1000);
    ofVec2f worldSize = getWorldSize();
    
    //World outline
    ofTexture outlineTexture = metaballGenerator->generate();

    ofFbo frameBuffer;
    frameBuffer.allocate(worldSize.x, worldSize.y, GL_RGBA);
    frameBuffer.begin();
        ofClear(255,255,255, 0);
    
        if(!groundShader.isLoaded())
            groundShader.load("groundKamenShader");

        groundShader.begin();
    
        groundShader.setUniformTexture("imageMask", outlineTexture, 0);

        groundShader.setUniform3fv("randomColor", &groundColor[0]);
        groundShader.setUniform1f("time", randomTime); //shader.setUniform1f("time", ofGetFrameNum() * 0.0005);
    
        groundShader.setUniform2f("worldSize", WorldCreator::worldWidth, WorldCreator::worldHeight);
    
        ofVec2f screenSize = Settings::getScreenSize();
        groundShader.setUniform2f("screenSize", screenSize.x, screenSize.y); //shader.setUniform1f("time", ofGetFrameNum() * 0.0005);
    
        ofRect(0,0, worldSize.x, worldSize.y);
    
        groundShader.end();
    frameBuffer.end();
    
    ofTexture frameBufferTexture = frameBuffer.getTextureReference();
    ofPixels pixels;
    frameBuffer.readToPixels(pixels);

    //ofPixels pixels;
    //outlineTexture.readToPixels(pixels);
    
    ofImage newImage;
    newImage.allocate(worldSize.x, worldSize.y, OF_IMAGE_COLOR_ALPHA);
    newImage.setFromPixels(pixels);
    
    //fbo->draw(0, 0, worldSize.x, worldSize.y);
//    ofBackground(0, 150, 0);
    
    Level *level = new Level(newImage, location);
    return level;
}


ofVec2f WorldCreator::getWorldSize()
{
    return ofVec2f(worldWidth, worldHeight);
}

ofVec3f WorldCreator::getRandomColor()
{
    if(groundColors.empty())
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

    int i = floor(ofRandom(0, groundColors.size() - 0.01f));
    return groundColors[i];
    
    //printf("color inden %i \n", colorIndex);
    //return ofColor(ofRandom(1), ofRandom(1), ofRandom(1));
}