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
//    Location *location = new Location(90, 300);
    
//    testSegment = new MapSegment(*location);
    
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

    /*for(int y = 0; y < 4; ++y)
    {
        for(int x = 0; x < 8; ++x)
        {
            int locationValue = Location::getValue(x, y);
            
            ofSeedRandom(locationValue);
            
            ofVec3f randomColor = WorldCreator::getRandomColor() * 255;
            
             ofColor groundColor(randomColor.x, randomColor.y, randomColor.z);
            
            ofVec2f size = WorldCreator::generateWorldSize();
            float area = size.x * size.y;
            
            ofVec2f offset(ofRandom(-2, 2), ofRandom(-2, 2));

            mapWorlds[y * 8 + x] = new MapWorld(groundColor, area, offset);
        }
    }*/
}

void Map::draw()
{
//    MapSegment::selectedMapWorld = NULL;
    selectedMapWorld = NULL;
    
    ofBackground(0);

    ofVec2f screenSize = Settings::getScreenSize();
    
    int segmentSize = screenSize.x / 2.5f;
    
    int startX = (screenSize.x - segmentSize) / 2;
    int startY = (screenSize.y - segmentSize) / 2;
    
    int mouseX = input->mouseX;
    int mouseY = input->mouseY;

    for(int y = 0; y < width; ++y)
    {
        for(int x = 0; x < height; ++x)
        {
            ofFill();
            MapSegment *ms = mapSegments[y * height + x];
            int posX = startX + ((x - 1) * segmentSize);
            int posY = startY + ((y - 1) * segmentSize);
            ms->draw(posX, posY, segmentSize, segmentSize);
            
            ofSetColor(170);
            ofNoFill();
            ofRect(posX, posY, segmentSize, segmentSize);
        }
    }
    
    if(selectedMapWorld != NULL)
    {
        std::ostringstream s;
        s << selectedMapWorld->location.x << "," << selectedMapWorld->location.y;
        s << " " << selectedMapWorld->location.value();
        ofDrawBitmapStringHighlight(s.str(), 15, 50);
        
//        printf("x %i\n", selectedMapWorld->color.r);
    }
    
    /*            if(mouseX > posX && mouseX < posX + segmentSize && mouseY > posY && mouseY < posY + segmentSize)
     ofFill();
     else*/
    
    
            //mapSegments[y * height + x] = new MapSegment(segmentLocation);
//    testSegment->draw(startX, startY, segmentSize, segmentSize);

    
  //  ofVec2f border;
//    border.x = screenSize.x / 7;
  //  border.y = screenSize.y / 7;
    
    /*ofVec2f worldCount(8, 4);
    
    ofVec2f mapSize;
    mapSize.x = screenSize.x  - (border.x * 2);
    mapSize.y = screenSize.y  - (border.y * 2);

    ofVec2f spacing;
    spacing.x = mapSize.x / (worldCount.x  - 1);
    spacing.y = mapSize.y / (worldCount.y  - 1);
    
    testSegment->draw(100, 100, 500, 500);*/
    
   /* ofSeedRandom(50);
    
    for(int y = 0; y < worldCount.y; y++)
    {
        for(int x = 0; x < worldCount.x; x++)
        {
            MapWorld *mw = mapWorlds[y * 8 + x];
            ofVec2f offset = mw->offset;
            offset.x *= spacing.x / 10;
            offset.y *= spacing.y / 10;
            
            float size = mw->areaFraction / 110000;
            size = CLAMP(size, 6, 100);

            ofSetColor(mw->color);

//            ofCircle(border.x + (ofRandom(0, 7) * spacing.x), border.y + (ofRandom(0, 3) * spacing.y), size);
            ofCircle(border.x + (x * spacing.x) + offset.x, border.y + (y * spacing.y) + offset.y, size);
        }
    }*/
}


MapWorld *Map::getSelectedMapWorld()
{
    return selectedMapWorld;
}

