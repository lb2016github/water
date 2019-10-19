#version 330

uniform samplerCube cube_map;

in struct
{
	vec3 coordinate;
}vs_out;
out vec4 frag_color;

void main(){
    vec4 color = texture(cube_map, vs_out.coordinate);
	frag_color = vec4(color.xyz, 1);
}