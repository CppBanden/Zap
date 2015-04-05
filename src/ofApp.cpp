#include "ofApp.h"

void ofApp::setup()
{
    ofSetFrameRate(Settings::frameRate);
    //Location startLocation(2564,1094);
    Location startLocation(100,100);
    
    input = new Input();
    worldCreator = new WorldCreator();
    map = new Map(startLocation, input);
    universeMap = new UniverseMap();
    
    player = new Player(input, 99.6f, 100.12f);
    
    setMapOverviewState();
}

void ofApp::setExploreState()
{
    if(map->selectedMapWorld != NULL)
    {
        travel(map->selectedMapWorld->location);
        
        state = Explore;
    }
}

void ofApp::setMapOverviewState()
{
    state = MapOverview;
}

void ofApp::setUniverseOverviewState()
{
    state = UniverseOverview;
}

void ofApp::update()
{
   if(state == Explore)
   {
       player->update();
   }
   else if(state == MapOverview)
   {
       player->updateMap();
   }
}

///TODO brightness + contrast for world generatorz

void ofApp::draw()
{
    if(state == Explore)
    {
        world->draw(player->cameraPos);
        
        player->draw();
        
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
    else if(state == MapOverview)
    {
        map->draw(player->cameraWorldPos);
        
        player->drawMap();
    }
    else if(state == UniverseOverview)
    {
        universeMap->draw(map->currentLocation);
    }
    
    //Location GUI
//    std::ostringstream s;
  //  s << "Location " << player->worldPos.x << "," << player->worldPos.y;
    //ofDrawBitmapStringHighlight(s.str(), 15, 20);
}

bool ofApp::travel()
{

}

bool ofApp::travel(Location location)
{
    int locationValue = location.value();
    
    world = worldCreator->createWorld(locationValue);
    
    //ofVec2f levelSize = WorldCreator::getWorldSize();
    //player = new Player(level, input, levelSize.x / 2, levelSize.y / 2);
    ofVec2f landingSpot = world->worldSize;
    landingSpot.x /= 2;
    landingSpot.y /= 2;
//    landingSpot.x = 460;
  //  landingSpot.y = 460;
    
    player->travel(world, landingSpot.x, landingSpot.y);
}

//--------------------------------------------------------------

float ageTest = 0;

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

    if(key == 'e')
    {
        input->button1Pressed = true;
        
        if(state == MapOverview)
            map->ping();
    }
    
    //Test Age
    if(key == 'r')
    {
        int locationValue = world->location;
        ageTest += 0.1f;
        world = worldCreator->createWorld(locationValue, ageTest);
    }
    else if(key == 'f')
    {
        int locationValue = world->location;
        ageTest -= 0.1f;
        world = worldCreator->createWorld(locationValue, ageTest);
    }
    
    if(key == 'o')
    {
        travel();
    }
    
    if(key == 'm')
    {
        if(state == MapOverview)
        {
            setExploreState();
        }
        else
        {
            setMapOverviewState();
        }
    }
    
    if(key == 'n')
    {
        if(state == UniverseOverview)
        {
            setMapOverviewState();
        }
        else
        {
            setUniverseOverviewState();
        }
    }
    
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

    ///TODO should show entire level
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
    
    if(key == 'e')
        input->button1Pressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
    input->mouseX = x;
    input->mouseY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if(state == MapOverview)
    {
        map->move();
    }
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

