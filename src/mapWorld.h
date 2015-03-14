//
//  mapWorld.h
//  Zap
//
//  Created by Martin Fasterholdt on 08/03/15.
//
//

#ifndef __Zap__mapWorld__
#define __Zap__mapWorld__

#include <stdio.h>
#include "ofMain.h"
#include "location.h"

class MapWorld
{
public:
    float areaFraction;
    ofColor color;
    ofVec2f offset;
    Location location;
    
    MapWorld(ofColor colorInput, float areaFractionInput, ofVec2f offsetInput, Location locationInput);
};

#endif /* defined(__Zap__mapWorld__) */
