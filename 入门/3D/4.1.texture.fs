#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
uniform float aph;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
	FragColor=mix(texture(texture1,TexCoord),texture(texture2,vec2(TexCoord.x,TexCoord.y)),0.2);
	//对第三个参数进行线性插值，如果第三个值是0.0，它会返回第一个输入；如果是1.0，会返回第二个输入值。
	//0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。
}