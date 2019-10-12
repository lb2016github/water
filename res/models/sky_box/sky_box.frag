#version 330

out vec4 frag_color;
in vec3 tex_coord;
uniform samplerCube cube_map;

void main() {
    frag_color = texture(cube_map, tex_coord);
}
