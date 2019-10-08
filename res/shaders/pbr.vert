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
layout(location=LOCATION_TANGENT) in vec3 tangent;


struct VSOut
{
    vec3 w_normal;
    vec3 world_position;
    vec3 w_tangent;
    vec2 coord;
};

out VSOut vs_out;

uniform mat4 world_matrix;
uniform mat4 wvp;

void main() {
    vs_out.w_normal = (world_matrix * vec4(normal, 0)).xyz;
    vs_out.w_tangent = (world_matrix * vec4(tangent, 0)).xyz;
    vs_out.world_position = (world_matrix * vec4(position, 1)).xyz;
    vs_out.coord = coordinate;
    gl_Position = wvp * vec4(position, 1.0);
}
