#pragma once

#include "ofMain.h"
#include "player.h"
#include "input.h"
#include "level.h"
#include "settings.h"
#include "worldCreator.h"

class ofApp : public ofBaseApp
{
public:
    int nextLocation;
    bool showEdge = false;
    static int mouseX;
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofColor getPixel();
    
    Input *input;
    Level *level;
    Player *player;
    WorldCreator *worldCreator;
};
