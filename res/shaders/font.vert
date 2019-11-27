#version 330
#define LOCATION_POSITION 0
#define LOCATION_NORMAL 1
#define LOCATION_COLOR 2
#define LOCATION_COORDINATE 3
#define LOCATION_TANGENT 4

layout(location=LOCATION_POSITION) in vec3 position;
//layout(location=LOCATION_NORMAL) in vec3 normal;
//layout(location=LOCATION_COLOR) in vec3 color;
layout(location=LOCATION_COORDINATE) in vec2 coordinate;
//layout(location=LOCATION_TANGENT) in vec3 tangent;

out vec2 uv;
uniform vec2 screen_size;

void main(){
	uv = coordinate;
//    float x = 2 * position.x / screen_size.x - 1;
//    float y = 2 * position.y / screen_size.y - 1;
    float x = 2 * position.x / screen_size.x - 1;
    float y = 2 * position.y / screen_size.y - 1;
//    vec2 xy = position.xy - 1;
//    if (xy.x > 1)
//    {
//        xy.x = 1;
//    }
//    if(xy.y > 1)
//    {
//        xy.y = 1;
//    }
    gl_Position = vec4(x, y, -0.9, 1);
}
