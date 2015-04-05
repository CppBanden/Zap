//
//  item.h
//  Zap
//
//  Created by Martin Fasterholdt on 14/03/15.
//
//

#ifndef __Zap__item__
#define __Zap__item__

#include <stdio.h>
#include "ofMain.h"

class Item
{
public:
    
    int x;
    int y;
    ofColor color;
    
    Item(int x, int y, ofColor color);
    void draw();
};
#endif /* defined(__Zap__item__) */
