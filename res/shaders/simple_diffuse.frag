#version 330

uniform sampler2D diffuse;

in struct
{
	vec2 coordinate;
}vs_out;
out vec4 frag_color;

void main(){
    vec4 color = texture2D(diffuse, vs_out.coordinate.xy);
	frag_color = vec4(color.xyz, 1);
}