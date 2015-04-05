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
    static ofVec2f drawWorldPos;
    
    ofVec2f worldPos;
    ofVec2f cameraWorldPos;
    
    ofVec2f pos;
    ofVec2f cameraPos;
    
    ofVec2f velocity;
    ofImage image;
    bool infiniteFuel = false;
    
    Input *input;
    World *level;
    
    float size = 20;
    float fuel = 100;
    
    //Grounded Velocity
    float moveSpeed = 0.013f; //0.004;
    float maxMoveSpeed = 0.5f;
    float friction = 0.0035f; //0
    float fuelDrainMove = 0.0006f;
    float fuelDrainDig = 0.35f;
    
    //Floating Velocity
    float moveSpeedFloating = 0.008;
    float frictionFloating = 0;
    float maxMoveSpeedFloating = 0.7f;
    float fuelDrainMoveFloating = 0.0003f;
    
    //Map Velocity
    float moveSpeedMap = 0.000008;
    float frictionMap = 0.0000002;
    float maxMoveSpeedMap = 0.0006;

    //Digging
    float wallFriction = 0.5f;
    float digSpeed = 0.05f;
    float digSpeedEdge = 0.005f;
    
    //Visuals
    int frame;
    int totalFrames = 13;
    int fps = 4;
  
    //Camera
    float cameraFollowSpeed = 0.045f;
    
    Player(Input *i, float x, float y);

    void draw();
    void drawMap();
    void update();
    void updateMap();
    void travel(World *world, int x, int y);
    void useFuel(float amount);

    std::string getDebugPos();
};

#endif /* defined(__Zap__player__) */
