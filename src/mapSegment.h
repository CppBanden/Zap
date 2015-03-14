//
//  mapSegment.h
//  Zap
//
//  Created by Martin Fasterholdt on 12/03/15.
//
//

#ifndef __Zap__mapSegment__
#define __Zap__mapSegment__

#include <stdio.h>
#include "location.h"
#include "worldCreator.h"
#include "ofMain.h"

class MapSegment
{
public:
    
    int width = 3;
    int height = 3;
    
    MapWorld *mapWorlds[9];
    MapWorld **selectedMapWorld;
    
    MapSegment(Location location, MapWorld **selectedMapWorld);
    void draw(int drawX, int drawY, int drawWidth, int drawHeight);
};

#endif /* defined(__Zap__mapSegment__) */
