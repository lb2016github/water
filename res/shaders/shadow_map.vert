#version 330
#define LOCATION_POSITION 0
#define LOCATION_NORMAL 1
#define LOCATION_COLOR 2
#define LOCATION_COORDINATE 3
#define LOCATION_TANGENT 4

layout(location=LOCATION_POSITION) in vec3 position;
//layout(location=LOCATION_NORMAL) in vec3 normal;
//layout(location=LOCATION_COLOR) in vec3 color;
//layout(location=LOCATION_COORDINATE) in vec2 coordinate;
//layout(location=LOCATION_TANGENT) in vec3 tangent;

uniform mat4 light_vp;
uniform mat4 world;

void main(){
	gl_Position = light_vp * world * vec4(position, 1);
}