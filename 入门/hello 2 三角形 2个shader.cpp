#include <glad.h>
#include <glfw3.h> 
#include<iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"  gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0";

const char* fragmentShader1Source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.5f, 1.0f, 0.1f);\n"
"}\0";

const char* fragmentShader2Source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 0.1f);\n"
"}\0";
int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ʹ�õ��Ǻ���ģʽ(Core-profile)
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//����GLFW��������Ϊ��ǰ�߳���������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//glad������ָ��
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//������id�����ã���glcreate������ɫ�����͡�

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//��ɫ�������ַ�����������ɫ��Դ��
	glCompileShader(vertexShader);


	unsigned int fragmentShader1;
	fragmentShader1= glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShader1);
	
	unsigned int fragmentShader2;
	fragmentShader2= glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShader2);
	
   

	unsigned int shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	
	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);


	//glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);
    
 float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };
	

	

    unsigned int VBOs[2],VAOs[2];
	glGenBuffers(2, VBOs);//һ������id����һ��VBO����
	glGenVertexArrays(2, VAOs);
	

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//��VBO�󶨵����������
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	//���û���������ݸ��Ƶ���ǰ�󶨻���ĺ���
	//��һ��������Ŀ�껺�����ͣ��ڶ����Ǵ�С�������������ݣ�
	//���ĸ�ָ���Կ���ι������������
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//������ɫ���е�location=0������������vec3��3��ֵ��ɣ��������ͣ��Ƿ��׼��
	//��������ʼλ�õ�ƫ������
	glEnableVertexAttribArray(0);//�ö�������λ��ֵ�����ö�������
	
	
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);//����Ƿ���esc
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//״̬���ú���
		glClear(GL_COLOR_BUFFER_BIT);//״̬ʹ�ú���
		
		glUseProgram(shaderProgram1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glUseProgram(shaderProgram2);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);//������ɫ����
		glfwPollEvents();//�����û�д���ʲô�¼�
		


	}
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);


	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
