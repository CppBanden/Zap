//
//  player.h
//  Zap
//
//  Created by Martin Fasterholdt on 07/02/15.
//
//

#ifndef __Zap__player__
#define __Zap__player__

#include <stdio.h>
#include "ofMain.h"
#include "input.h"
#include "level.h"
#include "settings.h"

class Player
{
public:
    
    ofVec2f pos;
    ofVec2f velocity;
    ofImage image;
    
    Input *input;
    Level *level;
    
    float size = 20;
    
    float moveSpeed =0.004;//0.013;
    float maxMoveSpeed = 0.5;
    float friction = 0;//0.0035;
    
    float wallFriction = 0.5;
    float digSpeed = 0.04f;
    float digSpeedEdge = 0.005f;
    
    int frame;
    int totalFrames = 13;
    int fps = 4;
    
    //Fuel
    float fuel = 100;
    float fuelDrainMove = 0.0006f;
    float fuelDrainDig = 0.3f;
    
    Player(Level *l, Input *i, int x, int y);

    void draw();
    void update();
    
    std::string getDebugPos();
};

#endif /* defined(__Zap__player__) */
