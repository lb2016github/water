#version 330

struct BaseLight{
	vec3 color;
	float ambiant_intensity;
	float diffuse_intensity;
};
struct DirectionLight{
	BaseLight base_light;
	vec3 direction;
};

out vec4 frag_color;
uniform sampler2D diffuse;
uniform DirectionLight dir_light;
uniform vec3 eye_pos;
in struct
{
	vec3 normal;
	vec2 tex_coord;
	vec3 world_pos;
}vs_out;

// base on Phong lighting model, obj color should be multiplied outside
vec3 calc_dir_color_factor(vec3 light_dir, vec3 normal, BaseLight base_light)
{
	vec3 ambiant_color = vec3(0, 0, 0);
	vec3 diffuse_color = vec3(0, 0, 0);
	vec3 specular_color = vec3(0, 0, 0);
	// calculate ambiant color
	ambiant_color = base_light.color * base_light.ambiant_intensity;
    // calculating diffuse color
    float diffuse_factor = dot(normal, -light_dir);
	if(diffuse_factor > 0)
	{
		// calculating diffuse color
        diffuse_color = base_light.color * base_light.diffuse_intensity * diffuse_factor;

        // calculating specular color
		vec3 reflect_dir = normalize(reflect(light_dir, normal));
		vec3 eye_dir = normalize(eye_pos - world_pos);
		float spe_factor = dot(eye_dir, reflect_dir);
		if(spe_factor > 0)
		{
            specular_color = base_light.color * spe_factor;
		}
	}
    return ambiant_color + diffuse_color + specular_color;
}

void main(){
    vec4 color = texture2D(diffuse, vs_out.tex_coord.xy);
	// calulate direction color
	vec3 dir_color_factor = calc_dir_color_factor(dir_light.direction, vs_out.normal, dir_light.base_light);
	vec3 dir_color = dir_color_factor * color.xyz;
	frag_color = vec4(dir_color, 1);
}