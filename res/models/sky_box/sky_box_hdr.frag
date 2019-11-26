#version 330

out vec4 frag_color;
in vec3 tex_coord;
uniform sampler2D env_map_hdr;

const vec2 inv_atan = vec2(0.1591, 0.3183);
vec2 sample_from_hdr(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= inv_atan;
    uv += 0.5;
    return uv;
}

vec3 ACESToneMapping(vec3 color, float adapted_lum)
{
	const float A = 2.51f;
	const float B = 0.03f;
	const float C = 2.43f;
	const float D = 0.59f;
	const float E = 0.14f;

	color *= adapted_lum;
	return (color * (A * color + B)) / (color * (C * color + D) + E);
}

void main() {
    vec2 uv = sample_from_hdr(normalize(tex_coord));
    frag_color = texture(env_map_hdr, uv);
	frag_color.rgb = ACESToneMapping(frag_color.rgb, 0.8);
}

