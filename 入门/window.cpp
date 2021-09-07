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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//我们使用的是核心模式(Core-profile)
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//宽，长，名字
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);//告诉GLFW将它设置为当前线程主上下文

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//glad管理函数指针
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);//视口，左下角坐标， 宽度和高度
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
    while (!glfwWindowShouldClose(window))
    {
       
        processInput(window);//检查是否按下esc
        glfwSwapBuffers(window);//交换颜色缓冲
        glfwPollEvents();//检查有没有触发什么事件
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);//状态使用函数
       

    }
    glfwTerminate();
    return 0;
}