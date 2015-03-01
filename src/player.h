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
#include "world.h"
#include "settings.h"

class Player
{
public:
    
    ofVec2f pos;
    ofVec2f cameraPos;
    ofVec2f velocity;
    ofImage image;

    Input *input;
    World *level;
    
    float size = 20;
    
    float moveSpeed = 0.013; //0.004;
    float maxMoveSpeed = 0.5;
    float friction = 0.0035; //0
    
    float wallFriction = 0.5f;
    float digSpeed = 0.05f;
    float digSpeedEdge = 0.005f;
    
    int frame;
    int totalFrames = 13;
    int fps = 4;
    
    //Fuel
    float fuel = 100;
    float fuelDrainMove = 0.0006f;
    float fuelDrainDig = 0.35f;
  
    //Camera
    float cameraFollowSpeed = 0.045f;
    
    Player(World *w, Input *i, int x, int y);

    void draw();
    void update();
    
    std::string getDebugPos();
};

#endif /* defined(__Zap__player__) */
