#version 150

uniform vec3 randomColor;
uniform sampler2DRect imageMask;
uniform sampler2DRect imageRocks;

out vec4 outputColor;

void main()
{
    vec2 w = vec2(gl_FragCoord.x, gl_FragCoord.y);
    vec4 texel = texture(imageMask, w.xy);
    vec4 texelRocks = texture(imageRocks, w.xy);
    
    float alpha = 1;
    
    if(texel.w < 0.001f)
        alpha = 0;
    
    vec4 c = vec4(randomColor.xyz, texel.w);
//    vec4 c = vec4(randomColor.xyz, texel.w);
//    c = texel;
    outputColor = c;
}