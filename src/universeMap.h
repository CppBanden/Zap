//
//  universeMap.h
//  Zap
//
//  Created by Martin Fasterholdt on 14/03/15.
//
//

#ifndef __Zap__universeMap__
#define __Zap__universeMap__

#include <stdio.h>
#include "ofMain.h"
#include "settings.h"
#include "location.h"

class UniverseMap
{
public:
    ofImage playerIcon;
    
    UniverseMap();
    void draw(Location playerLocation);
};

#endif /* defined(__Zap__universeMap__) */
