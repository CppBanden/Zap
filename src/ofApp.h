#pragma once

#include "ofMain.h"
#include "player.h"
#include "input.h"
#include "world.h"
#include "settings.h"
#include "worldCreator.h"
#include "map.h"
#include "mapWorld.h"
#include "location.h"

class ofApp : public ofBaseApp
{
public:
    enum State{Explore, MapOverview};
    
    State state;
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
    
    bool travel();
    bool travel(Location location);    
    
    Input *input;
    World *world;
    Player *player;
    Map *map;
    WorldCreator *worldCreator;
};
