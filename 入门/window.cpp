#include <glad.h>
#include <glfw3.h> 
#include<iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ʹ�õ��Ǻ���ģʽ(Core-profile)
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//����������
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//����GLFW��������Ϊ��ǰ�߳���������

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//glad������ָ��
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);//�ӿڣ����½����꣬ ��Ⱥ͸߶�
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //����GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
    while (!glfwWindowShouldClose(window))
    {
       
        processInput(window);//����Ƿ���esc
        glfwSwapBuffers(window);//������ɫ����
        glfwPollEvents();//�����û�д���ʲô�¼�
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//״̬���ú���
        glClear(GL_COLOR_BUFFER_BIT);//״̬ʹ�ú���
       

    }
    glfwTerminate();
    return 0;
}