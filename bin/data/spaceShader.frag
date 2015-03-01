#version 150

#define M_PI 3.1415926535897932384626433832795

out vec4 outputColor;
uniform vec2 worldSize;           // viewport resolution (in pixels)
uniform float iGlobalTime;           // shader playback time (in seconds)

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
    float size = 30.0;
    float prob = 0.95;
    
    vec2 pos = floor(1.0 / size * gl_FragCoord.xy);
    
    float color = 0.0;
    float starValue = rand(pos);
    
/*    if (starValue > prob)
    {
        vec2 center = size * pos + vec2(size, size) * 0.5;
        
        float t = 0.9 + 0.2 * sin(iGlobalTime + (starValue - prob) / (1.0 - prob) * 45.0);
        
        color = 1.0 - distance(gl_FragCoord.xy, center) / (0.5 * size);
        color = color * t / (abs(gl_FragCoord.y - center.y)) * t / (abs(gl_FragCoord.x - center.x));
    }
    else*/ if (rand(gl_FragCoord.xy / worldSize.xy) > 0.9996)
    {
        float r = rand(gl_FragCoord.xy);
        color = r;// * (0.25 * sin(iGlobalTime * (r * 5.0) + 720.0 * r) + 0.75);
    }
    
    outputColor = vec4(vec3(color), 1.0);
}