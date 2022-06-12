#version 440
#pragma optimize(on)
uniform vec4 iMouse;
uniform vec3 iResolution;
uniform vec2 iAnt;

const int W = 1920;
const int H = 980;


layout(std430, binding = 0) buffer dcA1 { float A1 [  ]; };
layout(std430, binding = 1) buffer dcA2 { float A2 [  ]; };
layout(std430, binding = 2) buffer dcA3 { float A3 [  ]; };

layout(rgba8, binding=1) uniform writeonly image2D img; 
layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;


int per(int x, int nx) {
    if (x < 0) x += nx;
    if (x >= nx) x -= nx;
    return x;
}

vec4 color(float t)
{
    vec4 col;
    col.r = t;
    col.g = t;
    col.b = t;
    col.a = 1;
    return col;
}

float random(vec2 co) { return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453); }

void main() {

    int i = int(gl_GlobalInvocationID.x);
    int j = int(gl_GlobalInvocationID.y);

    //A2[Ant.x + Ant.y * W] == 0.0f;
    vec2 an = iAnt.xy;
    if (i == an.x && j == an.y && A1[i + j * W] == 0.0f) // (distance(vec2(i, j), vec2(an.x, an.y)) == 1.0f)
    {
        A1[i + j * W] = 1.0f;
        A3[i + j * W] = 1.0f;
    }
    else if (i == an.x && j == an.y && A1[i + j * W] == 1.0f)
    {
        A1[i + j * W] = 0.0f;
    }
    if (i == an.x && j == an.y)
        A3[(i + W / 2) + j * W] += 0.05f; // 1.0f;// 0.0255f; 
    /*if (distance(vec2(i, j), vec2(an.x, an.y)) <= 5.0f)
        if (distance(vec2(i, j), vec2(an.x, an.y)) <= 4.0f)
            if (distance(vec2(i, j), vec2(an.x, an.y)) <= 3.0f)
                if (distance(vec2(i, j), vec2(an.x, an.y)) <= 2.0f)
                    if (distance(vec2(i, j), vec2(an.x, an.y)) <= 1.0f)
                        A3[(i + W / 2) + j * W] += 1.0f;// 0.0255f; 
                    else
                        A3[(i + W / 2) + j * W] += 0.65f;// 0.0205f; 
                else
                    A3[(i + W / 2) + j * W] += 0.50f;// 0.0155f; 
            else
                A3[(i + W / 2) + j * W] += 0.35f;// 0.0105f; 
        else
            A3[(i + W / 2) + j * W] += 0.15f;// 0.0055f;*/

    /*
    vec2 M = iMouse.xy;// / iResolution.xy;
    if( iMouse.w > 0. ){
        if ( distance(vec2(i,j), vec2(M.x,M.y)) <= 15.0f) {
            A2[i+j*W] = 1.0f;
        }
    }
    */

    vec4 col = vec4(vec3(A1[i + j * W] * 255.0f), 1);
    if (A1[i + j * W] == A3[i + j * W])
        imageStore(img, ivec2(gl_GlobalInvocationID.xy), col);
    else {
        //float r = 255.0f, g = 1.0f, b = 1.0f;
        /* if (A3[i + j * W] <= 25) { g = 15.0f; }
         if (A3[i + j * W] > 25 && A3[i + j * W] <= 75) { g = 15.0f; b = 35.0f; }
         if (A3[i + j * W] > 125 && A3[i + j * W] <= 175) { r = 20.0f; g = 15.0f; b = 25.0f; }
         if (A3[i + j * W] > 175 && A3[i + j * W] <= 255) { r = 55.0f; g = 15.0f; b = 25.0f; }*/


        /*if (A3[i + j * W] <= 30.0f ) { r = 159.0f; g = 77.0f; b = 168.0f; }
        if (A3[i + j * W] > 30.0f && A3[i + j * W] <= 70) { r = 104.0f; g = 61.0f; b = 171.0f; }
        if (A3[i + j * W] > 70.0f && A3[i + j * W] <= 125.0f) { r = 5.0f; g = 37.0f; b = 181.0f; }
        if (A3[i + j * W] > 125.0f && A3[i + j * W] <= 150.0f) { r = 14.0f; g = 105.0f; b = 192.0f; }
        if (A3[i + j * W] > 150.0f) { r = 20.0f; g = 205.0f; b = 220.0f; }*/
  
        //col = vec4(vec3(A3[i + j * W] *, A3[i + j * W] * g, A3[i + j * W] * b), 1);
       /* r = (255.0f - r) / 255.0f;
        g = (255.0f - g) / 255.0f;
        b = (255.0f - b) / 255.0f;
        col = vec4(vec3(r, g, b), 1);*/

        if (A3[i + j * W] <= 0.1) col = vec4(vec3(0.945, 0.968, 0.933), 1);
        if (A3[i + j * W] > 0.1 && A3[i + j * W] <= 0.2) col = vec4(vec3(0.835, 0.901, 0.8), 1);
        if (A3[i + j * W] > 0.2 && A3[i + j * W] <= 0.3) col = vec4(vec3(0.725, 0.839, 0.666), 1);
        if (A3[i + j * W] > 0.3 && A3[i + j * W] <= 0.4) col = vec4(vec3(0.611, 0.772, 0.529), 1);
        if (A3[i + j * W] > 0.4 && A3[i + j * W] <= 0.5) col = vec4(vec3(0.501, 0.705, 0.396), 1);
        if (A3[i + j * W] > 0.5 && A3[i + j * W] <= 0.6) col = vec4(vec3(0.4, 0.607, 0.294), 1);
        if (A3[i + j * W] > 0.6 && A3[i + j * W] <= 0.7) col = vec4(vec3(0.309, 0.047, 0.227), 1);
        if (A3[i + j * W] > 0.7 && A3[i + j * W] <= 0.8) col = vec4(vec3(0.223, 0.341, 0.160), 1);
        if (A3[i + j * W] > 0.8 && A3[i + j * W] <= 0.9) col = vec4(vec3(0.133, 0.203, 0.098), 1);
        if (A3[i + j * W] > 0.9 && A3[i + j * W] <= 1.0) col = vec4(vec3(0.047, 0.070, 0.031), 1);
        if (A3[i + j * W] > 1.0) col = vec4(vec3(0.474, 0.227, 0.309), 1);
       /* '#F1F7EE' 0.0   0.945, 0.968, 0.933
        '#D5E6CC' 0.1   0.835, 0.901, 0.8
        '#B9D6AA' 0.2   0.725, 0.839, 0.666
        '#9CC587' 0.3   0.611, 0.772, 0.529
        '#80B465' 0.4   0.501, 0.705, 0.396
        '#669B4B' 0.5   0.4, 0.607, 0.294
        '#4F793A' 0.6   0.309, 0.047, 0.227
        '#395729' 0.7   0.223, 0.341, 0.160
        '#223419' 0.8   0.133, 0.203, 0.098
        '#0C1208' 0.9   0.047, 0.070, 0.031
        '#793A4F' 1.0   0.474, 0.227, 0.309*/

        imageStore(img, ivec2(gl_GlobalInvocationID.xy), col); 
    }
}