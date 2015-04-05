//
//  universeMap.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 14/03/15.
//
//

#include "universeMap.h"

UniverseMap::UniverseMap()
{
    playerIcon.loadImage("images/playerIcon.png");
    playerIcon.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}

void UniverseMap::draw(Location playerLocation)
{
    ofVec2f screenSize = Settings::getScreenSize();
    
    ofNoFill();
    ofSetColor(220);
    
    int mapSize = screenSize.x * 0.8;
    
    if(mapSize > screenSize.y)
        mapSize = screenSize.y * 0.8;
    
    int drawPosX = (screenSize.x - mapSize) / 2;
    int drawPosY = (screenSize.y - mapSize) / 2;

    ofRect(drawPosX, drawPosY, mapSize, mapSize);
    int size = 20;
    int playerX = drawPosX - size / 2.0f + mapSize / 2.0f + (playerLocation.x / 9999.0f) * mapSize / 2.0f;
    int playerY = drawPosY - size / 2.0f + mapSize / 2.0f + (playerLocation.y / 9999.0f) * mapSize / 2.0f;
    
    ofFill();
    ofSetColor(255);
    playerIcon.draw(playerX, playerY, size, size);
}