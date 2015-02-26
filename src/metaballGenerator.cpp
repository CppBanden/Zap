//
//  metaBallGenerator.cpp
//  Sap
//
//  Created by Martin Fasterholdt on 15/02/15.
//
//

#include "metaballGenerator.h"
#include "worldCreator.h"

MetaballGenerator::MetaballGenerator()
{

}

ofTexture MetaballGenerator::generate()
{
    if(!metaballShader.isLoaded())
        metaballShader.load("metaballShader");
    
    ofVec2f worldSize = WorldCreator::getWorldSize();
    float minSize = 0.001f;
    float maxSize = 0.01f;
    float border = 0.15f;
    
    int metaBallCount = 40;
    ofVec3f metaballs[40];
    
    for(int i = 0; i < metaBallCount; ++i)
    {
        float x = ofRandom(border, 1-border);
        float y = ofRandom(border, 1-border);
        float size = ofRandom(minSize, maxSize);
        metaballs[i] = ofVec3f( x, y, size);
    }
    
    ofFbo fbo;

    fbo.allocate(worldSize.x, worldSize.y, GL_RGBA);
    fbo.setDefaultTextureIndex(0);
    fbo.begin();
    
        ofClear(255,255,255, 0);
        ofSetColor(0);
        ofRect(0,0,worldSize.x, worldSize.y);
    
        metaballShader.begin();

        metaballShader.setUniform3fv("metaballs", &metaballs[0].x, metaBallCount);
        metaballShader.setUniform2f("worldSize", worldSize.x, worldSize.y);

        ofVec2f screenSize = Settings::getScreenSize();
        metaballShader.setUniform2f("screenSize", screenSize.x, screenSize.y);


        ofRect(0,0, worldSize.x, worldSize.y);
    
        metaballShader.end();
    
    fbo.end();

    return fbo.getTextureReference();
}