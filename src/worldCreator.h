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
#include <vector>

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
    World *createWorld(int locationInput, float age = 0.5f);
    void showShader(int locationInput);
    
    static ofVec3f getRandomColor();
    static ofVec2f generateWorldSize();
    static vector<Item> generateItems();
    static MapWorld *createMapWorld(Location locationInput);
};

#endif /* defined(__Sap__worldCreator__) */
