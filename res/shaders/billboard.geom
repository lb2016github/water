#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

out vec2 tex_coord;

uniform vec3 cam_pos;   // camera position
uniform vec2 size;      // size of billboard
uniform mat4 vp;        // view * proj matrix

void main() {
    vec3 dir2cam = normalize(cam_pos - gl_in[0].gl_Position.xyz);
    vec3 tmp_up = vec3(0, 1, 0);
    vec4 right = vec4(normalize(cross(tmp_up, dir2cam)), 0);
    vec4 up = vec4(normalize(cross(dir2cam, right.xyz)), 0);

    vec2 half_size = size / 2.0f;

    // left down
    vec4 v_pos = gl_in[0].gl_Position - right * half_size.x - up * half_size.y;
    gl_Position = vp * v_pos;
    tex_coord = vec2(0, 0);
    EmitVertex();

    // right down
    v_pos = gl_in[0].gl_Position + right * half_size.x - up * half_size.y;
    gl_Position = vp * v_pos;
    tex_coord = vec2(1, 0);
    EmitVertex();

    // left up
    v_pos = gl_in[0].gl_Position - right * half_size.x + up * half_size.y;
    gl_Position = vp * v_pos;
    tex_coord = vec2(0, 1);
    EmitVertex();

    // right up
    v_pos = gl_in[0].gl_Position + right * half_size.x + up * half_size.y;
    gl_Position = vp * v_pos;
    tex_coord = vec2(1, 1);
    EmitVertex();

    EndPrimitive();

}
