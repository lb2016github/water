#version 330
layout(points) in;
layout(triangle_strip, max_vertices=17) out;

uniform float length;      // size cube
uniform mat4 wvp;

void main() {
    // front
    // A ----- D
    // |       |
    // |       |
    // B ------C
    // back
    // d ----- a
    // |       |
    // |       |
    // c ------b
    // BCADadbcBCDcdABba



    float halfLen = length / 2.0f;
    vec4 center = gl_in[0].gl_Position;

    vec4 A = wvp * (center + vec4(-halfLen, halfLen, halfLen, 0));
    vec4 B = wvp * (center + vec4(-halfLen, -halfLen, halfLen, 0));
    vec4 C = wvp * (center + vec4(halfLen, -halfLen, halfLen, 0));
    vec4 D = wvp * (center + vec4(halfLen, halfLen, halfLen, 0));

    vec4 a = wvp * (center + vec4(-halfLen, halfLen, -halfLen, 0));
    vec4 b = wvp * (center + vec4(-halfLen, -halfLen, -halfLen, 0));
    vec4 c = wvp * (center + vec4(halfLen, -halfLen, -halfLen, 0));
    vec4 d = wvp * (center + vec4(halfLen, halfLen, -halfLen, 0));
    // front
    gl_Position = B;
    EmitVertex();
    gl_Position = C;
    EmitVertex();
    gl_Position = A;
    EmitVertex();
    gl_Position = D;
    EmitVertex();
    gl_Position = a;
    EmitVertex();
    gl_Position = d;
    EmitVertex();
    gl_Position = b;
    EmitVertex();
    gl_Position = c;
    EmitVertex();
    gl_Position = B;
    EmitVertex();
    gl_Position = C;
    EmitVertex();
    gl_Position = D;
    EmitVertex();
    gl_Position = c;
    EmitVertex();
    gl_Position = d;
    EmitVertex();
    gl_Position = A;
    EmitVertex();
    gl_Position = B;
    EmitVertex();
    gl_Position = b;
    EmitVertex();
    gl_Position = a;
    EmitVertex();

    EndPrimitive();

}
