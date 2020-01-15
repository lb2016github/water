#version 330
#define LOCATION_POSITION 0
#define LOCATION_NORMAL 1
#define LOCATION_COLOR 2
#define LOCATION_COORDINATE 3
#define LOCATION_TANGENT 4

layout(location=LOCATION_POSITION) in vec3 position;
layout(location=LOCATION_NORMAL) in vec3 normal;
//layout(location=LOCATION_COLOR) in vec3 color;
layout(location=LOCATION_COORDINATE) in vec2 coordinate;
//layout(location=LOCATION_TANGENT) in vec3 tangent;

uniform mat4 wvp;
uniform mat4 world;
out struct
{
	vec3 normal;
	vec2 tex_coord;
	vec3 world_pos;
}vs_out;

void main(){
	vs_out.normal = normal;
	vs_out.tex_coord = coordinate;
	vs_out.world_pos = (world * vec4(position, 1)).xyz;
	gl_Position = wvp * vec4(position, 1);
}

