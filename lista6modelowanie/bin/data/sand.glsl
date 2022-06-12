#version 440
#pragma optimize(on)
uniform vec4 iMouse;
uniform vec3 iResolution;
uniform int iStep;
uniform float iKey;
uniform int iTime;
uniform int iLos;
const int W = 1920;
const int H = 980;


layout(std430, binding = 0) buffer dcA1 { int A1 [  ]; };
layout(std430, binding = 1) buffer dcA2 { int A2 [  ]; };
layout(std430, binding = 2) buffer dcG { int G [  ]; };
layout(std430, binding = 4) buffer dcW1 { int W1 [  ]; };
layout(std430, binding = 5) buffer dcW2 { int W2 [  ]; };
layout(std430, binding = 6) buffer dcSS { int SS [  ]; };
//layout(std430, binding = 3) buffer dcR { float R [  ]; };

layout(rgba8, binding = 3) uniform writeonly image2D img;
layout(local_size_x = 6, local_size_y = 6, local_size_z = 1) in;


int per(int x, int nx)
{
    if (x < 0) x += nx;
    if (x >= nx) x -= nx;
    return x;
}

float per(float x, float nx)
{
    if (x < 0.0f) x += nx;
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

float random(vec2 co) { return fract(sin(dot(co.xy + iTime, vec2(12.9898, 78.233))) * 43758.5453); }

void PushWater(int ul, int ur, int ll, int lr)
{
    if (A1[ul] == 1 && W1[ul] == 1)
    {
        if (A1[ll] == 0 && W1[ll] == 0) { W2[ul] = 0; W2[ll] = 1; }
        else if (A1[lr] == 0 && W1[lr] == 0) { W2[ul] = 0; W2[lr] = 1; }
        else if (A1[ur] == 0 && W1[ur] == 0) { W2[ul] = 0; W2[ur] = 1; }
    }
    if (A1[ll] == 1 && W1[ll] == 1)
    {
        if (A1[ul] == 0 && W1[ul] == 0) { W2[ll] = 0; W2[ul] = 1; }
        else if (A1[lr] == 0 && W1[lr] == 0) { W2[ll] = 0; W2[lr] = 1; }
        else if (A1[ur] == 0 && W1[ur] == 0) { W2[ll] = 0; W2[ur] = 1; }
    }
    if (A1[lr] == 1 && W1[lr] == 1)
    {
        if (A1[ul] == 0 && W1[ul] == 0) { W2[lr] = 0; W2[ul] = 1; }
        else if (A1[ll] == 0 && W1[ll] == 0) { W2[lr] = 0; W2[ll] = 1; }
        else if (A1[ur] == 0 && W1[ur] == 0) { W2[lr] = 0; W2[ur] = 1; }
    }
    if (A1[ur] == 1 && W1[ur] == 1)
    {
        if (A1[ul] == 0 && W1[ul] == 0) { W2[ur] = 0; W2[ul] = 1; }
        else if (A1[ll] == 0 && W1[ll] == 0) { W2[ur] = 0; W2[ll] = 1; }
        else if (A1[lr] == 0 && W1[lr] == 0) { W2[ur] = 0; W2[lr] = 1; }
    }
}

void main()
{

    int i, j;
    i = int(gl_GlobalInvocationID.x);
    j = int(gl_GlobalInvocationID.y);

    int ul = i + j * W;
    int ur = i + 1 + j * W;
    int ll = i + (j + 1) * W;
    int lr = (i + 1) + (j + 1) * W;

    float los = random(vec2(int(i), int(j)));
    float prog = i / W;


    if (i % 2 == iStep && j % 2 == iStep)
    {
        if (A1[ul] == 1 && A1[ur] == 1 && A1[ll] == 0 && A1[lr] == 0)
        {
            if (los <= 0.99f)
            {
                A2[ul] = 0;
                A2[ur] = 0;
                A2[ll] = 1;
                A2[lr] = 1;
            }
            else
            {
                A2[ul] = A1[ul];
                A2[ur] = A1[ur];
                A2[ll] = A1[ll];
                A2[lr] = A1[lr];
            }
            //PushWater(ul, ur, ll, lr);

        }
        /*else if (A1[ul] == 1 && A1[ll] == 1 && A1[ur] == 0 && A1[lr] == 0)
        {
            if (los <= 0.90f)
            {
                A2[ul] = 0;
                A2[ur] = 0;
                A2[ll] = 1;
                A2[lr] = 1;
            }
            else
            {
                A2[ul] = A1[ul];
                A2[ur] = A1[ur];
                A2[ll] = A1[ll];
                A2[lr] = A1[lr];
            }
        }
        else if (A1[ul] == 0 && A1[ll] == 0 && A1[ur] == 1 && A1[lr] == 1)
        {
            if (los <= 0.90f)
            {
                A2[ul] = 0;
                A2[ur] = 0;
                A2[ll] = 1;
                A2[lr] = 1;
            }
            else
            {
                A2[ul] = A1[ul];
                A2[ur] = A1[ur];
                A2[ll] = A1[ll];
                A2[lr] = A1[lr];
            }
        }*/
        else
        {
            A2[ul] = G[ul] * A1[ul] + (1 - G[ul]) * A1[ul] * A1[ll] * (A1[lr] + (1 - A1[lr]) * A1[ur]);
            A2[ur] = G[ur] * A1[ur] + (1 - G[ur]) * A1[ur] * A1[lr] * (A1[ll] + (1 - A1[ll]) * A1[ul]);
            A2[ll] = A1[ll] + (1 - A1[ll]) * (A1[ul] * (1 - G[ul]) + (1 - A1[ul]) * A1[ur] * (1 - G[ur]) * A1[lr]);
            A2[lr] = A1[lr] + (1 - A1[lr]) * (A1[ur] * (1 - G[ur]) + (1 - A1[ur]) * A1[ul] * (1 - G[ul]) * A1[ll]);

            if (A2[ul] == 1 && A2[ll] == 1 && A2[lr] == 1 && A2[ur] == 0)
            {
                SS[ul] = iLos;
            }
            else if (A2[ul] == 1 && A2[ll] == 1 && A2[ur] == 1 && A2[lr] == 1 && SS[ul] != 0) SS[ul] = 0;

            if (A2[ul] == 1 && A2[ll] == 1 && A2[lr] == 1 && A2[ur] == 0 && SS[ul] != 0)
            {
                A2[ur] = 1;
                A2[ul] = 0;
                SS[ul + 1] = SS[ul] - 1;
                SS[ul] = 0;
            }


            /*if (A1[ul] == 1 && A1[ll] == 1 && A1[lr] == 1 && A1[ur] == 0)
            {
                A2[ur] = 1;
                A2[ul] = 0;
            }
            else if (A1[ul] == 0 && A1[ll] == 1 && A1[lr] == 1 && A1[ur] == 1)
            {
                A2[ur] = 0;
                A2[ul] = 1;
            }
*/

            /*int slide = int(random(vec2(int(i), int(j))) * 1 + 2);
            int ASRul = G[ul + slide] * A1[ul + slide] + (1 - G[ul + slide]) * A1[ul + slide] * A1[ll + slide] * (A1[lr + slide] + (1 - A1[lr + slide]) * A1[ur + slide]);
            int ASRur = G[ur + slide] * A1[ur + slide] + (1 - G[ur + slide]) * A1[ur + slide] * A1[lr + slide] * (A1[ll + slide] + (1 - A1[ll + slide]) * A1[ul + slide]);
            int ASRll = A1[ll + slide] + (1 - A1[ll + slide]) * (A1[ul + slide] * (1 - G[ul + slide]) + (1 - A1[ul + slide]) * A1[ur + slide] * (1 - G[ur + slide]) * A1[lr + slide]);
            int ASRlr = A1[lr + slide] + (1 - A1[lr + slide]) * (A1[ur + slide] * (1 - G[ur + slide]) + (1 - A1[ur + slide]) * A1[ul + slide] * (1 - G[ul + slide]) * A1[ll + slide]);
            //float tmpA1ul = A1[ul];//, tmpA1ur = A1[ur];

            int ASLul = G[ul - slide] * A1[ul - slide] + (1 - G[ul - slide]) * A1[ul - slide] * A1[ll - slide] * (A1[lr - slide] + (1 - A1[lr - slide]) * A1[ur - slide]);
            int ASLur = G[ur - slide] * A1[ur - slide] + (1 - G[ur - slide]) * A1[ur - slide] * A1[lr - slide] * (A1[ll - slide] + (1 - A1[ll - slide]) * A1[ul - slide]);
            int ASLll = A1[ll - slide] + (1 - A1[ll - slide]) * (A1[ul - slide] * (1 - G[ul - slide]) + (1 - A1[ul - slide]) * A1[ur - slide] * (1 - G[ur - slide]) * A1[lr - slide]);
            int ASLlr = A1[lr - slide] + (1 - A1[lr - slide]) * (A1[ur - slide] * (1 - G[ur - slide]) + (1 - A1[ur - slide]) * A1[ul - slide] * (1 - G[ul - slide]) * A1[ll - slide]);

            if ( ( (A1[ul] == 1 && A1[ll] == 1 && A1[ur] == 0 && A1[lr] == 0) || (A1[ul] == 1 && A1[ll] == 1 && A1[ur] == 0 && A1[lr] == 1)) )// && ASRul == 0 && ASRur == 0 && ASRll == 0 && ASRlr == 0)
            {
                if (A2[lr] == 1 && A2[ul] == 0 && ASRul == 0 && ASRur == 0 && ASRll == 0 && ASRlr == 0)
                {
                    A2[lr] = 0;
                    A2[lr + slide] = 1;
                }
                else if (ASRul == 0 && ASRur == 0 )
                {
                    A2[ul] = 0;
                    A2[ul + slide] = 1;
                }
            }
            if ( (A1[ur] == 1 && A1[lr] == 1 && A1[ul] == 0 && A1[ll] == 0) || (A1[ur] == 1 && A1[lr] == 1 && A1[ul] == 0 && A1[ll] == 1))
            {
                if (A2[ll] == 1 && A2[ur] == 0 && ASLul == 0 && ASLur == 0 && ASLll == 0 && ASLlr == 0)
                {
                    A2[ll] = 0;
                    A2[ll - slide] = 1;
                }
                else if ( ASLul == 0 && ASLur == 0 )
                {
                    A2[ur] = 0;
                    A2[ur - slide] = 1;
                }
            }*/

            /*if (A1[ul] == 1 && W1[ll] == 1) { A2[ll] = 1; W2[ul] = 1; }
            if (A1[ur] == 1 && W1[lr] == 1) { A2[lr] = 1; W2[ur] = 1; }
            if (A1[ul] == 1 && A1[ur] == 1 && W1[ll] == 1 && W1[lr] == 1) { A2[ll] = 1; A2[lr] = 1; W2[ul] = 1; W2[ur] = 1; }
            */
            // WATER
            //PushWater(ul, ur, ll, lr);

        }
    }

    if (i % 2 == iStep && j % 2 == iStep)
    {
        // GROUND
        //W2[ul] = G[ul] * W1[ul] + (1 - G[ul]) * W1[ul] * W1[ll] * (W1[lr] + (1 - W1[lr]) * W1[ur]);
        //W2[ur] = G[ur] * W1[ur] + (1 - G[ur]) * W1[ur] * W1[lr] * (W1[ll] + (1 - W1[ll]) * W1[ul]);
        //W2[ll] = W1[ll] + (1 - W1[ll]) * (W1[ul] * (1 - G[ul]) + (1 - W1[ul]) * W1[ur] * (1 - G[ur]) * W1[lr]);
        //W2[lr] = W1[lr] + (1 - W1[lr]) * (W1[ur] * (1 - G[ur]) + (1 - W1[ur]) * W1[ul] * (1 - G[ul]) * W1[ll]);
        // sand
        int tmpUL = A1[ul] * W1[ul] + (1 - A1[ul]) * W1[ul] * W1[ll] * (W1[lr] + (1 - W1[lr]) * W1[ur]);
        int tmpUR = A1[ur] * W1[ur] + (1 - A1[ur]) * W1[ur] * W1[lr] * (W1[ll] + (1 - W1[ll]) * W1[ul]);
        int tmpLL = W1[ll] + (1 - W1[ll]) * (W1[ul] * (1 - A1[ul]) + (1 - W1[ul]) * W1[ur] * (1 - A1[ur]) * W1[lr]);
        int tmpLR = W1[lr] + (1 - W1[lr]) * (W1[ur] * (1 - A1[ur]) + (1 - W1[ur]) * W1[ul] * (1 - A1[ul]) * W1[ll]);

        W2[ul] = tmpUL;
        W2[ur] = tmpUR;
        W2[ll] = tmpLL;
        W2[lr] = tmpLR;

        if (W1[ul] != tmpUL) { W2[ul] = G[ul] * W1[ul] + (1 - G[ul]) * W1[ul] * W1[ll] * (W1[lr] + (1 - W1[lr]) * W1[ur]); }
        if (W1[ur] != tmpUR) { W2[ur] = G[ur] * W1[ur] + (1 - G[ur]) * W1[ur] * W1[lr] * (W1[ll] + (1 - W1[ll]) * W1[ul]); }
        if (W1[ll] != tmpLL) { W2[ll] = W1[ll] + (1 - W1[ll]) * (W1[ul] * (1 - G[ul]) + (1 - W1[ul]) * W1[ur] * (1 - G[ur]) * W1[lr]); }
        if (W1[lr] != tmpLR) { W2[lr] = W1[lr] + (1 - W1[lr]) * (W1[ur] * (1 - G[ur]) + (1 - W1[ur]) * W1[ul] * (1 - G[ul]) * W1[ll]); }

        int slide = int(random(vec2(int(i), int(j))) * iLos);
        int ASRul = G[ul + slide] * A1[ul + slide] + (1 - G[ul + slide]) * A1[ul + slide] * A1[ll + slide] * (A1[lr + slide] + (1 - A1[lr + slide]) * A1[ur + slide]);
        int ASRur = G[ur + slide] * A1[ur + slide] + (1 - G[ur + slide]) * A1[ur + slide] * A1[lr + slide] * (A1[ll + slide] + (1 - A1[ll + slide]) * A1[ul + slide]);
        int ASRll = A1[ll + slide] + (1 - A1[ll + slide]) * (A1[ul + slide] * (1 - G[ul + slide]) + (1 - A1[ul + slide]) * A1[ur + slide] * (1 - G[ur + slide]) * A1[lr + slide]);
        int ASRlr = A1[lr + slide] + (1 - A1[lr + slide]) * (A1[ur + slide] * (1 - G[ur + slide]) + (1 - A1[ur + slide]) * A1[ul + slide] * (1 - G[ul + slide]) * A1[ll + slide]);
        //float tmpA1ul = A1[ul];//, tmpA1ur = A1[ur];

        int ASLul = G[ul - slide] * A1[ul - slide] + (1 - G[ul - slide]) * A1[ul - slide] * A1[ll - slide] * (A1[lr - slide] + (1 - A1[lr - slide]) * A1[ur - slide]);
        int ASLur = G[ur - slide] * A1[ur - slide] + (1 - G[ur - slide]) * A1[ur - slide] * A1[lr - slide] * (A1[ll - slide] + (1 - A1[ll - slide]) * A1[ul - slide]);
        int ASLll = A1[ll - slide] + (1 - A1[ll - slide]) * (A1[ul - slide] * (1 - G[ul - slide]) + (1 - A1[ul - slide]) * A1[ur - slide] * (1 - G[ur - slide]) * A1[lr - slide]);
        int ASLlr = A1[lr - slide] + (1 - A1[lr - slide]) * (A1[ur - slide] * (1 - G[ur - slide]) + (1 - A1[ur - slide]) * A1[ul - slide] * (1 - G[ul - slide]) * A1[ll - slide]);

        if (W1[ul] == 1 && W1[ll] == 1 && W1[ur] == 0 && W1[lr] == 0 && W2[lr] == 1 && W2[ul] == 0 && ASRul == 0 && ASRur == 0 && ASRll == 0 && ASRlr == 0)
        {
            W2[lr] = 0;
            W2[lr + slide] = 1;
        }
        if (W1[ur] == 1 && W1[lr] == 1 && W1[ul] == 0 && W1[ll] == 0 && W2[ll] == 1 && W2[ur] == 0 && ASLul == 0 && ASLur == 0 && ASLll == 0 && ASLlr == 0)
        {
            W2[ll] = 0;
            W2[ll - slide] = 1;
        }/*
        if (W1[ul] == 1 && W1[ll] == 1 && W1[ur] == 0 && W1[lr] == 1 && ASRul == 0 && ASRur == 0 && ASRll == 0 && ASRlr == 0)
        {
            W2[ul] = 0;
            W2[ul + slide] = 1;
        }
        if (W1[ul] == 0 && W1[ll] == 1 && W1[ur] == 1 && W1[lr] == 1 && ASLul == 0 && ASLur == 0 && ASLll == 0 && ASLlr == 0)
        {
            W2[ur] = 0;
            W2[ur - slide] = 1;
        }

        if (tmpLL == 0 && tmpLR == 0 && tmpUL == 1 && tmpUR == 0) { W2[ul] = 0; W2[ur] = 1; }
        if (tmpLL == 0 && tmpLR == 0 && tmpUL == 0 && tmpUR == 1) { W2[ul] = 1; W2[ur] = 0; }*/

        //PushWater(ul, ur, ll, lr);

    }

    vec4 col = vec4(vec3(0), 1);
    vec2 M = iMouse.xy;// / iResolution.xy;

    if (A2[i + j * W] == 1) { col = vec4(vec3(0.988f, 0.964f, 0.392f), 1); }    // sand
    if (W2[i + j * W] == 1) { col = vec4(vec3(0.070f, 0.1252f, 0.99f), 1); }      // water

    if (G[i + j * W] == 1 || G[i + j * W] == 2)                              // ground
    {// col = vec4(vec3(0.235f, 0.045f, 0.035f), 1);    

        if (G[i + j * W] == 1)
            col = vec4(vec3(0.070f, 0.992f, 0.125f), 1);    // green
        else
            col = vec4(vec3(0.235f, 0.045f, 0.035f), 1);    // brown
    }

    if (iMouse.w > 0. )
    {
        if (iKey == 0.0f)
        {
            if (distance(vec2(i, j), vec2(M.x, M.y)) <= 15)
            {
                A2[i + j * W] = 1;
                // G[i + j * W] = 1.0f;
                col = vec4(vec3(0.988f, 0.964f, 0.392f), 1);
            }
            /*if (distance(j, M.y) == 1 && distance(i, M.x) <= 500)
            {
                A2[i + j * W] = 1;
                col = vec4(vec3(0.988f, 0.964f, 0.392f), 1);
            }
            if (distance(vec2(i, j), vec2(M.x, M.y)) == 1)
            {
                A2[i + j * W] = 1;
                col = vec4(vec3(0.988f, 0.964f, 0.392f), 1);
            }*/
        }
        else if (iKey == 1.0f)
        {
            if (distance(vec2(i, j), vec2(M.x, M.y)) <= 15)
            {
                //G[i + j * W] = 1.0f;
                if (j < M.y - 10.0f + (los + 1.0f * (los / 2 + 1.0f)) * 5.0f) // jakies losowe obliczenia zeby fajna trawa wyszla
                    G[i + j * W] = 1;
                else
                    G[i + j * W] = 2;

            }
        }
        else if (iKey == 2.0f)
        {
            if (distance(vec2(i, j), vec2(M.x, M.y)) <= 15)
            {
                W2[i + j * W] = 1;
            }
        }
    }/*
    col = vec4(vec3(random(vec2(int(i), int(j)))), 1);*/
    //vec4 col = vec4(vec3(A2[i + j * W] * 255.0f), 1);
    imageStore(img, ivec2(gl_GlobalInvocationID.xy), col);
}