#version 330
#define MAX_POINT_LIGHT_NUM 5
#define MAX_SPOT_LIGHT_NUM 5
#define PI 3.141592654

// Define Lights
struct BaseLight
{
    vec3 color;
    float ambiance_intensity;
    float diffuse_intensity;
};
struct DirectionLight
{
    BaseLight base_light;
    vec3 direction;
};
struct Atten
{
    float constant;
    float linear;
    float exp;
};
struct PointLight
{
    BaseLight base_light;
    Atten atten;
    vec3 position;
};
struct SpotLight
{
    BaseLight base_light;
    Atten atten;
    vec3 position;
    vec3 direction;
    float cutoff;
};
struct LightConfig
{
    DirectionLight dir_light;
    float point_light_num;
    PointLight point_lights[MAX_POINT_LIGHT_NUM];
    float spot_light_num;
    SpotLight spot_lights[MAX_SPOT_LIGHT_NUM];
};
// material of pbr
struct PBRMaterial
{
    vec3 albedo;
    vec3 normal;
    float metalness;
    float roughness;
};

struct VSOut
{
    vec3 w_normal;
    vec3 world_position;
    vec3 w_tangent;
    vec2 coord;
};

in VSOut vs_out;
out vec4 frag_color;

uniform LightConfig light;
uniform vec3 cam_position;
uniform sampler2D albedo;
uniform sampler2D metallic;
uniform sampler2D normal;
uniform sampler2D roughness;
uniform sampler2D ao;

float calc_ndf_ggx_tr(vec3 n, vec3 h, float r);
float calc_geometry_schlick_ggx(vec3 n, vec3 v, float k);
float calc_geometry_smith(vec3 n, vec3 view, vec3 light, float k);
vec3 calc_fresnel_schlick(vec3 h, vec3 v, vec3 f0);
vec3 calc_brdf_cook_torrance(PBRMaterial mat, vec3 view_dir, vec3 light_dir);

void main()
{
    vec3 tex_normal = texture2D(normal, vs_out.coord).xyz;
    vec3 tex_albedo = texture2D(albedo, vs_out.coord).xyz;
    vec3 tex_metallic = texture2D(metallic, vs_out.coord).xyz;
    vec3 tex_roughness = texture2D(roughness, vs_out.coord).xyz;
    vec3 tex_ao = texture2D(ao, vs_out.coord).xyz;

    // get normal
    tex_normal = tex_normal * 2 - 1;
    vec3 w_normal = normalize(vs_out.w_normal);
    vec3 w_tangent = normalize(vs_out.w_tangent);
    w_tangent = normalize(w_tangent - dot(w_tangent, w_normal) * w_normal);
    vec3 bi_tangent = normalize(cross(w_tangent, w_normal));
    mat3 tbn = mat3(w_tangent, bi_tangent, w_normal);

    PBRMaterial mat;
    mat.normal = normalize(tbn * tex_normal);
    mat.albedo = tex_albedo;
    mat.metalness = tex_metallic.x;
    mat.roughness = tex_roughness.x;
    vec3 view_dir = normalize(cam_position - vs_out.world_position);
    vec3 out_light = vec3(0, 0, 0);
    for(int i = 0; i < light.point_light_num; ++i)
    {
        vec3 light_dir = normalize(light.point_lights[i].position - vs_out.world_position);
        float distance = length(vs_out.world_position - light.point_lights[i].position);
        Atten atten = light.point_lights[i].atten;
        vec3 radiance = light.point_lights[i].base_light.color / (atten.constant + atten.linear * distance + atten.exp * distance * distance);
        vec3 brdf = calc_brdf_cook_torrance(mat, view_dir, light_dir);
        out_light += brdf * dot(mat.normal, light_dir) * radiance;
    }
    // for direction light
    {
        vec3 light_dir = normalize(light.dir_light.direction);
        vec3 radiance = light.dir_light.base_light.color;
        vec3 brdf = calc_brdf_cook_torrance(mat, view_dir, light_dir);
        out_light += brdf * dot(mat.normal, light_dir) * radiance;
    }
    vec3 ambient = vec3(0.03) * tex_albedo * tex_ao;
    frag_color = vec4(out_light + ambient, 1);
}

// r^2 / (pi((n*h)^2(r^2-1) + 1)^2)
float calc_ndf_ggx_tr(vec3 n, vec3 h, float r)
{
    float r2 = r * r;   // it is said that r = r^2 make the result better
    float nh = max(dot(n, h), 0);
    float tmp = nh * nh * (r2 - 1) + 1;
    return r2 / (PI * tmp * tmp);
}

// n * v / (n*v)(1 - k) + k)
float calc_geometry_schlick_ggx(vec3 n, vec3 v, float k)
{
//    float nv = dot(n, v);
    float nv = max(dot(n, v), 0);
    float tmp = nv * (1 - k) + k;
    return nv / tmp;
}

float calc_geometry_smith(vec3 n, vec3 view_dir, vec3 light_dir, float k)
{
    float view_dir_geom = calc_geometry_schlick_ggx(n, view_dir, k);
    float light_dir_geom = calc_geometry_schlick_ggx(n, light_dir, k);
    return view_dir_geom * light_dir_geom;
}

// fresnel 
vec3 calc_fresnel_schlick(vec3 h, vec3 v, vec3 f0)
{
    return f0 + (vec3(1) - f0) * pow(1 - dot(h, v), 5);
}

// calculate brdf of cook-torrance
vec3 calc_brdf_cook_torrance(PBRMaterial mat, vec3 view_dir, vec3 light_dir)
{
    vec3 h = normalize(view_dir + light_dir);
    // calculating dfg
    float d = calc_ndf_ggx_tr(mat.normal, h, mat.roughness);    // ndf

    float _alpha = mat.roughness;
    float _k = pow(_alpha + 1, 2) / 8;
    float geom = calc_geometry_smith(mat.normal, view_dir, light_dir, _k);  // g

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, mat.albedo, mat.metalness);
    vec3 f = calc_fresnel_schlick(h, view_dir, f0);    // f

    vec3 dfg = d * f * geom;

    // kd and ks
    vec3 ks = f;
    vec3 kd = 1 - ks;
    kd *= 1 - mat.metalness;    // 金属会吸收所有的折射光，所以没有漫反射系数为0


    vec3 f_diffuse = kd * mat.albedo / PI;
    vec3 f_specular = d * f * geom / (4 * max(dot(view_dir, mat.normal), 0) * max(dot(light_dir, mat.normal), 0) + 0.0001);

    return f_diffuse + f_specular;
}