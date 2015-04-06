//
//  mapSegment.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 12/03/15.
//
//

#include "mapSegment.h"

MapSegment::MapSegment(Location locationInput, MapWorld **selectedMapWorld)
{
    this->selectedMapWorld = selectedMapWorld;
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            Location newLocation(locationInput.x + x, locationInput.y + y);
            mapWorlds[y * height + x] = WorldCreator::createMapWorld(newLocation);
        }
    }
}

void MapSegment::draw(int drawX, int drawY, int drawWidth, int drawHeight)
{
    int mouseX = ofGetMouseX();
    int mouseY = ofGetMouseY();

    for(int y = 0; y < height; ++y) git
    {
        for(int x = 0; x < width; ++x)
        {
            MapWorld *mw = mapWorlds[y * height + x];
            
            ofVec2f offset = mw->offset;
            int posX = drawX + drawWidth * offset.x;
            int posY = drawY + drawHeight * offset.y;
            
            float size = (mw->areaFraction / 700000) * (drawWidth / 100);
//            size = CLAMP(size, 6, 500);

            if(*selectedMapWorld == NULL)
            {
                //Player check
                ofVec2f playerPos = Player::instance->drawWorldPos;
                if(playerPos.x > posX - size && playerPos.x < posX + size && playerPos.y > posY - size && playerPos.y < posY + size)
                {
                    ofSetColor(250);
                    ofCircle(posX, posY, size + 2);
                    *selectedMapWorld = mw;
                }
                
                //Hover check
/*                if(mouseX > posX - size && mouseX < posX + size && mouseY > posY - size && mouseY < posY + size)
                {
                    ofSetColor(250);
                    ofCircle(posX, posY, size + 2);
                    *selectedMapWorld = mw;
                }*/
            }
            
            ofSetColor(mw->color);
            ofCircle(posX, posY, size);
            
            //TEMP DEBUG item
            if(mw->items.size() > 0)
            {
                ofSetColor(255);
                ofCircle(posX, posY, size / 3);
            }
        }
    }
}

