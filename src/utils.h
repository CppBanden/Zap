//
//  utils.h
//  Zap
//
//  Created by Martin Fasterholdt on 06/04/15.
//
//

#ifndef __Zap__utils__
#define __Zap__utils__

#include <stdio.h>
#include "settings.h"

class Utils
{
public:
    static ofVec2f mapRenderPos;
    static ofVec2f mapCameraPos;
    static float mapUnitSize;
    static ofVec2f getMapDrawPos(ofVec2f pos);
    static ofVec2f getMapDrawPos(ofVec2f pos, float size);
    
    ///TODO Add rounding function
};

#endif /* defined(__Zap__utils__) */
