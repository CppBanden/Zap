//
//  map.h
//  Zap
//
//  Created by Martin Fasterholdt on 08/03/15.
//
//

#ifndef __Zap__map__
#define __Zap__map__

#include <stdio.h>
#include "ofMain.h"
#include "settings.h"
#include "mapWorld.h"
#include "worldCreator.h"
#include "location.h"
#include "mapSegment.h"
#include "input.h"

class Map
{
public:
    
    int width = 3;
    int height = 3;
    
    int segmentWidth = 3;
    int segmentHeight = 3;
    
    Input *input;
    MapSegment *mapSegments[9];
    
    MapWorld *selectedMapWorld;
    
    Map(Location location, Input *input);
    
    void draw();
    MapWorld *getSelectedMapWorld();
};
#endif /* defined(__Zap__map__) */