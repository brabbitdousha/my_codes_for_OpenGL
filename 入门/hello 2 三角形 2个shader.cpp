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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//我们使用的是核心模式(Core-profile)
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//告诉GLFW将它设置为当前线程主上下文
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//glad管理函数指针
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//还是用id来引用，给glcreate传递着色器类型。

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//着色器对象，字符串数量，着色器源码
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
	glGenBuffers(2, VBOs);//一个缓冲id生成一个VBO对象
	glGenVertexArrays(2, VAOs);
	

	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//把VBO绑定到这个类型上
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	//把用户定义的数据复制到当前绑定缓冲的函数
	//第一个参数是目标缓冲类型，第二个是大小，第三个是数据，
	//第四个指定显卡如何管理给定的数据
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//顶点着色器中的location=0，顶点属性是vec3，3个值组成，数据类型，是否标准化
	//步长，起始位置的偏移量。
	glEnableVertexAttribArray(0);//用顶点属性位置值，启用顶点属性
	
	
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(secondTriangle),secondTriangle,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	while (!glfwWindowShouldClose(window))
	{

		processInput(window);//检查是否按下esc
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
		glClear(GL_COLOR_BUFFER_BIT);//状态使用函数
		
		glUseProgram(shaderProgram1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glUseProgram(shaderProgram2);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glfwSwapBuffers(window);//交换颜色缓冲
		glfwPollEvents();//检查有没有触发什么事件
		


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
