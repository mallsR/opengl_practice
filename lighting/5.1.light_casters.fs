// 5. light casters.fs

#version 330 core
in vec3 Normal;
in vec3 FragPos;
// diffuse map and specular map coord
in vec2 TexCoords;

out vec4 FragColor;

// materials
struct Material{
    sampler2D diffuse;
    sampler2D specular;
    // 影响镜面高光的散射/半径。
    float shininess;
};

// Light
struct Light {
    // directional light use light direction
    // vec3 direction;
    
//    point light use
//    vec3 position;
    float constant;
    float linear;
    float quadratic;
    
//    spot light use
    vec3 position;
    vec3 direction;
    float cut0ff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 摄影机的位置，用于计算specular lighting
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    //    spot light use
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    
    if (theta > cut0ff) {
        // ambient light
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        //        vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
        
        // Diffuse lighting
        vec3 norm = normalize(Normal);
        //    directional light use light.direction
        //    vec3 lightDir = normalize(-light.direction);
        
        //    point light use
        //        vec3 lightDir = normalize(light.position - viewPos);
        // compute diffuse compoent
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoords));
        //        vec3 diffuse = diff * light.diffuse * texture(material.diffuse, TexCoords).rgb;
        
        // Specular lighting
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        // compute specular compoent
        float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);
        // 镜面强度(Specular Intensity)
        vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoords));
        //        vec3 specular = spec * light.specular * texture(material.specular, TexCoords).rgb;
        
        //    point light use : compute attenuation
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
        //    ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
        
        vec3 result  = (ambient + diffuse + specular);
        FragColor = vec4(result, 1.0);
    } else {
        FragColor = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);
    }
}

