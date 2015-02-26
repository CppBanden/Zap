//
//  level.cpp
//  Sap
//
//  Created by Martin Fasterholdt on 07/02/15.
//
//

#include "level.h"

Level::Level(string fileName)
{
    ofImage fileImage;
    
    fileImage.loadImage(fileName);
    
    Level::SetupImage(fileImage);
}

Level::Level(ofImage i, int locationInput)
{
    location = locationInput;
    
    Level::SetupImage(i);
}

void Level::SetupImage(ofImage i)
{
    ofDisableArbTex();
    
    image = i;
    image.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    image.getTextureReference().setTextureWrap(GL_REPEAT,GL_REPEAT);
    
    ofEnableArbTex();
    
    worldSize.x = image.getWidth();
    worldSize.y = image.getHeight();
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

/*void Level::wrapPosition(int *x, int *y)
{
    if(*x < 0)
        x += (int)worldSize.x;
    else if(*x >= (int)worldSize.x)
        x -= (int)worldSize.x;
    
    if(*y < 0)
        y += (int)worldSize.y;
    else if(*y >= (int)worldSize.y)
        y -= (int)worldSize.y;
}*/