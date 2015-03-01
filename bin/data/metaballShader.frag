#version 150

uniform vec2 worldSize;
uniform vec2 screenSize;

out vec4 outputColor;

#define NUM_BALLS 100

uniform vec3 metaballs[NUM_BALLS];

void main( void )
{
    float ratio = worldSize.y / worldSize.x;
    float divider = 25; //outter
    float intensity = 10; //inner

    float coordX = gl_FragCoord.x / worldSize.x;
    float coordY = gl_FragCoord.y / worldSize.x;

    float sum = 0.0f;
    
    for(int i=0; i<NUM_BALLS; ++i)
    {
        vec3 testBall = metaballs[i];
        
        float x = testBall.x;
        float y = testBall.y;//(screenSize.y - worldSize.y) / worldSize.y + testBall.y; //Move to generator
        float z = testBall.z; //size
        
        vec3 b = vec3(x, y * ratio, z);
        
        float distX = abs(b.x - coordX);
        float distY = abs(b.y - coordY);
        
        //Cubic Distance
        float norm = 2.35;
        distX = pow(distX, norm);
        distY = pow(distY, norm);
        sum += z / (distX + distY);
        
        //Spherical Distance
        //float dist = distance(b.xy, vec2(coordX, coordY));
        //sum += z / dist;
    }

    sum = pow(sum / intensity, divider);
   
    if(sum < 1)
        sum = 0;
    
    //Clamp
/*    if(sum < 1 && sum > 0.1)
    {
        sum = fract(sin(dot(gl_FragCoord.xy, vec2(12.9898,78.233))) * 43758.5453) * sum * 1.25;
        
        if(sum > 0.4)
            sum = 1;
        else
            sum = 0;
    }*/
    
    outputColor = vec4(1, 1, 1, sum);
}








