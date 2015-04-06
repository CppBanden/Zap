#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"
#include "settings.h"

//========================================================================
int main( )
{
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    
    bool fullScreen = false;
    int defaultScreenWidth = 1600;//800;//1600;
    int defaultScreenHeight = 900;//450;//900;
    
    if(fullScreen)
    {
        ofSetupOpenGL(800, 600, OF_FULLSCREEN);
    }
    else
    {
        ofSetupOpenGL(defaultScreenWidth, defaultScreenHeight, OF_WINDOW);
        //ofSetupOpenGL(Settings::defaultScreenWidth, Settings::defaultScreenHeight, OF_WINDOW);
    }
    
    ofRunApp(new ofApp());

}
