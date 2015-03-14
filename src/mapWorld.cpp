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