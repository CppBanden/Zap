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
        ofVec2f screenSize = Settings::getScreenSize();
        ofSetupOpenGL(screenSize.x, screenSize.y, OF_WINDOW);
    }
    
    ofRunApp(new ofApp());

}
