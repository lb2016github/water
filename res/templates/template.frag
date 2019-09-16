#version 330
#define MAX_POINT_LIGHT_NUM 5
#define MAX_SPOT_LIGHT_NUM 5

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

