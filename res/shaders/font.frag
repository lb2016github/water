#version 330

in vec2 uv;
uniform sampler2D tex;
uniform vec3 color;
out vec4 frag_color;

void main(){
    vec2 uv1 = vec2(uv.x, 1 - uv.y);
    float s = texture(tex, uv1).x;
    frag_color = vec4(color, s);
}