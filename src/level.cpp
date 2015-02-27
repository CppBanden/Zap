//
//  level.cpp
//  Sap
//
//  Created by Martin Fasterholdt on 07/02/15.
//
//

#include "level.h"

///TODO this setting should be somewhere else
float Level::zoom = 3.0f;

Level::Level(string fileName)
{
    ofImage fileImage;
    
    fileImage.loadImage(fileName);
    
    Level::setupImage(fileImage);
}

Level::Level(ofImage i, int locationInput)
{
    location = locationInput;
    
    Level::setupImage(i);
}

void Level::setupImage(ofImage i)
{
    ofDisableArbTex();
    
    image = i;
    image.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    image.getTextureReference().setTextureWrap(GL_REPEAT,GL_REPEAT);
    
    ofEnableArbTex();
    
    setZoom(Level::zoom);
    
    worldSize.x = image.getWidth();
    worldSize.y = image.getHeight();
}

void Level::draw(ofVec2f pos)
{
    ///TODO Ratio and zoom only needs to be calculated on screen and zoom changes
    
    ///TODO Center level when ratio does not fit perfectly
    
    ///TODO Cap width in relatio to max height to support super wide window
    
    ofVec2f screenSize = Settings::getScreenSize();
    
    ofSetColor(0, 0, 0);
    ofRect(0, 0, screenSize.x, screenSize.y);
    
    float ratio = (screenSize.x / zoomSize.x);
    drawArea.x = screenSize.x;
    drawArea.y = zoomSize.y * ratio;

    ofVec2f renderPos;
    renderPos.x = pos.x - (drawArea.x / 2) / ratio;
    renderPos.y = pos.y - (drawArea.y / 2) / ratio;
    
    ofSetColor(255);
    image.drawSubsection(0, 0, drawArea.x, drawArea.y, renderPos.x, renderPos.y, zoomSize.x, zoomSize.y);
}

void Level::setPixel(int x, int y, ofColor color)
{
    image.setColor(x, y, color);
}

void Level::fadePixel(int x, int y, float amount)
{
    if(x < 0)
        x += worldSize.x;
    else if(x >= worldSize.x)
        x -= worldSize.x;
    
    if(y < 0)
        y += worldSize.y;
    else if(y >= worldSize.y)
        y -= worldSize.y;
    
    ofColor current = image.getColor(x, y);
    float nextBrightness = (current.getBrightness() / 255) - amount;
    
    if(nextBrightness < 0)
        nextBrightness = 0;
    
    current.setBrightness(nextBrightness * 255);
    
    image.setColor(x, y, current);
}

void Level::updateImage()
{
    image.update();
}

void Level::setZoom(float zoomInput)
{
    ///TODO world ratio should not be set here
    zoomSize.x = 160 * zoomInput;
    zoomSize.y = 90 * zoomInput;
    
    Level::zoom = zoomInput;
}

ofVec2f Level::getWorldSize()
{
    return worldSize;
}

ofColor Level::getPixel(int x, int y)
{
    return image.getColor(x, y);
}

void Level::wrapPosition(ofVec2f *pos)
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