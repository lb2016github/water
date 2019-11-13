#version 330
#define LOCATION_POSITION 0
#define LOCATION_NORMAL 1
#define LOCATION_COLOR 2
#define LOCATION_COORDINATE 3
#define LOCATION_TANGENT 4
#define LOCATION_BONES 5
#define LOCATION_BONE_WEIGHTS 6

#define MAX_BONES 256

layout(location=LOCATION_POSITION) in vec3 position;
layout(location=LOCATION_BONES) in ivec4 bones;
layout(location=LOCATION_BONE_WEIGHTS) in vec4 bone_weigths;

uniform mat4 wvp;
uniform mat4 bone_trans[MAX_BONES];

void main(){
    mat4 transformation = bone_trans[bones[0]] * bone_weigths[0];
    transformation += bone_trans[bones[1]] * bone_weigths[1];
    transformation += bone_trans[bones[2]] * bone_weigths[2];
    transformation += bone_trans[bones[3]] * bone_weigths[3];
    position = (transformation * vec4(position, 1)).xyz;
    gl_Position = wvp * vec4(position, 1);
}

