//
//  mapWorld.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 08/03/15.
//
//

#include "mapWorld.h"

MapWorld::MapWorld(ofColor colorInput, float areaFractionInput, ofVec2f offsetInput, Location locationInput)
{
    areaFraction = areaFractionInput;
    color = colorInput;
    offset = offsetInput;
    location = locationInput;
}

MapWorld::MapWorld(ofColor colorInput, float areaFractionInput, ofVec2f offsetInput, Location locationInput, vector<Item> itemsInput)
{
    areaFraction = areaFractionInput;
    color = colorInput;
    offset = offsetInput;
    location = locationInput;
    items = itemsInput;
    
    ///TODO this could be cleaner no hardcoded size
    pos.x = floor(location.x / 3.0f) * 3.0f + offset.x * 3.0f;
    pos.y = floor(location.y / 3.0f) * 3.0f + offset.y * 3.0f;
}