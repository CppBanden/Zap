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
    
    vec4 c = vec4(randomColor.xyz, texel.x);

    outputColor = c;
}