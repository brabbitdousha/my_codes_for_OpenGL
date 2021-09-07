#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D difffuse;
    sampler2D specular;    
    float shininess;
}; 
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;


uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D EmissionMap;
uniform float Moffset;
uniform vec3 LL;
void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.difffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.difffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * (vec3(texture(material.specular,TexCoords))));  
    vec3 emission =vec3(LL)*texture(EmissionMap,vec2(TexCoords.x,TexCoords.y+Moffset)).rgb;

    vec3 result = ambient + diffuse + specular+emission;
    FragColor = vec4(result, 1.0);
} 