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
//            int locationValue = Location::getValue(locationInput.x + x, locationInput.y + y);
            Location newLocation(locationInput.x + x, locationInput.y + y);
            mapWorlds[y * height + x] = WorldCreator::createMapWorld(newLocation);
            
            /*ofSeedRandom(locationValue);
            
            ofVec3f randomColor = WorldCreator::getRandomColor() * 255;
            
            ofColor groundColor(randomColor.x, randomColor.y, randomColor.z);
            
            ofVec2f size = WorldCreator::generateWorldSize();
            float area = size.x * size.y;
            
            ofVec2f offset(ofRandom(0, 1), ofRandom(0, 1));
            
            mapWorlds[y * height + x] = new MapWorld(groundColor, area, offset);*/
        }
    }
    
}

void MapSegment::draw(int drawX, int drawY, int drawWidth, int drawHeight)
{
    int mouseX = ofGetMouseX();
    int mouseY = ofGetMouseY();
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            MapWorld *mw = mapWorlds[y * height + x];
            
            ofVec2f offset = mw->offset;
            int posX = drawX + drawWidth * offset.x;
            int posY = drawY + drawHeight * offset.y;
            
            ///TODO make releative to drawWidth
            
            float size = (mw->areaFraction / 500000) * (drawWidth / 100);
            
            size = CLAMP(size, 6, 100);
            
            //Hover check
            if(*selectedMapWorld == NULL)
            {
                if(mouseX > posX - size && mouseX < posX + size && mouseY > posY - size && mouseY < posY + size)
                {
                    ofSetColor(250);
                    ofCircle(posX, posY, size + 2);
                    *selectedMapWorld = mw;
                }
            }
            
            ofSetColor(mw->color);
            ofCircle(posX, posY, size);
        }
    }
}

