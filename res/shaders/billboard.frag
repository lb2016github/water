#version 330

uniform sampler2D diffuse;
in vec2 tex_coord;
out vec4 frag_color;

void main() {
    frag_color = vec4(texture2D(diffuse, tex_coord).xyz, 1);
}
