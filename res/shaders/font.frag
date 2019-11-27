#version 330

in vec2 uv;
uniform sampler2D tex;
uniform vec3 color;
out vec4 frag_color;

void main(){
    float s = texture(tex, uv).x;
    frag_color = vec4(color, s);
}