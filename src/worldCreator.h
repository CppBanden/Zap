//
//  worldCreator.h
//  Sap
//
//  Created by Martin Fasterholdt on 14/02/15.
//
//

#ifndef __Sap__worldCreator__
#define __Sap__worldCreator__

#include <stdio.h>
#include "ofMain.h"
#include "world.h"
#include "metaballGenerator.h"
#include "settings.h"
#include "mapWorld.h"
#include "location.h"

class WorldCreator
{
public:
    ofShader outlineShader;
    ofShader groundShader;
    ofShader surfaceShader;
    ofShader spaceShader;
    
    vector<ofVec3f> groundColors;
    MetaballGenerator *metaballGenerator;
    
    WorldCreator();
    World *createWorld(int locationInput);
    void showShader(int locationInput);
    
    static ofVec3f getRandomColor();
    static ofVec2f generateWorldSize();
    static MapWorld *createMapWorld(Location locationInput);
    static const int defaultLocation = 870301;// 50001; //217761072; //162557792; //554100416; //840460480; //993632448; //576686720;
};

#endif /* defined(__Sap__worldCreator__) */
