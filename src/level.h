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

class Level
{
public:
    
    ofImage image;
    ofVec2f worldSize;
    int location;
    
    Level(string filename);
    Level(ofImage i, int locationInput);
    
    void SetupImage(ofImage i);
    void setPixel(int x, int y, ofColor color);
    void fadePixel(int x, int y, float amount);
    void updateImage();
    void wrapPosition(ofVec2f *pos);
    void wrapPosition(int *x, int *y);
    
    ofVec2f getWorldSize();
    ofColor getPixel(int x, int y);
    
    void generateLevel();
};

#endif /* defined(__Sap__level__) */
