#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
void main()
{     
   // FragColor = texture(texture_diffuse1, TexCoords);
    float ratio=1.00/2.42;
     vec3 I=normalize(Position-cameraPos);
    vec3 R=refract(I,normalize(Normal),ratio);
    FragColor=vec4(texture(skybox,R).rgb,1.0);
    
}