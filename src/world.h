//
//  level.h
//  Sap
//
//  Created by Martin Fasterholdt on 07/02/15.
//
//

#ifndef __Sap__level__
#define __Sap__level__

#include <stdio.h>
#include "ofMain.h"
#include "settings.h"

class World
{
public:
    static float zoom;
    
    ofImage imageRocks;
    ofImage imageSurface;
    ofShader spaceShader;
    ofVec2f worldSize;
    ofVec2f zoomSize;
    ofVec2f drawArea;
    
    int location;

    World(ofImage rocks, ofImage surface, int locationInput);
    
    void setupImage(ofImage *image);
    void draw(ofVec2f pos);
    void setPixel(int x, int y, ofColor color);
    void fadePixel(int x, int y, float amount);
    void updateImage();
    void wrapPosition(ofVec2f *pos);
    void generateLevel();
    ofVec2f getWorldSize();
    ofColor getPixel(int x, int y);
    void setZoom(float zoom);
};

#endif /* defined(__Sap__level__) */
