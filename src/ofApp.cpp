#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(Settings::frameRate);

    input = new Input();
    
    worldCreator = new WorldCreator();

    nextLocation = WorldCreator::defaultLocation;
}

void ofApp::update()
{
    if(nextLocation == -1)
        player->update();
}

void ofApp::draw()
{
    //Create world
    if(nextLocation != -1)
    {
        level = worldCreator->createWorld(nextLocation);
        ofVec2f levelSize = WorldCreator::getWorldSize();
        player = new Player(level, input, levelSize.x / 2, levelSize.y / 2);
        
        nextLocation = -1;
    }
    
    ofVec2f screenSize = Settings::getScreenSize();
    
    ofVec2f worldSize = level->getWorldSize();
    int worldScale = Settings::worldScale;
    
    ofVec2f renderPos;
    renderPos.x = player-> pos.x - (screenSize.x / 2 / worldScale);
    renderPos.y = player-> pos.y - (screenSize.y / 2 / worldScale);

    ofSetColor(0, 0, 0);
    ofRect(0, 0, screenSize.x, screenSize.y);
    //***Possible blend offset to make camera blend?

    ofSetColor(255);
    level->image.drawSubsection(0, 0, screenSize.x, screenSize.y, renderPos.x, renderPos.y, screenSize.x / worldScale, screenSize.y / worldScale);

    ofSetColor(255);
    player->draw();
    
    if(false)
    {
        ofNoFill();
        //ofRect(0, 0, WorldCreator::worldWidth, WorldCreator::worldHeight);
        ofRect(screenSize.x / 2 - WorldCreator::worldWidth / 2, screenSize.y / 2 - WorldCreator::worldHeight / 2, WorldCreator::worldWidth, WorldCreator::worldHeight);
    }

    //Location GUI
    std::ostringstream s;
    s << "Location :" << level->location;
    ofDrawBitmapStringHighlight(s.str(), 15, 20);
    
    //Debug info
    if(true)
    {
        ofDrawBitmapStringHighlight(player->getDebugPos(), 15, 80);
        //printf("bright %f \n", level->getPixel(player->pos.x, player->pos.y).getBrightness() / 255);

        ofSetColor(level->getPixel(player->pos.x, player->pos.y));
        ofFill();
        ofDrawPlane(82, 115, 140, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == 'd' || key == OF_KEY_RIGHT)
        input->rightPressed = true;
    else if(key == 'a' || key == OF_KEY_LEFT)
        input->leftPressed = true;
    else if(key == 'w' || key == OF_KEY_UP)
        input->upPressed = true;
    else if(key == 's' || key == OF_KEY_DOWN)
        input->downPressed = true;

    if(key == 'o')
    {
        nextLocation = 0;
    }
    else if(key == 'p')
    {
        nextLocation = level->location + 1;
    }
    
    if(key == 'i')
        showEdge = !showEdge;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if(key == 'd' || key == OF_KEY_RIGHT)
        input->rightPressed = false;
    else if(key == 'a' || key == OF_KEY_LEFT)
        input->leftPressed = false;
    else if(key == 'w' || key == OF_KEY_UP)
        input->upPressed = false;
    else if(key == 's' || key == OF_KEY_DOWN)
        input->downPressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

