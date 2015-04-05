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
    
    /*int segmentX = floor(location.x / 3.0f) * 3;
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
    currentSegmentY = segmentY;*/
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

void Map::draw(ofVec2f cameraPos)
{
    selectedMapWorld = NULL;
    
    ofVec2f screenSize = Settings::getScreenSize();
//    ofVec2f playerOffset = currentMapWorld->offset;
    int segmentSize = screenSize.x / 1.2f; //0.4f;
    
    //Update map segments
    int segmentX = round(cameraPos.x) * segmentWidth;
    int segmentY = round(cameraPos.y) * segmentHeight;
    if(currentSegmentX != segmentX || currentSegmentY != segmentY)
    {
        for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
            {
                Location segmentLocation(segmentX + ((x - 1) * segmentWidth), segmentY + ((y - 1) * segmentHeight));
                mapSegments[y * height + x] = new MapSegment(segmentLocation, &selectedMapWorld);
            }
        }
        
        //Set current map world
        currentSegmentX = segmentX;
        currentSegmentY = segmentY;
    }

    ofBackground(0);
    
    float offsetX = (cameraPos.x - round(cameraPos.x)) * segmentSize;
    float offsetY = (cameraPos.y - round(cameraPos.y)) * segmentSize;
    
//    cout << "pos " << pos.x << "," << pos.y << " offset " << offsetX << ", " << offsetY << " segment " << segmentX << ", " << segmentY << " \n" ;
   // cout << "pos " << pos.x << " offset " << offsetX << " segment " << segmentX << " \n" ;
    int startX = (screenSize.x - segmentSize) / 2 - offsetX;
    int startY = (screenSize.y - segmentSize) / 2 - offsetY;
    
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
/*    int size = 20;
    int playerX = startX + segmentSize;// * playerOffset.x;
    int playerY = startY + segmentSize;// * playerOffset.y;
    
    ofFill();
    ofSetColor(255);
    playerIcon.draw(playerX - size / 2, playerY - size / 2, size, size);*/
    
    //Ping
    
    ofVec2f playerPos = Player::drawWorldPos;
    
    /*if(pingTest != NULL)
    {
        pingTest->draw();
        
        for(int i = 0, size = pingMapWorlds.size(); i < size; ++i)
        {
            MapWorld *mw = pingMapWorlds[i];
            float dist = ofDist(playerPos.x, playerPos.y, mw->offset.x, mw->offset.y);
        }
    }*/
    
    if(selectedMapWorld != NULL)
    {
        std::ostringstream s;
        s << "Destination " << selectedMapWorld->location.x << "," << selectedMapWorld->location.y;
        //s << " " << selectedMapWorld->location.value();
        ofDrawBitmapStringHighlight(s.str(), 15, 50);
    }
}

void Map::ping()
{
    return;
    
    if(pingTest != NULL)
        return;
    
    ofVec2f playerPos = Player::drawWorldPos;
    
    pingTest = new Ping(playerPos, 5.0f);
    
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

MapWorld *Map::getSelectedMapWorld()
{
    return selectedMapWorld;
}
