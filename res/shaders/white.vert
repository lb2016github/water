#version 330
#define LOCATION_POSITION 0
#define LOCATION_NORMAL 1
#define LOCATION_COLOR 2
#define LOCATION_COORDINATE 3
#define LOCATION_TANGENT 4
#define LOCATION_JOINT_INDICES 5
#define LOCATION_JOINT_WEIGHTS 6

#define MAX_BONE_NUM 255

layout(location=LOCATION_POSITION) in vec3 position;
layout(location=LOCATION_NORMAL) in vec3 normal;
//layout(location=LOCATION_COLOR) in vec3 color;
layout(location=LOCATION_COORDINATE) in vec2 coordinate;
//layout(location=LOCATION_TANGENT) in vec3 tangent;
layout(location=LOCATION_JOINT_INDICES) in ivec4 jointIndices;
layout(location=LOCATION_JOINT_WEIGHTS) in vec4 jointWeights;

uniform mat4 wvp;
uniform mat4 world;

uniform mat4 skinMatrices[MAX_BONE_NUM];

out struct
{
	vec3 normal;
	vec2 tex_coord;
	vec3 world_pos;
}vs_out;

void main(){
    mat4 skinMatrix = skinMatrices[jointIndices.x] * jointWeights[jointIndices.x];
	skinMatrix += skinMatrices[jointIndices.y] * jointWeights[jointIndices.y];
	skinMatrix += skinMatrices[jointIndices.z] * jointWeights[jointIndices.z];
	skinMatrix += skinMatrices[jointIndices.w] * jointWeights[jointIndices.w];

	vec4 skinedPos = skinMatrix * vec4(position, 1);
	vec4 skinedNormal = skinMatrix * vec4(normal, 0);

	vs_out.normal = (world * skinedNormal).xyz;
	vs_out.tex_coord = coordinate;
	vs_out.world_pos = (world * skinedPos).xyz;
	gl_Position = wvp * skinedPos;
}

