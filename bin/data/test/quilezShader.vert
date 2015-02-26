#version 150

uniform mat4 modelViewProjectionMatrix;
uniform float time;

in vec4 position;

void main()
{
    gl_Position = modelViewProjectionMatrix * position;
}