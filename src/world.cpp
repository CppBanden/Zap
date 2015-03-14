//
//  level.cpp
//  Sap
//
//  Created by Martin Fasterholdt on 07/02/15.
//
//

#include "world.h"

///TODO this setting should be somewhere else
float World::zoom = 35;//9; //35;//1.5f;

World::World(ofImage rocks, ofImage surface, ofImage space, int locationInput)
{
    location = locationInput;
    
    ofDisableArbTex();
    
    imageRocks = rocks;
    setupImage(&imageRocks);
    
    imageSurface = surface;
    setupImage(&imageSurface);
    
    imageSpace = space;
    setupImage(&imageSpace);
    
    ofEnableArbTex();
    
    setZoom(World::zoom);
    
    worldSize.x = imageRocks.getWidth();
    worldSize.y = imageRocks.getHeight();
    
    
    ofDisableArbTex();
    
    frameBuffer.allocate(worldSize.x, worldSize.y, GL_RGBA);
    
    ofTexture frameBufferTexture = frameBuffer.getTextureReference();
    frameBufferTexture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    frameBufferTexture.setTextureWrap(GL_REPEAT,GL_REPEAT);
    
    ofEnableArbTex();

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

    float ratio = (screenSize.x / zoomSize.x);
    drawArea.x = screenSize.x;
    drawArea.y = zoomSize.y * ratio;

    ofVec2f renderPos;
    renderPos.x = pos.x - (drawArea.x / 2) / ratio;
    renderPos.y = pos.y - (drawArea.y / 2) / ratio;
    
    ofSetColor(255);
    
    imageSpace.drawSubsection(0, 0, drawArea.x, drawArea.y, renderPos.x, renderPos.y, zoomSize.x, zoomSize.y);
    
    imageSurface.drawSubsection(0, 0, drawArea.x, drawArea.y, renderPos.x, renderPos.y, zoomSize.x, zoomSize.y);

    imageRocks.drawSubsection(0, 0, drawArea.x, drawArea.y, renderPos.x, renderPos.y, zoomSize.x, zoomSize.y);
    
    
    //Experimenting with objects
    
    /*frameBuffer.begin();
    
        ofClear(255,255,255,0);

        ofSetColor(255, 129, 0);
        ofCircle(170, 170, 120);
    
        ofSetColor(150, 150, 150);
        ofRect(600, 600, 60, 30);
    frameBuffer.end();
    
    frameBuffer.getTextureReference().drawSubsection(0, 0, drawArea.x, drawArea.y, renderPos.x, renderPos.y, zoomSize.x, zoomSize.y);*/
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