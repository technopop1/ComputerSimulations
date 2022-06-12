#version 440
#pragma optimize(on)

const int W = 1580;
const int H = 1020;


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

	int idx = i + j * W; // grid index

    int idx1, idx2, idx3, idx4, idx5, idx6, idx7, idx8;
    int ip, jp, im, jm;
    ip = per(i + 1, W); // periodicity and neighbours
    im = per(i - 1, W);
    jp = per(j + 1, H);
    jm = per(j - 1, H);
    idx1 = ip + W * (jp);
    idx2 = ip + W * (j); // i+1,j
    idx3 = ip + W * (jm);
    idx4 = i + W * (jm); // i,j-1
    idx5 = im + W * (jm);
    idx6 = im + W * (j); // i-1, j
    idx7 = im + W * (jp);
    idx8 = i + W * (jp); // i, j+1

    int neighborsAlive = 0;
    if (A1[idx] == 255.0f) ++neighborsAlive;
    if (A1[idx1] == 255.0f) ++neighborsAlive;
    if (A1[idx2] == 255.0f) ++neighborsAlive;
    if (A1[idx3] == 255.0f) ++neighborsAlive;
    if (A1[idx4] == 255.0f) ++neighborsAlive;
    if (A1[idx5] == 255.0f) ++neighborsAlive;
    if (A1[idx6] == 255.0f) ++neighborsAlive;
    if (A1[idx7] == 255.0f) ++neighborsAlive;
    if (A1[idx8] == 255.0f) ++neighborsAlive;


	//if (((neighborsAlive == 2 || neighborsAlive == 3) && A1[i+j*W] == 255.0f) || (neighborsAlive == 3 && A1[i+j*W] == 0.0f))
	//	A2[i+j*W] = 255.0f;
	//else
	//	A2[i+j*W] = 0.0f;
    
    if ( neighborsAlive == 4 || neighborsAlive == 6 || neighborsAlive == 7 || neighborsAlive == 8 || neighborsAlive == 9) {
		A2[i+j*W] = 255.0f;
	}
	else {
		A2[i+j*W] = 0.0f;
	}

	vec4 col = vec4( vec3(A2[i+j*W]), 1);
	imageStore(img, ivec2(gl_GlobalInvocationID.xy), col);
}