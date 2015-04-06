//
//  utils.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 06/04/15.
//
//

#include "utils.h"

ofVec2f Utils::mapRenderPos;
ofVec2f Utils::mapCameraPos;
float Utils::mapUnitSize;

ofVec2f Utils::getMapDrawPos(ofVec2f pos)
{
    ofVec2f drawPos;
    drawPos.x = mapRenderPos.x +(pos.x - mapCameraPos.x) * mapUnitSize;
    drawPos.y = mapRenderPos.y +(pos.y - mapCameraPos.y) * mapUnitSize;
    
    return drawPos;
}

ofVec2f Utils::getMapDrawPos(ofVec2f pos, float size)
{
    ofVec2f drawPos;
    drawPos.x = mapRenderPos.x +(pos.x - mapCameraPos.x) * mapUnitSize - size / 2;
    drawPos.y = mapRenderPos.y +(pos.y - mapCameraPos.y) * mapUnitSize - size / 2;
    
    return drawPos;
}
