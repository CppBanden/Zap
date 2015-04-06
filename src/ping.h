//
//  ping.h
//  Zap
//
//  Created by Martin Fasterholdt on 22/03/15.
//
//

#ifndef __Zap__ping__
#define __Zap__ping__

#include <stdio.h>
#include "ofMain.h"
#include "utils.h"

class Ping
{
public:
    float velocity;
    ofVec2f origin;
    float size;
    
    Ping(ofVec2f origin, float velocity);
    void draw();
};
#endif /* defined(__Zap__ping__) */
