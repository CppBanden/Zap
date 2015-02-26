//
//  player.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 07/02/15.
//
//

#include <math.h>
#include "ofApp.h"
#include "player.h"

Player::Player(Level *l, Input *i, int x, int y)
{
    level = l;
    input = i;
    pos.x = x;
    pos.y = y;

    image.loadImage("images/player_01.png");
    image.getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    totalFrames = image.width/image.height;
}

void Player::update()
{
    //Move direction
    ofVec2f moveDir;

    if(input->rightPressed)
        moveDir.x = 1;
    else if(input->leftPressed)
        moveDir.x = -1;
    
    if(input->upPressed)
        moveDir.y = -1;
    else if(input->downPressed)
        moveDir.y = 1;
    
    //Acceleration
    if(fuel > 0 && (moveDir.x != 0 || moveDir.y != 0))
    {
        velocity += moveDir.normalize() * moveSpeed;
        fuel -= fuelDrainMove;
    }

    //Friction
    velocity -= velocity.normalized() * friction;

    //Wall friction
    ofColor currentColor = level->getPixel(pos.x, pos.y);
//    float currentBrightness = currentColor.getBrightness() / 255;
    float currentAlpha = currentColor.a / 255.0f;
    
    if(currentAlpha > 0.2f)
    {
        velocity -= velocity * wallFriction * currentAlpha;
        fuel -= fuelDrainDig * currentAlpha;
    }
    
    //Dig
    if(currentAlpha != 0)
    {
        float nextBrightness = currentAlpha - digSpeed;
        
        if(currentAlpha > 0.2f && nextBrightness < 0.2f)
            nextBrightness = 0.2f;
        
        if(currentAlpha < 0)
            currentAlpha = 0;
        
        ofColor nextColor = currentColor;
        nextColor.setBrightness(nextBrightness * 255);
        
        level->setPixel(pos.x, pos.y, nextColor);
        
        ///TODO larger digging area
        level->fadePixel(pos.x+1, pos.y, digSpeedEdge);
        level->fadePixel(pos.x-1, pos.y, digSpeedEdge);
        level->fadePixel(pos.x, pos.y+1, digSpeedEdge);
        level->fadePixel(pos.x, pos.y-1, digSpeedEdge);

        level->updateImage();
    }
    
    float speed = velocity.length();
    
    //Max speed
    if(speed > maxMoveSpeed)
        velocity = velocity.normalized() * maxMoveSpeed;
    
    if(moveDir.x == 0 && moveDir.y == 0 && speed < 0.002)
        velocity = ofVec2f::zero();

    pos += velocity;
    
    level->wrapPosition(&pos);
}

void Player::draw()
{
    ofVec2f screenSize = Settings::getScreenSize();

    ///TODO smooth camera follow
    //ofDrawPlane(pos.x, pos.y, 10, 10);
    
    if(fuel > 0)
    {
        ///TODO handle frame counting
        int currentFrame = (int)((ofGetFrameNum() / (float)Settings::frameRate) * fps) % totalFrames;
        image.drawSubsection((screenSize.x - size) / 2, (screenSize.y - size) / 2, size, size, 3 * currentFrame, 0, 3, 3);
    }

    //Fuel bar small background
    ofSetColor(40, 40, 50);
    ofFill();
    ofDrawPlane(10 + 160 / 2, 45, 168, 23);
    
    
    //Fuel bar small
    ofSetColor(100, 100, 100);
    ofFill();
    float remainingFuel =  160 * (fuel / 100);
    ofDrawPlane(10 + remainingFuel / 2, 45, remainingFuel, 15);
}

std::string Player::getDebugPos()
{
    std::ostringstream s;
    s << "Player pos : ";
    s << round(pos.x);
    s << ", ";
    s << round(pos.y);

    return s.str();
}

