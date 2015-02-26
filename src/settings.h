//
//  settings.h
//  Sap
//
//  Created by Martin Fasterholdt on 10/02/15.
//
//

#ifndef __Sap__settings__
#define __Sap__settings__

#include <stdio.h>
#include "ofMain.h"

class Settings
{
public:
    
    static const bool fullScreen = false;
    
    static const int defaultScreenWidth = 1300;//1610;
    static const int defaultScreenHeight = 700;//900;
    
    static const int worldScale = 8;
    static const int frameRate = 60;
    
    static ofVec2f getScreenSize();

};

#endif /* defined(__Sap__settings__) */