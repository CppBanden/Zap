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
    world->draw(player->cameraPos);
    
    player->draw();
    
    //Debug outline
/*    if(false)
    {
        ofVec2f screenSize = Settings::getScreenSize();
        ofNoFill();
        //ofRect(0, 0, WorldCreator::worldWidth, WorldCreator::worldHeight);
        ofRect(screenSize.x / 2 - WorldCreator::worldWidth / 2, screenSize.y / 2 - WorldCreator::worldHeight / 2, WorldCreator::worldWidth, WorldCreator::worldHeight);
    }*/
    
    //Location GUI
    std::ostringstream s;
    s << "Location :" << world->location;
    ofDrawBitmapStringHighlight(s.str(), 15, 20);
    
    //Debug info
    if(true)
    {
        ofDrawBitmapStringHighlight(player->getDebugPos(), 15, 80);
        //printf("bright %f \n", level->getPixel(player->pos.x, player->pos.y).getBrightness() / 255);

        ofSetColor(world->getRockPixel(player->pos.x, player->pos.y));
        ofFill();
        ofDrawPlane(82, 115, 140, 20);
    }
}

bool ofApp::travel(int destination)
{
    world = worldCreator->createWorld(destination);
    
//    ofVec2f levelSize = WorldCreator::getWorldSize();
    
//    player = new Player(level, input, levelSize.x / 2, levelSize.y / 2);
    ofVec2f landingSpot = world->worldSize;
    landingSpot.x /= 2;
    landingSpot.y /= 2;
    landingSpot.x = 450;
    landingSpot.y = 900;

    player = new Player(world, input, landingSpot.x, landingSpot.y);
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
        travel(world->location + 1);
    }
    
    if(key == 'i')
        showEdge = !showEdge;
    
    if(key == '1')
        world->setZoom(1.5); //Current expected default zoom
    else if(key == '2')
        world->setZoom(world->zoom + 0.25f);
    else if(key == '3')
        world->setZoom(world->zoom - 0.25f);
    else if(key == '4')
        world->setZoom(world->zoom + 2);
    else if(key == '5')
        world->setZoom(world->zoom - 2);
    else if(key == '0')
        world->setZoom(35); //Really far away
    
    ///TODO should shoul entire level
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

