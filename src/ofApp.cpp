#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(Settings::frameRate);

    input = new Input();
    
    worldCreator = new WorldCreator();

    travel(WorldCreator::defaultLocation);
}

void ofApp::update()
{
    player->update();
}

void ofApp::draw()
{
    level->draw(player->cameraPos);
    
    player->draw();
    
    //Debug outline
    if(false)
    {
        ofVec2f screenSize = Settings::getScreenSize();
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

bool ofApp::travel(int destination)
{
    level = worldCreator->createWorld(destination);
    
    ofVec2f levelSize = WorldCreator::getWorldSize();
    
//    player = new Player(level, input, levelSize.x / 2, levelSize.y / 2);
    player = new Player(level, input, 50, levelSize.y / 2);
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
        travel(0);
    }
    else if(key == 'p')
    {
        travel(level->location + 1);
    }
    
    if(key == 'i')
        showEdge = !showEdge;
    
    if(key == '1')
        level->setZoom(2);
    else if(key == '2')
        level->setZoom(2.5);
    else if(key == '3')
        level->setZoom(3);
    else if(key == '4')
        level->setZoom(3.5);
    else if(key == '5')
        level->setZoom(4);
    else if(key == '6')
        level->setZoom(4.5);
    else if(key == '0')
        level->setZoom(15);
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
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

