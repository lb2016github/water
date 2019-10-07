#version 330
#define LOCATION_POSITION 0
#define LOCATION_NORMAL 1
#define LOCATION_COLOR 2
#define LOCATION_COORDINATE 3
#define LOCATION_TANGENT 4

layout(location=LOCATION_POSITION) in vec3 position;
layout(location=LOCATION_NORMAL) in vec3 normal;
//layout(location=LOCATION_COLOR) in vec3 color;
//layout(location=LOCATION_COORDINATE) in vec2 coordinate;
//layout(location=LOCATION_TANGENT) in vec3 tangent;


struct VSOut
{
    vec3 albedo;
    vec3 normal;
    vec3 world_position;
};

out VSOut vs_out;

uniform mat4 world_matrix;
uniform mat4 wvp;
uniform vec3 albedo;

void main() {
    vs_out.albedo = vec3(albedo);
    vs_out.normal = (world_matrix * vec4(normal, 0)).xyz;
    vs_out.world_position = (world_matrix * vec4(position, 1)).xyz;
    gl_Position = wvp * vec4(position, 1.0);
}
