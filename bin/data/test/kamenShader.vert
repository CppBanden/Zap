#version 150

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
uniform float time;

in vec4 position;

void main()
{
//    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = modelViewProjectionMatrix * position;
}