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
}

void Map::move()
{
    ///TODO currently not being used
    if(selectedMapWorld == NULL)
        return;
    
    Location location = selectedMapWorld->location;

  //  int segmentX = floor(location.x / 3.0f) * 3;
//    int segmentY = floor(location.y / 3.0f) * 3;
    
    int segmentX = floor(location.x);
    int segmentY = floor(location.y);
    
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
vector<Ping *> pingReplies;

void Map::draw(ofVec2f cameraPos)
{
    selectedMapWorld = NULL;
    
    ofVec2f screenSize = Settings::getScreenSize();
//    ofVec2f playerOffset = currentMapWorld->offset;
    
    int segmentSize = screenSize.x / 5;//1.2f;//0.4f;//1.2f; //1.2; //5.0f; //1.2f; //0.4f;
    float unitSize = segmentSize / 3.0f;
    
    Utils::mapUnitSize = unitSize;
    Utils::mapRenderPos.x = (screenSize.x - segmentSize) / 2 + segmentSize / 2;
    Utils::mapRenderPos.y = (screenSize.y - segmentSize) / 2 + segmentSize / 2;
    
    Utils::mapCameraPos.x = cameraPos.x;
    Utils::mapCameraPos.y = cameraPos.y;
    
    //Update map segments
  //  int segmentX = round(cameraPos.x) * segmentWidth;
//    int segmentY = round(cameraPos.y) * segmentHeight;
    //int segmentX = round(cameraPos.x) * segmentWidth;
    //int segmentY = round(cameraPos.y) * segmentHeight;
    
    int segmentX = floor(cameraPos.x / 3.0f) * 3.0f;
    int segmentY = floor(cameraPos.y / 3.0f) * 3.0f;
    
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
    
  //  float offsetX = (cameraPos.x - round(cameraPos.x)) * segmentSize;
//    float offsetY = (cameraPos.y - round(cameraPos.y)) * segmentSize;

    float offsetX = (cameraPos.x - currentSegmentX) * unitSize;
    float offsetY = (cameraPos.y - currentSegmentY) * unitSize;

    float startX = Utils::mapRenderPos.x - offsetX;
    float startY = Utils::mapRenderPos.y - offsetY;
    
    for(int y = 0; y < width; ++y)
    {
        float posY = startY + ((y - 1) * segmentSize);
        
        for(int x = 0; x < height; ++x)
        {
            float posX = startX + ((x - 1) * segmentSize);

            ofSetColor(170);
            ofNoFill();
            ofRect(posX, posY, segmentSize, segmentSize);
        }
    }
    
    ///TODO flip so positive is upwards
    
    for(int y = 0; y < width; ++y)
    {
        float posY = startY + ((y - 1) * segmentSize);
        
        for(int x = 0; x < height; ++x)
        {
            float posX = startX + ((x - 1) * segmentSize);
            
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
    //ofVec2f playerPos = Player::instance->worldPos;
    //float dist = ofDist(playerPos.x, playerPos.y, 30, 30);
    //cout << dist << " dist\n";
    
    ofVec2f playerPos = Player::instance->drawWorldPos;
    
    if(pingTest != NULL)
    {
        pingTest->draw();
        
        /*for(int i = 0, size = pingMapWorlds.size(); i < size; ++i)
        {
            MapWorld *mw = pingMapWorlds[i];
            float dist = ofDist(playerPos.x, playerPos.y, mw->offset.x, mw->offset.y);
        }*/
        
        for(int j = 0, size = pingReplies.size(); j < size; j++)
        {
            pingReplies[j]->draw();
        }
        
        if(pingTest->velocity <= 0)
            pingTest = NULL;
    }
    
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
    if(pingTest != NULL)
        return;
    
    ofVec2f playerPos = Player::instance->worldPos;
    
    pingTest = new Ping(playerPos, 5.0f);
    
    pingMapWorlds.clear();
    
    pingReplies.clear();
    
    for(int y = 0; y < width; ++y)
    {
        for(int x = 0; x < height; ++x)
        {
            MapSegment *ms = mapSegments[y * height + x];
            
            for(int i = 0; i < 9; ++i)
            {
                MapWorld *mapWorld = ms->mapWorlds[i];
                pingMapWorlds.push_back(mapWorld);
             
                if(mapWorld->items.size() > 0)
                {
                    Ping *newPing = new Ping(mapWorld->pos, 5.0f);
                    pingReplies.push_back(newPing);
                }
            }
        }
    }
    
}

MapWorld *Map::getSelectedMapWorld()
{
    return selectedMapWorld;
}
