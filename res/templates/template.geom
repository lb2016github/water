#version 330
layout(triangles) in;
layout(triangles, max_vertices=3) out;

out vec2 tex_coord;

struct GSOut
{
    vec3 position;
    mat4 world_mtx;
    float metallic;
    float roughness;
};

uniform mat4 world_matrix;
uniform mat4 vp;

out GSOut vs_out;

void main() {
    for(float m = 0.1; m <= 1; m += 0.1)
    {
        for(float r = 0.1; r <= 1; r += 0.1)
        {
            for(int i = 0; i < 3; ++i)
            {
                vec4 position = gl_in[i].gl_Position;
                gs_out.roughness = r;
                gs_out.metallic = m;
                gs_out.position = position.xyz;
                gs_out.world_mtx = mat4(
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                r * 5, m * 5, 0, 1
                ) * world_matrix;
                gl_Position = vp * gs_out.world_mtx * position;
                EmitVertex();
            }
            EndPrimitive();
        }
    }
}
