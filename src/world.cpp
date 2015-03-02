//
//  level.cpp
//  Sap
//
//  Created by Martin Fasterholdt on 07/02/15.
//
//

#include "world.h"

///TODO this setting should be somewhere else
float World::zoom = 9; //35;//1.5f;

World::World(ofImage rocks, ofImage surface, int locationInput)
{
    location = locationInput;
    
    ofDisableArbTex();
    
    imageRocks = rocks;
    setupImage(&imageRocks);
    
    imageSurface = surface;
    setupImage(&imageSurface);
    
    ofEnableArbTex();
    
    setZoom(World::zoom);
    
    worldSize.x = imageRocks.getWidth();
    worldSize.y = imageRocks.getHeight();
}

void World::setupImage(ofImage *image)
{
    image->getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    image->getTextureReference().setTextureWrap(GL_REPEAT,GL_REPEAT);
}

void World::draw(ofVec2f pos)
{
    ///TODO Ratio and zoom only needs to be calculated on screen and zoom changes
    
    ///TODO Center level when ratio does not fit perfectly
    
    ///TODO Cap width in relation to max height to support super wide window
    
    ofVec2f screenSize = Settings::getScreenSize();

    //ofSetColor(10, 10, 10);
    //ofRect(0, 0, screenSize.x, screenSize.y);


    float ratio = (screenSize.x / zoomSize.x);
    drawArea.x = screenSize.x;
    drawArea.y = zoomSize.y * ratio;

    ofVec2f renderPos;
    renderPos.x = pos.x - (drawArea.x / 2) / ratio;
    renderPos.y = pos.y - (drawArea.y / 2) / ratio;

    
    if(!spaceShader.isLoaded())
        spaceShader.load("spaceShader");
    
    spaceShader.begin();
    
        spaceShader.setUniform2f("worldSize", zoomSize.x, zoomSize.y);
        ofRect(0, 0, screenSize.x, screenSize.y);
    
    spaceShader.end();
    
    ofSetColor(255);
    imageSurface.drawSubsection(0, 0, drawArea.x, drawArea.y, renderPos.x, renderPos.y, zoomSize.x, zoomSize.y);
    
    ofSetColor(255);
    imageRocks.drawSubsection(0, 0, drawArea.x, drawArea.y, renderPos.x, renderPos.y, zoomSize.x, zoomSize.y);
}

void World::setPixel(int x, int y, ofColor color)
{
    imageRocks.setColor(x, y, color);
}

void World::fadePixel(int x, int y, float amount)
{
    if(x < 0)
        x += worldSize.x;
    else if(x >= worldSize.x)
        x -= worldSize.x;
    
    if(y < 0)
        y += worldSize.y;
    else if(y >= worldSize.y)
        y -= worldSize.y;
    
    ofColor current = imageRocks.getColor(x, y);
    float nextAlpha = (current.a / 255) - amount;
    
    if(nextAlpha < 0)
        nextAlpha = 0;
    
    current.a = nextAlpha * 255;

    imageRocks.setColor(x, y, current);
}

ofColor World::getRockPixel(int x, int y)
{
    return imageRocks.getColor(x, y);
}

ofColor World::getSurfacePixel(int x, int y)
{
    return imageSurface.getColor(x, y);
}

void World::updateImage()
{
    imageRocks.update();
}

void World::setZoom(float zoomInput)
{
    ///TODO world ratio should not be set here
    zoomSize.x = 160 * zoomInput;
    zoomSize.y = 100 * zoomInput;
    
    World::zoom = zoomInput;
}

ofVec2f World::getWorldSize()
{
    return worldSize;
}



void World::wrapPosition(ofVec2f *pos)
{
    if(pos->x < 0)
        pos->x += worldSize.x;
    else if(pos->x >= worldSize.x)
        pos->x -= worldSize.x;
    
    if(pos->y < 0)
        pos->y += worldSize.y;
    else if(pos->y >= worldSize.y)
        pos->y -= worldSize.y;
}