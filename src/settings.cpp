//
//  settings.cpp
//  Sap
//
//  Created by Martin Fasterholdt on 10/02/15.
//
//

#include "settings.h"

ofVec2f Settings::getScreenSize()
{
    ofVec2f size;
    
    //if(fullScreen)
    {
        size.x = ofGetWidth();
        size.y = ofGetHeight();
    }
    /*else
    {
        size.x = defaultScreenWidth;
        size.y = defaultScreenHeight;
    }*/
    
    return size;
}
