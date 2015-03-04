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

class WorldCreator
{
public:
    ofShader outlineShader;
    ofShader groundShader;
    ofShader surfaceShader;
    
    vector<ofVec3f> groundColors;
    MetaballGenerator *metaballGenerator;
    
    WorldCreator();
    World *createWorld(int locationInput);
    void showShader(int locationInput);
    ofVec3f getRandomColor();

    static const int defaultLocation = 162557792; //554100416; //840460480; //993632448; //576686720;
};

#endif /* defined(__Sap__worldCreator__) */
