//
//  metaBallGenerator.h
//  Sap
//
//  Created by Martin Fasterholdt on 15/02/15.
//
//

#ifndef __Sap__metaBallGenerator__
#define __Sap__metaBallGenerator__

#include <stdio.h>
#include "ofMain.h"
#include "settings.h"

class MetaballGenerator
{
public:
    ofShader metaballShader;
    
    MetaballGenerator();
    ofTexture generate(ofVec2f worldSizem, float area, float density);
};

#endif /* defined(__Sap__metaBallGenerator__) */
