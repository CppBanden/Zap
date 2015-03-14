//
//  location.h
//  Zap
//
//  Created by Martin Fasterholdt on 09/03/15.
//
//

#ifndef __Zap__location__
#define __Zap__location__

#include <stdio.h>
#include "ofMain.h"

class Location
{
public:
    
    int x;
    int y;
    
    Location();
    Location(int x, int y);
    int value();
    
    static int getValue(int x, int y);
};
#endif /* defined(__Zap__location__) */
