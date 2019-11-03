#version 420
layout(triangles) in;
layout(triangle_strip, max_vertices=4) out;

struct VSOut
{
    vec3 position;
    mat4 world_mtx;
    float metallic;
    float roughness;
};

uniform mat4 world_matrix;
uniform mat4 vp;

out VSOut vs_out;

void main() {
    for(float m = 0.1; m <= 1; m += 0.1)
    {
        for(float r = 0.1; r <= 1; r += 0.1)
        {
            mat4 world_mtx = world_matrix;
            world_mtx[3][0] += r * 50;
            world_mtx[3][1] += m * 50;
            vs_out.roughness = r;
            vs_out.metallic = m;
            vs_out.world_mtx = world_mtx;

            for(int i = 0; i < 3; ++i)
            {
                vec4 position = gl_in[i].gl_Position;
                vs_out.position = position.xyz;
                gl_Position = vp * world_matrix * position;
                EmitVertex();
            }
            EndPrimitive();
        }
    }
}
