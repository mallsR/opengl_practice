//输入输出变量
#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

// 定义不同光源
//---------------------
// directional light
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// point light
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// spot light
struct SpotLight{
    vec3 position;
    vec3 direction;
    float innerCut0ff;
    float outerCut0ff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Materials
//----------
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    // 影响镜面高光的散射/半径。
    float shininess;
};

// uniform
uniform vec3 viewPos;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

// 函数声明区域
//---------------
// function:compute directional light
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
// function : compute point light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
// function : compute spot light
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main() {
//    属性设置
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
//    first stage ： directional light
    vec3 directional_light = CalcDirLight(dirLight, norm, viewDir);
    
//    second stage ： point light
    vec3 point_light = vec3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < NR_POINT_LIGHTS; ++i) {
        point_light += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
    
//    third stage : spot light
    vec3 spot_light = CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    vec3 result = directional_light + point_light + spot_light;
    
    FragColor = vec4(result, 1.0);
}

//函数定义区域
//--------------
// function:compute directional light
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
//    光线方向
    vec3 light_dir = normalize(-light.direction);
//    diffuse
    float diff = max(0.0, dot(normal, light_dir));
//    specular
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(0.0, dot(reflect_dir, viewDir)), material.shininess);
//    combine ambient, diffuse, specular;
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}


// function : compute point light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
//    光线方向
    vec3 light_dir = normalize(light.position -  fragPos);
//    diffuse
    float diff = max(0.0, dot(normal, light_dir));
//    specular
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(0.0, dot(reflect_dir, viewDir)), material.shininess);
    
//    计算衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                     light.quadratic * (distance * distance));
    
//    combine ambient, diffuse, specular
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient * diffuse + specular);
}

// function : compute spot light
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
//    光线方向
    vec3 light_dir = normalize(fragPos - light.position);

//    compute intensity
    float theta = dot(light_dir, normalize(light.direction));
    float epsilon = light.innerCut0ff - light.outerCut0ff;
    float intensity = clamp((theta - light.outerCut0ff) / epsilon, 0.0, 1.0);
    
//    attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));
        
//    compute diff coeffieient
    float diff = max(0.0, dot(normal, -light_dir));
//    compute specular coefficient
    vec3 reflect_dir = reflect(light_dir, normal);
    float spec = pow(max(0.0, dot(reflect_dir, viewDir)), material.shininess);
    
    //    compute diffuse, specular and combine
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular);
}
