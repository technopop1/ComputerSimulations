#version 440
#pragma optimize(on)
uniform vec4 iMouse;
uniform vec3 iResolution;

const int W = 1920;
const int H = 1080;


layout(std430, binding = 0) buffer dcA1 { float A1 [  ]; };
layout(std430, binding = 1) buffer dcA2 { float A2 [  ]; };

layout(rgba8, binding=1) uniform writeonly image2D img; 
layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;


int per(int x, int nx) {
    if (x < 0) x += nx;
    if (x >= nx) x -= nx;
    return x;
}

vec4 color(float t) {
    vec4 col;
    col.r = t;
    col.g = t;
    col.b = t;
    col.a = 1;
    return col;
}


void main(){ 

	int i, j;
	i = int(gl_GlobalInvocationID.x);
	j = int(gl_GlobalInvocationID.y);
    
    float neighborsAliveR1 = 0;
    float neighborsAliveR2 = 0;
    float neighborsAliveR3 = 0;
    float neighborsAliveR4 = 0;
    float NumOfCellsR1 = 0;
    float NumOfCellsR2 = 0;
    float NumOfCellsR3 = 0;
    float NumOfCellsR4 = 0;

    int r1 = 3, r2 = 5, r3 = 7, r4 = 13;
    //int r1 = 1*2, r2 = 4*2, r3 = 7*2, r4 = 15*2 ;

    /*for (int x = i - r4 ; x < i + r4; ++x ) {
          for (int y = j - r4 ; y < j + r4; ++y ) {
              if ( distance(vec2(x,y), vec2(i,j)) <= float(r1)) {
                  NumOfCellsR1++;
                  if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR1;
              }
              if ( distance(vec2(x,y), vec2(i,j)) <= float(r2) && distance(vec2(x,y), vec2(i,j)) >= float(r1) ) {
                  NumOfCellsR2++;
                  if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR2;
              }
              if ( distance(vec2(x,y), vec2(i,j)) <= float(r3) && distance(vec2(x,y), vec2(i,j)) >= float(r2) ) {
                  NumOfCellsR3++;
                  if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR3;
              }
              if ( distance(vec2(x,y), vec2(i,j)) <= float(r4) && distance(vec2(x,y), vec2(i,j)) >= float(r3) ) {
                  NumOfCellsR4++;
                  if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR4;
              }
          }
     }*/

    // KWADRATOWE S¥SIEDZTWO
    for (int x = i - r4; x < i + r4; ++x)
    {
        for (int y = j - r4; y < j + r4; ++y)
        {
            if ((x >= i - r1) && (x <= i + r1) && (y >= j - r1) && (y <= j + r1))
            {
                NumOfCellsR1++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR1;
            }
            if ((x >= i - r2) && (x <= i + r2) && (y >= j - r2) && (y <= j + r2))
            {
                NumOfCellsR2++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR2;
            }
            if ((x >= i - r3) && (x <= i + r3) && (y >= j - r3) && (y <= j + r3))
            {
                NumOfCellsR3++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR3;
            }
            if ((x >= i - r4) && (x <= i + r4) && (y >= j - r4) && (y <= j + r4))
            {
                NumOfCellsR4++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR4;
            }
        }
    }
    // KWADRATOWE PIERSCIENIE
    /*for (int x = i - r4; x < i + r4; ++x)
    {
        for (int y = j - r4; y < j + r4; ++y)
        {
            if (  (x >= i - r1) && (x <= i + r1) && (y >= j - r1) && (y <= j + r1))
            {
                NumOfCellsR1++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR1;
            }
            if (  ((x >= i - r2) && (x <= i + r2) && (y >= j - r2) && (y <= j + r2)) &&
                 !((x >= i - r1) && (x <= i + r1) && (y >= j - r1) && (y <= j + r1)))
            {
                NumOfCellsR2++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR2;
            }
            if (  ((x >= i - r3) && (x <= i + r3) && (y >= j - r3) && (y <= j + r3)) &&
                 !((x >= i - r2) && (x <= i + r2) && (y >= j - r2) && (y <= j + r2)))
            {
                NumOfCellsR3++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR3;
            }
            if (  ((x >= i - r4) && (x <= i + r4) && (y >= j - r4) && (y <= j + r4)) &&
                 !((x >= i - r3) && (x <= i + r3) && (y >= j - r3) && (y <= j + r3)))
            {
                NumOfCellsR4++;
                if (A1[per(x, W) + per(y, H) * W] == 1.0f) ++neighborsAliveR4;
            }
        }
    }*/

    /* for (int x = i - r4 ; x < i + r4; ++x ) {
         for (int y = j - r4 ; y < j + r4; ++y ) {
             if (     distance(vec2(x,y), vec2(i,j)) <= float(r4)) {
                 NumOfCellsR1++;
                 if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR1;
             }
             if (     distance(vec2(x,y), vec2(i,j)) <= float(r1) 
                 || ( distance(vec2(x,y), vec2(i,j)) <= float(r2+1) && distance(vec2(x,y), vec2(i,j)) >= float(r2) ) 
                 || ( distance(vec2(x,y), vec2(i,j)) <= float(r3) && distance(vec2(x,y), vec2(i,j)) >= float(r3) ) 
                 ) {
                 NumOfCellsR2++;
                 if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR2;
             }
             if (     distance(vec2(x,y), vec2(i,j)) <= float(r3+3) ) {
                 NumOfCellsR3++;
                 if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR3;
             }
             if (     distance(vec2(x,y), vec2(i,j)) <= float(r1+1) 
                 || ( distance(vec2(x,y), vec2(i,j)) <= float(r2+3) && distance(vec2(x,y), vec2(i,j)) >= float(r2) ) 
                 || ( distance(vec2(x,y), vec2(i,j)) <= float(r3+2) && distance(vec2(x,y), vec2(i,j)) >= float(r3+1) ) 
                 || ( distance(vec2(x,y), vec2(i,j)) <= float(r4+1) && distance(vec2(x,y), vec2(i,j)) >= float(r4-2) ) 
                 ) {
                 NumOfCellsR4++;
                 if ( A1[ per(x,W) + per(y,H)*W ] == 1.0f ) ++neighborsAliveR4;
             }
         }
     }*/

    float rhoR1 = neighborsAliveR1 / NumOfCellsR1;
    float rhoR2 = neighborsAliveR2 / NumOfCellsR2;
    float rhoR3 = neighborsAliveR3 / NumOfCellsR3;
    float rhoR4 = neighborsAliveR4 / NumOfCellsR4;

    // int r1 = 3, r2 = 5, r3 = 8, r4 = 25;
    if (neighborsAliveR2 >= 34 && neighborsAliveR2 <= 58 && A1[i + j * W] == 1.0f)
        A2[i + j * W] = 1.0f;
    else if (neighborsAliveR2 > 33 && neighborsAliveR2 < 46)
        A2[i + j * W] = 1.0f;
    else
        A2[i + j * W] = 0.0f;

    //int r1 = 3, r2 = 9, r3 = 27, r4 = 19;
    /*if (rhoR1 <= 0.120f) { A2[i + j * W] = 0.0f; }
    if (rhoR2 <= 0.100f) { A2[i + j * W] = 0.0f; }
    if (rhoR1 >= 0.120f && rhoR1 <= 0.150f) { A2[i + j * W] = 0.0f; }
    if (rhoR1 >= 0.210f && rhoR1 <= 0.220f) { A2[i + j * W] = 1.0f; }
    if (rhoR1 >= 0.350f && rhoR1 <= 0.500f) { A2[i + j * W] = 0.0f; }
    if (rhoR1 >= 0.750f && rhoR1 <= 0.850f) { A2[i + j * W] = 0.0f; }
    if (rhoR2 >= 0.100f && rhoR2 <= 0.280f) { A2[i + j * W] = 0.0f; }
    if (rhoR2 >= 0.430f && rhoR2 <= 0.550f) { A2[i + j * W] = 1.0f; }*/


    // int r1 = 5, r2 = 13, r3 = 20, r4 = 19;
    /*if (rhoR1 <= 0.10f) { A2[i + j * W] = 0.0f; }
    if (rhoR2 <= 0.10f) { A2[i + j * W] = 0.0f; }
    if ((rhoR1 < 0.5f && rhoR2 > 0.25f && rhoR2 < 0.33f) || (rhoR1 > 0.5f && rhoR2 > 0.35f && rhoR2 < 0.51f)) { A2[i + j * W] += 0.1f; }
    if ((rhoR1 > 0.5f && rhoR2 > 0.25f && rhoR2 < 0.33f) || (rhoR1 < 0.5f && rhoR2 > 0.25f && rhoR2 < 0.33f)) { A2[i + j * W] -= 0.1f; }
    if ((rhoR1 < 0.85f && rhoR2 > 0.5f && rhoR2 < 0.6f) || (rhoR1 > 0.3f && rhoR2 > 0.45f && rhoR2 < 0.65f)) { A2[i + j * W] += 0.2f; }
    if ((rhoR1 > 0.85f && rhoR2 > 0.5f && rhoR2 < 0.6f) || (rhoR1 < 0.3f && rhoR2 > 0.15f && rhoR2 < 0.44f)) { A2[i + j * W] -= 0.3f; }
    if ((rhoR2 > 0.95f && rhoR3 > 0.70f && rhoR3 < 0.85f) || (rhoR2 < 0.5f && rhoR3 > 0.35f && rhoR3 < 0.77f)) { A2[i + j * W] += 0.05f; }
    if (A2[i + j * W] < 0.0f) { A2[i + j * W] = 0.0f; }
    if (A2[i + j * W] > 1.0f) { A2[i + j * W] = 1.0f; }*/


    // r1 = 3, r2 = 5
    /*if (neighborsAliveR2 >= 0.0 && neighborsAliveR2 <= 33.0) { A2[i + j * W] = 0.0; }
    if (neighborsAliveR2 >= 34.0 && neighborsAliveR2 <= 55.0 && A2[i + j * W] == 1.0f) { A2[i + j * W] = 1.0; }
    if (neighborsAliveR2 >= 34.0 && neighborsAliveR2 <= 45.0) { A2[i + j * W] = 1.0; }
    if (neighborsAliveR2 >= 58.0 && neighborsAliveR2 <= 121.0) { A2[i + j * W] = 0.0; }*/

    /*if (rhoR2 >= 0.0 && rhoR2 <= 0.33) { A2[i + j * W] = 0.0; }
    if (rhoR2 >= 0.34 && rhoR2 <= 0.55 && A2[i + j * W] == 1.0f) { A2[i + j * W] = 1.0; }
    if (rhoR2 >= 0.34 && rhoR2 <= 0.45) { A2[i + j * W] = 1.0; }
    if (rhoR2 >= 0.58 && rhoR2 <= 0.121) { A2[i + j * W] = 0.0; }*/


    //int r1 = 3, r2 = 6, r3 = 9, r4 = 20;
    /*if ( rhoR1 < 0.01 ) { A2[i+j*W] = 0.0f; }
    if( rhoR1 >= 0.262364076538086 &&  rhoR1 <= 0.902710297241211 ) { A2[i+j*W] = 0.0f; }
    if( rhoR1 >= 0.876029204711914 &&  rhoR1 <= 0.764857985839844 ) { A2[i+j*W] = 1.0f; }
    if( rhoR1 >= 0.533621850585938 &&  rhoR1 <= 0.911603994750977 ) { A2[i+j*W] = 0.0f; }
    if( rhoR1 >= 0.787092229614258 &&  rhoR1 <= 0.449131724243164 ) { A2[i+j*W] = 0.0f; }
                                                     
    if( rhoR2 < 0.01 ) { A2[i+j*W] = 0.0f; }                        
    if( rhoR2 >= 0.342407354125977 &&  rhoR2 <= 0.377982144165039 ) { A2[i+j*W] = 1.0f; }
    if( rhoR2 >= 0.453578572998047 &&  rhoR2 <= 0.057809033813477 ) { A2[i+j*W] = 1.0f; }
    if( rhoR2 >= 0.484706514282227 &&  rhoR2 <= 0.671474161987305 ) { A2[i+j*W] = 1.0f; }
    if( rhoR2 >= 0.057809033813477 &&  rhoR2 <= 0.11117121887207  ) { A2[i+j*W] = 0.0f; }
                                                  
    if( rhoR3 < 0.01) { A2[i+j*W] = 0.0f; }                            
    if( rhoR3 >= 0.342407354125977 &&  rhoR3 <= 0.382428992919922 ) { A2[i+j*W] = 1.0f; }
    if( rhoR3 >= 0.755964288330078 &&  rhoR3 <= 0.53806869934082  ) { A2[i+j*W] = 1.0f; }
    if( rhoR3 >= 0.195661345214844 &&  rhoR3 <= 0.217895588989258 ) { A2[i+j*W] = 0.0f; }
    if( rhoR3 >= 0.671474161987305 &&  rhoR3 <= 0.489153363037109 ) { A2[i+j*W] = 1.0f; }
                                               
    if( rhoR4 < 0.01) { A2[i+j*W] = 0.0f; }                               
    if( rhoR4 >= 0.889369750976563 &&  rhoR4 <= 0.978306726074219 ) { A2[i+j*W] = 1.0f; }
    if( rhoR4 >= 0.035574790039063 &&  rhoR4 <= 0.133405462646484 ) { A2[i+j*W] = 0.0f; }
    if( rhoR4 >= 0.88492290222168  &&  rhoR4 <= 0.760411137084961 ) { A2[i+j*W] = 0.0f; }
    if( rhoR4 >= 0.635899371948242 &&  rhoR4 <= 0.257917227783203 ) { A2[i+j*W] = 1.0f; }*/


    //vec2 M = (vec2(i,j) - iMouse.xy) / iResolution.xy;
    vec2 M = iMouse.xy;// / iResolution.xy;
    if( iMouse.w > 0. ){
        for(int ix = int(M.x) - 15; ix < int(M.y) + 15; ++ix){
            for(int iy = int(M.y) - 15; iy < int(M.y) + 15; ++iy){
                if ( distance(vec2(ix,iy), vec2(M.x,M.y)) <= float(15)) {
                    A2[ix+iy*W] = 1.0f;
                }
            }
        }
    }

    vec4 col = vec4( vec3(A1[i+j*W])*255.0f, 1);
	imageStore(img, ivec2(gl_GlobalInvocationID.xy), col);
}