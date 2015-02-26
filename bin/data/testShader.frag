#version 150

uniform sampler2DRect imageMask;
uniform vec3 randomColor;

out vec4 outputColor;

void main()
{
    vec2 w = vec2(gl_FragCoord.x, gl_FragCoord.y); ///TODO Move to generator
    vec4 texel = texture(imageMask, w.xy);
    
    vec4 c = vec4(randomColor.xyz, texel.x);

    outputColor = c;
}