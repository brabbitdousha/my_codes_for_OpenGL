#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{     float ambientStrength=0.1;
      vec3 ambient=ambientStrength*lightColor;//环境光照
       
      vec3 norm=normalize(Normal);
      vec3 lightDir=normalize(lightPos-FragPos);
      float diff=max(dot(norm,lightDir),0.0);//漫反射
      vec3 diffuse=diff*lightColor;

       float specularStrength=0.5; //镜面光照
       vec3 viewDir=normalize(viewPos-FragPos);
       vec3 reflectDir=reflect(-lightDir,norm);
       //reflect函数要求第一个向量是从光源指向片段位置的向量，但是lightDir当前正好相反，
       //是从片段指向光源（由先前我们计算lightDir向量时，减法的顺序决定）。
       //为了保证我们得到正确的reflect向量，我们通过对lightDir向量取反来获得相反的方向。
       //第二个参数要求是一个法向量，所以我们提供的是已标准化的norm向量。
       float spec=pow(max(dot(viewDir,reflectDir),0.0),32);
       vec3 specular=specularStrength*spec*lightColor;

      vec3 result=(ambient+diffuse+specular)*objectColor;
    FragColor = vec4(result, 1.0);
}