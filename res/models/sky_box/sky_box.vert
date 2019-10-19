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

uniform mat4 vp;
uniform vec3 cam_pos;
uniform float scale;
out vec3 tex_coord;

void main(){
    vec4 wvp_pos = vp * vec4(position * scale + cam_pos, 1);
    wvp_pos.z = wvp_pos.w * 0.999f;
    gl_Position = wvp_pos;
    tex_coord = position;
}
