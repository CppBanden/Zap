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

MapWorld *WorldCreator::createMapWorld(Location locationInput)
{
    ofSeedRandom(locationInput.value());
    
    ofVec3f randomColor = getRandomColor() * 255;
    ofColor groundColor(randomColor.x, randomColor.y, randomColor.z);
    
    ofVec2f size = generateWorldSize();
    float area = size.x * size.y;
    
    ofVec2f offset(ofRandom(0, 1), ofRandom(0, 1));
    
    return new MapWorld(groundColor, area, offset, locationInput);
}

World *WorldCreator::createWorld(int locationInput)
{
    //Handle Location
    int location;
    
    if(locationInput <= 0)
        location = round(ofRandom(0, 99999999)); //Travel to random location
    else
        location = locationInput; //Travel to known location
    
//    int i =  99999999;
    //i =  9999 + 9999;
    
    //399.920.004

    //printf("%i\n", i);
    
    ofSeedRandom(location);
    
    printf("travel to location : %i \n", location);
    
    //Preparation
    ofVec2f screenSize = Settings::getScreenSize();
    ofFbo frameBuffer;
    ofPixels pixels;
    
    ///TODO consider tool to just randomize one element
    
    //Create World
    ofVec3f groundColor = getRandomColor();
    
    ofVec3f surfaceColor = groundColor; ///Allow different ground color
    surfaceColor /= ofRandom(3, 4);

    ofVec2f worldSize = generateWorldSize();
    frameBuffer.allocate(worldSize.x, worldSize.y, GL_RGBA);

    float minDensity = 0.8;
    float maxDensity = 1;
    float density = ofRandom(minDensity, maxDensity);

    ofFill();
    
    //World outline
    ofTexture outlineTexture = metaballGenerator->generate(worldSize, density);
    
    
    //Outline
    float randomTimeOutline = ofRandom(0, 1000);

    frameBuffer.begin();
        ofClear(255,255,255,0);
    
        if(!outlineShader.isLoaded())
            outlineShader.load("outlineKamenShader");
    
        outlineShader.begin();
    
        outlineShader.setUniform1f("time", randomTimeOutline);
        outlineShader.setUniformTexture("imageMask", outlineTexture, 0);
        outlineShader.setUniform2f("worldSize", worldSize.x, worldSize.y);
    
        ofRect(0,0, worldSize.x, worldSize.y);
    
        outlineShader.end();
    frameBuffer.end();
    
    ofImage imageOutline;
    imageOutline.allocate(worldSize.x, worldSize.y, OF_IMAGE_COLOR_ALPHA);
    frameBuffer.readToPixels(pixels);
    imageOutline.setFromPixels(pixels);
    
    
    //Rocks
    float sharpness = ofRandom(2.0f, 2.3f);
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
        ofClear(255,255,255,0);
    
        if(!groundShader.isLoaded())
            groundShader.load("groundKamenShader");

        groundShader.begin();

            groundShader.setUniform1f("time", randomTime); //shader.setUniform1f("time", ofGetFrameNum() * 0.0005);
            groundShader.setUniform1f("sharpnees", sharpness);
            groundShader.setUniform1f("density", rockDensity);
    
            ///TODO blend between multiple colors
            groundShader.setUniform3fv("randomColor", &groundColor[0]);
            groundShader.setUniformTexture("imageMask", imageOutline.getTextureReference(), 0);
            //groundShader.setUniformTexture("imageMask", outlineTexture, 0);
    
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
    
    //Surface
    frameBuffer.begin();
        ofClear(0,0,0,0);

        if(!surfaceShader.isLoaded())
            surfaceShader.load("surfaceShader");
    
        surfaceShader.begin();
    
            surfaceShader.setUniformTexture("imageMask", imageOutline.getTextureReference(), 0);
            //surfaceShader.setUniformTexture("imageRocks", imageOutline.getTextureReference(), 1);
    
            surfaceShader.setUniform3fv("randomColor", &surfaceColor[0]);
    
            ofRect(0,0,worldSize.x, worldSize.y);
    
        surfaceShader.end();
    frameBuffer.end();
    
    ofImage imageSurface;
    imageSurface.allocate(worldSize.x, worldSize.y, OF_IMAGE_COLOR_ALPHA);
    frameBuffer.readToPixels(pixels);
    imageSurface.setFromPixels(pixels);
    
    //Space
    frameBuffer.begin();
        ofClear(0,0,0,0);
    
        if(!spaceShader.isLoaded())
        {
            spaceShader.load("spaceShader");
        }
    
        spaceShader.begin();
            spaceShader.setUniform2f("worldSize", worldSize.x, worldSize.y);
            ofRect(0,0,worldSize.x, worldSize.y);
        spaceShader.end();
    frameBuffer.end();
    
    ofImage imageSpace;
    imageSpace.allocate(worldSize.x, worldSize.y, OF_IMAGE_COLOR_ALPHA);
    frameBuffer.readToPixels(pixels);
    imageSpace.setFromPixels(pixels);
    
    World *world = new World(imageRocks, imageSurface, imageSpace, location);

    return world;
}

ofVec2f WorldCreator::generateWorldSize()
{
    float maxSize = 2500;
    float minSize = 500;

    ofVec2f worldSize;
    worldSize.x = ofRandom(minSize, maxSize);
    worldSize.y = ofRandom( MAX(worldSize.x / 2, minSize), MIN(worldSize.x * 2, maxSize));
    
    return worldSize;
}

ofVec3f WorldCreator::getRandomColor()
{
    ///TODO consider range control, Hue, Saturation, Brightness
    
    ofVec3f randomColor(ofRandom(1),ofRandom(1),ofRandom(1));
    return randomColor;
}