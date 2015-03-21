//
//  location.cpp
//  Zap
//
//  Created by Martin Fasterholdt on 09/03/15.
//
//

#include "location.h"

Location::Location()
{
}

Location::Location(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Location::value()
{
/*    if(x == 0)
        return y;

    if(x > 0)
    {
        return x + abs(y) + 10000;
    }
    else
    {
        return x + y - 10000;
    }
    
    0, 0 = 0
    0, 1 = 1
    0, 500, 500
    0, -12 = -12
    
    1, 0 = 10000
    1, 1 = 10001
    1, 50 = 10050
    -1, 0 = -1
    -1, -1*/
    
  //  -9999 -> 9999
//    0 -> 19998
    
    ///TODO check if this works for handling coordinates, something is fishy
    return ofSign(y) * (((x + 9999) * 10000) + abs(y));
    
    ///TODO 0,0 is currently strange as well as a horizontal line
    
    //return x * 10000 + y;
}

int Location::getValue(int x, int y)
{
    return ofSign(y) * (((x + 9999) * 10000) + abs(y));
    
    //return x * 10000 + y;
}