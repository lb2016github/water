#version 420
layout(triangles) in;
layout(triangle_strip, max_vertices=200) out;

struct VSOut
{
    vec3 position;
    vec3 trans;
    float metallic;
    float roughness;
};

uniform mat4 world_matrix;
uniform mat4 vp;

out VSOut vs_out;

void main() {
    for(float m = 0.1; m <= 1; m += 0.2)
    {
        for(float r = 0.1; r <= 1; r += 0.2)
        {
            mat4 world_mtx = world_matrix;
            vs_out.roughness = r;
            vs_out.metallic = m;
            vs_out.trans = vec3((r - 0.5) * 15, (m - 0.5) * 15, 0);
            world_mtx[3][0] += vs_out.trans.x;
            world_mtx[3][1] += vs_out.trans.y;

            for(int i = 0; i < 3; ++i)
            {
                vec4 position = gl_in[i].gl_Position;
                vs_out.position = position.xyz;
                gl_Position = vp * world_mtx * position;
                EmitVertex();
            }
            EndPrimitive();
        }
    }
}
