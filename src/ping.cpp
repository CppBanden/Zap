//
//  ping.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 22/03/15.
//
//

#include "ping.h"
Ping::Ping(ofVec2f originInput, float velocityInput)
{
    origin = originInput;
    velocity = velocityInput;
}

void Ping::draw()
{
    if(velocity <= 0)
        return;

    velocity -= 0.03f;
    
    if(velocity < 1.0f)
        velocity = 0;

    size += velocity;

    ofNoFill();
    ofSetColor(230, 230, 255, 100);
//    ofCircle(origin.x, origin.y, size);
    
    ofVec2f drawPos = Utils::getMapDrawPos(origin);
    ofCircle(drawPos.x, drawPos.y, size);
}