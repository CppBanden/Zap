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
#include "level.h"
#include "metaballGenerator.h"
#include "settings.h"

class WorldCreator
{
public:
    ofShader groundShader;
    vector<ofVec3f> groundColors;
    MetaballGenerator *metaballGenerator;
    
    WorldCreator();
    Level *createWorld(int locationInput);
    void showShader(int locationInput);
    ofVec3f getRandomColor();

    static const int defaultLocation = 674685952;
    static const int worldWidth = 600;
    static const int worldHeight = 400;
    
    static ofVec2f getWorldSize();
};

#endif /* defined(__Sap__worldCreator__) */
