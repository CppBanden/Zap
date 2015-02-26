#version 150

uniform vec3 randomColor;
uniform float time;
uniform vec2 wrapSize;
uniform float test;

uniform float width = 200;
uniform float height = 150;

out vec4 outputColor;

vec4 mod289(vec4 x)
{
    return x - floor(x * (1.0 / 289)) * 289;
}

vec4 wrap(vec4 v)
{
     //Width and height must be factors of wrapSize
    float x = wrapSize.x / width;
    float y = wrapSize.y / height;
    
    v.x = v.x - floor(v.x * (1.0 / x)) * x;
    v.y = v.y - floor(v.y * (1.0 / y)) * y;
    v.z = v.z - floor(v.z * (1.0 / x)) * x;
    v.w = v.w - floor(v.w * (1.0 / y)) * y;
    
    return v;
}

vec4 permute(vec4 x)
{
    return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
    return 1.79284291400159 - 0.85373472095314 * r;
}

vec2 fade(vec2 t)
{
    return t*t*t*(t*(t*6.0-15.0)+10.0);
}

// Classic Perlin noise
float cnoise(vec2 P)
{
    vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
    vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
    Pi = wrap(Pi);
    //Pi = mod289(Pi); // To avoid truncation effects in permutation
    
    vec4 ix = Pi.xzxz;
    vec4 iy = Pi.yyww;
    vec4 fx = Pf.xzxz;
    vec4 fy = Pf.yyww;

    vec4 i = permute(permute(ix) + iy);
    
    vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
    vec4 gy = abs(gx) - 0.5 ;
    vec4 tx = floor(gx + 0.5);
    gx = gx - tx;
    
    vec2 g00 = vec2(gx.x,gy.x);
    vec2 g10 = vec2(gx.y,gy.y);
    vec2 g01 = vec2(gx.z,gy.z);
    vec2 g11 = vec2(gx.w,gy.w);
    
    vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
    g00 *= norm.x;
    g01 *= norm.y;
    g10 *= norm.z;
    g11 *= norm.w;
    
    float n00 = dot(g00, vec2(fx.x, fy.x));
    float n10 = dot(g10, vec2(fx.y, fy.y));
    float n01 = dot(g01, vec2(fx.z, fy.z));
    float n11 = dot(g11, vec2(fx.w, fy.w));
    
    vec2 fade_xy = fade(Pf.xy);
    vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
    float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
    
    return 2.3f * n_xy;
}


float fbmOld(vec2 P)
{
    int octaves = 7;//7
    float lacunarity = 2.5;//2.5;//2.5;//2.5;
    float gain = 1;
    
    float sum = 0.05;//2; //Offset, density
    float amp = 0.2f;//1; //test / 2;//1.0;
    vec2 pp = P;
    
    int i;
    
    for(i = 0; i < octaves; i+=1)
    {
        amp *= gain;
        
        vec2 t = pp * pow(2, i);
        sum += amp * pow(0.5, i) * cnoise(t);
        
        //sum += amp * cnoise(pp);
        //pp *= lacunarity;
    }
    
    return sum;
}
//Kamen Fbm
float fbm(vec2 P, int octaves, float lacunarity, float gain)
{
    float sum = 0.0;
    float amp = 1.0;
    vec2 pp = P;
    
    lacunarity = 1.5;
    float lowLacunarity = 0.6;
    
    
    int i;
    
    for(i = 0; i < octaves; i+=1)
    {
        amp *= gain;
        vec2 t = pp * pow(2, i);
        sum += amp * pow(lowLacunarity, i) * cnoise(t);
        
        pp *= lacunarity;
    }
    
    return sum;
}

//Quilez
float fbmQ(vec2 P)
{
    int octaves = 12;
    float lacunarity = 1.5;//2.5;
    float gain = 0.45;
    
    float sum = 0.05;//2; //Offset, density
    float amp = 1.0; //test / 2;//1.0;
    vec2 pp = P;
    
    int i;
    
    float lowLacunarity = 0.6f;
    
    for(i = 0; i < octaves; i+=1)
    {
        amp *= gain;
        
        vec2 t = pp * pow(2, i);
        sum += amp * pow(lowLacunarity, i) * cnoise(t);
        
        pp *= lacunarity;
    }
    
    return sum;
}

//Kamen pattern
float pattern( in vec2 p, out vec2 q, out vec2 r , in float time)
{
    float l = 2.3;
    float g = 0.4;
    int oc = 10;
    
    q.x = fbm( p + vec2(time,time),oc,l,g);
    q.y = fbm( p + vec2(5.2*time,1.3*time) ,oc,l,g);
    
    r.x = fbm( p + 4.0*q + vec2(1.7,9.2),oc,l,g );
    r.y = fbm( p + 4.0*q + vec2(8.3,2.8) ,oc,l,g);
    
    return fbm( p + 4.0*r ,oc,l,g);
}

void main()
{
    /*vec2 q = gl_FragCoord.xy / vec2(width, height);
    
    vec2 p = -1.0 + 2.0 * q;
    vec2 qq;
    vec2 r;
    float color = pattern(p,qq,r,time);
    
    vec4 c = vec4(randomColor.x, randomColor.y, randomColor.z, color * 2.5f);*/
    
    vec2 p = gl_FragCoord.xy / vec2(width, height);
    
    //Level 3
    vec2 q = vec2 ( fbmQ(p), fbmQ( p + vec2(5.2f * time, 1.3f * time)));
    
    float qA = 4.0;
    vec2 r = vec2 ( fbmQ(p + qA * q + vec2(1.7, 9.2)),
                   fbmQ( p + qA * q + vec2(8.3f, 2.8f)));
    
    float result = fbmQ(p + qA * r);
    
    vec4 c = vec4(randomColor.xyz, result);
    c *= 2.5;
    
    //--Noise
    //float color = cnoise(p);
    //vec4 c = vec4(1, 1, 1, color * 3.2f);
    
    //--Fbm
    //float color = fbm(p, 10, 0, 0.7f);
    //vec4 c = vec4(1, 1, 1, color * 3.2f);
    
    outputColor = c;
}