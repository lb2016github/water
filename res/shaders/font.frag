#version 330

in vec2 uv;
uniform sampler2D tex;
uniform vec3 color;
out vec4 frag_color;

void main(){
    float s = texture(tex, uv).x;
    frag_color = vec4(255, 0, 0, s);
//	frag_color = vec4(color, 1) * sampled ;
//    frag_color = vec4(1, 1, 1, s);
}