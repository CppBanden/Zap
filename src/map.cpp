//
//  map.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 08/03/15.
//
//

#include "map.h"

Map::Map(Location location, Input *input)
{
    this->input = input;
    
    int segmentX = floor(location.x / 3.0f) * 3;
    int segmentY = floor(location.y / 3.0f) * 3;
    
    for(int y = 0; y < width; ++y)
    {
        for(int x = 0; x < height; ++x)
        {
            Location segmentLocation(segmentX + ((x - 1) * segmentWidth), segmentY + ((y - 1) * segmentHeight));
            mapSegments[y * height + x] = new MapSegment(segmentLocation, &selectedMapWorld);
        }
    }
    
    //Set current map world
    int index = abs(segmentY - location.y) * height + abs(segmentX - location.x);
    currentMapWorld = mapSegments[height + 1]->mapWorlds[index];
    
    playerIcon.loadImage("images/playerIcon.png");
    playerIcon.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    currentLocation = location;
    currentSegmentX = segmentX;
    currentSegmentY = segmentY;
}

void Map::move()
{
    if(selectedMapWorld == NULL)
        return;
    
    Location location = selectedMapWorld->location;

    int segmentX = floor(location.x / 3.0f) * 3;
    int segmentY = floor(location.y / 3.0f) * 3;
    
    if(currentSegmentX != segmentX || currentSegmentY != segmentY)
    {
        for(int y = 0; y < width; ++y)
        {
            for(int x = 0; x < height; ++x)
            {
                Location segmentLocation(segmentX + ((x - 1) * segmentWidth), segmentY + ((y - 1) * segmentHeight));
                mapSegments[y * height + x] = new MapSegment(segmentLocation, &selectedMapWorld);
            }
        }
    }
    
    //Set current map world
    int index = abs(segmentY - location.y) * height + abs(segmentX - location.x);
    currentMapWorld = mapSegments[height + 1]->mapWorlds[index];
    
    currentLocation = location;
    currentSegmentX = segmentX;
    currentSegmentY = segmentY;
}

float currentPingSize;
float currentPingVelocity;
vector<MapWorld *> pingMapWorlds;

void Map::draw()
{
    selectedMapWorld = NULL;
    
    ofBackground(0);

    ofVec2f screenSize = Settings::getScreenSize();
    ofVec2f playerOffset = currentMapWorld->offset;
    
    int segmentSize = screenSize.x / 2.5f;
    
    int startX = (screenSize.x - segmentSize) / 2;
    int startY = (screenSize.y - segmentSize) / 2;
    
    for(int y = 0; y < width; ++y)
    {
        int posY = startY + ((y - 1) * segmentSize);
        
        for(int x = 0; x < height; ++x)
        {
            int posX = startX + ((x - 1) * segmentSize);
            
            ofSetColor(170);
            ofNoFill();
            ofRect(posX, posY, segmentSize, segmentSize);
        }
    }
    
    ///TODO flip so positive is upwards
    
    for(int y = 0; y < width; ++y)
    {
        int posY = startY + ((y - 1) * segmentSize);
        
        for(int x = 0; x < height; ++x)
        {
            int posX = startX + ((x - 1) * segmentSize);
            
            ofFill();
            MapSegment *ms = mapSegments[y * height + x];
            ms->draw(posX, posY, segmentSize, segmentSize);
        }
    }
    
    //Current location
    int size = 20;
    int playerX = startX + segmentSize * playerOffset.x;
    int playerY = startY + segmentSize * playerOffset.y;
    
    ofFill();
    ofSetColor(255);
    playerIcon.draw(playerX - size / 2, playerY - size / 2, size, size);
    
    //Ping
    ///Ping should be moved somewhere else
    if(currentPingVelocity > 0)
    {
        currentPingSize += currentPingVelocity;
        
        currentPingVelocity -= 0.03f;
        if(currentPingVelocity < 1.0f)
            currentPingVelocity = 0;
        
        ofNoFill();
        ofSetColor(230, 230, 255, 100);
        ofCircle(playerX, playerY, currentPingSize);

        for(int i = 0, size = pingMapWorlds.size(); i < size; ++i)
        {
            MapWorld *mw = pingMapWorlds[i];
            float dist = ofDist(playerX, playerY, mw->offset.x, mw->offset.y);
            
        }
    }
    else if(input->button1Pressed)
    {
        currentPingSize = 0;
        currentPingVelocity = 5;
        pingMapWorlds.clear();
        
        for(int y = 0; y < width; ++y)
        {
            for(int x = 0; x < height; ++x)
            {
                MapSegment *ms = mapSegments[y * height + x];

                for(int i = 0; i < 9; ++i)
                    pingMapWorlds.push_back(ms->mapWorlds[i]);
            }
        }
    }
    
    if(selectedMapWorld != NULL)
    {
        std::ostringstream s;
        s << "Destination " << selectedMapWorld->location.x << "," << selectedMapWorld->location.y;
        //s << " " << selectedMapWorld->location.value();
        ofDrawBitmapStringHighlight(s.str(), 15, 50);
    }
}


MapWorld *Map::getSelectedMapWorld()
{
    return selectedMapWorld;
}

