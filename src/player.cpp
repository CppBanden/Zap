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

Player::Player(World *l, Input *i, int x, int y)
{
    level = l;
    input = i;
    
    pos.x = x;
    pos.y = y;
    
    cameraPos.x = x;
    cameraPos.y = y;
    
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
    
    ///TODO very little control and barely any friction in open space
    
    //Wall friction
    ofColor currentColor = level->getPixel(pos.x, pos.y);
    float currentAlpha = currentColor.a / 255.0f;

    if(currentAlpha > 0.1f)
    {
        velocity -= velocity * wallFriction * currentAlpha;
        fuel -= fuelDrainDig * currentAlpha;
    }
    
    ///TODO dig ahead of player instead of current pixel
    //Dig
    if(currentAlpha != 0)
    {
        float nextAlpha = currentAlpha - digSpeed;
        
        if(currentAlpha > 0.1f && nextAlpha < 0.1f)
            nextAlpha = 0.1f;
        
        if(nextAlpha < 0)
            nextAlpha = 0;
        
        ofColor nextColor = currentColor;

        nextColor.a = nextAlpha * 255;
        
        level->setPixel(pos.x, pos.y, nextColor);
        
        ///TODO larger digging area
        ///TODO fixe digging edges
/*        level->fadePixel(pos.x+1, pos.y, digSpeedEdge);
        level->fadePixel(pos.x-1, pos.y, digSpeedEdge);
        level->fadePixel(pos.x, pos.y+1, digSpeedEdge);
        level->fadePixel(pos.x, pos.y-1, digSpeedEdge);*/

        level->updateImage();
    }
    
    float speed = velocity.length();
    
    //Max speed
    if(speed > maxMoveSpeed)
        velocity = velocity.normalized() * maxMoveSpeed;
    
    if(moveDir.x == 0 && moveDir.y == 0 && speed < 0.002)
        velocity = ofVec2f::zero();

    pos += velocity;
    
    ofVec2f previousPos = pos;
    
    level->wrapPosition(&pos);
    
    //Camera follow
    cameraPos.x += pos.x - previousPos.x;
    cameraPos.y += pos.y - previousPos.y;
    
    cameraPos += (pos - cameraPos) * cameraFollowSpeed;
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
        
        ///TODO zoom dependent size, probably a general system
        float ratio = (screenSize.x / level->zoomSize.x);
        
        ofVec2f drawPos;
        drawPos.x = (level->drawArea.x - size) / 2;
        drawPos.x += (pos.x - cameraPos.x) * ratio;
        
        drawPos.y = (level->drawArea.y - size) / 2;
        drawPos.y += (pos.y - cameraPos.y) * ratio;
        
        image.drawSubsection(drawPos.x, drawPos.y, size, size, 3 * currentFrame, 0, 3, 3);
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

