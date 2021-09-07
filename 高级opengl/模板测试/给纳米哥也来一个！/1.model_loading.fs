#version 330 core
out vec4 FragColor;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
struct Material {
    sampler2D difffuse;
    sampler2D specular;    
    float shininess;
}; 
struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};
#define NR_POINT_LIGHTS 4

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;
uniform Material material;
uniform sampler2D EmissionMap;
uniform float Moffset;
uniform vec3 LL;

uniform DirLight dirLight;
vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir)
{
    vec3 lightDir=normalize(-light.direction);
    float diff=max(dot(normal,lightDir),0.0);

    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

    vec3 ambient=light.ambient*vec3(texture(texture_diffuse1,TexCoords));
    vec3 diffuse=light.diffuse*diff*vec3(texture(texture_diffuse1,TexCoords));
    vec3 specular=light.specular*spec*vec3(texture(texture_specular1,TexCoords));
    return (ambient+diffuse+specular);
}

uniform PointLight pointLights[NR_POINT_LIGHTS];
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir)
{
       vec3 lightDir = normalize(light.position - fragPos);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                 light.quadratic * (distance * distance));    
    // 合并结果
    vec3 ambient  = light.ambient  * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular); 
}
uniform SpotLight spotLight;
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
      vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}


void main()
{    //material.difffuse=texture_diffuse1;
     //material.specular=texture_specular1;
    
    vec3 norm =normalize(Normal);
    vec3 ViewDir=normalize(viewPos-FragPos);

    vec3 result=CalcDirLight(dirLight,norm,ViewDir);

    for(int i=0;i<=0;i++)
    result+=CalcPointLight(pointLights[i],norm,FragPos,ViewDir);

    result+=CalcSpotLight(spotLight,norm,FragPos,ViewDir);
    //vec3 emission =vec3(LL)*texture(EmissionMap,vec2(TexCoords.x,TexCoords.y+Moffset)).rgb;
    //result+=emission;
    FragColor=vec4(result,1.0);
    
} 