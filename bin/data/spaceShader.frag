#version 150

out vec4 outputColor;
uniform vec2 worldSize;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{    
    float color = 0.0;

    if (rand(gl_FragCoord.xy / worldSize.xy) > 0.9986)
        color = rand(gl_FragCoord.xy);

    outputColor = vec4(vec3(color), 1.0);
}