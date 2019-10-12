#version 330

uniform sampler2D diffuse;
in vec2 tex_coord;

void main() {
    gl_FragColor = vec3(texture2D(diffuse, tex_coord).xyz, 1);
}
