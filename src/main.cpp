#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"
#include "settings.h"

//========================================================================
int main( )
{
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    
    if(Settings::fullScreen)
    {
        ofSetupOpenGL(800, 600, OF_FULLSCREEN);
    }
    else
    {
        ofSetupOpenGL(Settings::defaultScreenWidth, Settings::defaultScreenHeight, OF_WINDOW);
    }
    
    ofRunApp(new ofApp());

}
