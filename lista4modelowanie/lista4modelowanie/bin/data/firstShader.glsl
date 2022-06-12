#version 440

layout(binding = 0) buffer dcA1 { float A1 [ ]; };
layout(rgba8, binding=1) uniform writeonly image2D img; 
layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;

const int W = 1920;
const int H = 1080;

void main(){ 

	int i, j;
	i = int(gl_GlobalInvocationID.x);
	j = int(gl_GlobalInvocationID.y);

	//int idx = i+j*W;
	//A1[idx] = i / float(W);

	int idx = i+j*W;
	A1[idx] = ( (i - W/2)*(i - W/2) + (j - H/2)*(j - H/2)) / float(W*H);

	//if ( acos( ( W/2 * i + H/2 * j )/( sqrt( (W/2 - i)*(W/2 - i) + (H/2 - j)*(H/2 - j) ) ) ) ) 
	
	float degree = acos( ( 0 * i + H/2 * j ) / ( sqrt( (0 - i)*(0 - i)) + sqrt((H/2 - j)*(H/2 - j) ) ) );
	//float degree = acos( dot( normalize(vec2(0, H/2)),  normalize(vec2(i, j)) ) / ( sqrt( (0 - i)*(0 - i) ) + sqrt( (H/2 - j)*(H/2 - j) ) ) );

	if (degree > 250) degree = 0 + (360-degree);
	else if (degree < 0) degree = 360 - degree;

	vec4 col = vec4( A1[idx]+int(degree), A1[idx], A1[idx]+int(degree), 1);   //vec4( vec3(A1[idx]), 1);
	//vec4 col = vec4( vec3(A1[idx]), 1);
	imageStore(img, ivec2(gl_GlobalInvocationID.xy), col);
}