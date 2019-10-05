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

uniform vec3 view;


// r^2 / (pi((n*h)^2(r^2-1) + 1)^2)
float calc_ndf_ggx_tr(vec3 n, vec3 h, float r)
{
    float r2 = r * r;
    float nh = n.dot(h);
    float tmp = nh * nh * (r2 - 1) + 1;
    return r2 / (PI * tmp * tmp);
}

// n * v / (n*v)(1 - k) + k)
float calc_geometry_schlick_ggx(vec3 n, vec3 v, float k)
{
    float nv = n.dot(v);
    float tmp = nv * (1 - k) + k;
    return nv / tmp;
}

float calc_geometry_smith(vec3 n, vec3 view, vec3 light, float k)
{
    float view_geom = calc_geometry_schlick_ggx(n, view, k);
    float light_geom = calc_geometry_schlick_ggx(n, light, k);
    return view_geom * light_geom;
}

// fresnel 
float calc_fresnel_schlick(vec3 h, vec3 v, vec3 f0)
{
    return f0 + (1 - f0)* pow(1 - dot(h, v), 5);
}

// calculate brdf of cook-torrance
vec3 calc_brdf_cook_torrance(PBRMaterial mat, vec3 view_dir, vec3 light_dir)
{
    vec3 h = (view_dir + light_dir) / length(view_dir + light_dir);
    // calculating dfg
    float d = calc_ndf_ggx_tr(mat.normal, h, mat.roughness);    // f

    float _alpha = mat.roughness;
    float _k = pow(_alpha + 1, 2) / 8;
    float geom = calc_geometry_smith(mat.normal, view_dir, light_dir, _k);  // g

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, mat.albedo, mat.metalness);
    float f = calc_fresnel_schlick(h, view_dir, f0);    // f

    float dfg = d * f * geom;

    // kd and ks
    float kd = 1 - f;
    float ks = f;

    vec3 f_diffuse = kd * mat.albedo / PI;
    vec3 f_specular = ks * d * f * geom / (4 * dot(view_dir, mat.normal) * dot(light_dir, mat.normal));

    return f_diffuse + f_specular;
}
