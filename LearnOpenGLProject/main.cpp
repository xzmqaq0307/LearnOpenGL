#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "learnopengl/shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // ��ʼ��GLFW
    glfwInit();
    // ���汾�źʹΰ汾�Ŷ�����Ϊ3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // ʹ�ú���ģʽ
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // ����һ������, ��, ��, ����
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create CLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 
    glfwMakeContextCurrent(window);

    // ������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("3-3-shader.vs", "3-3-shader.fs");
    
    float vertices[] = {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int VBO, VAO;
    // ������Ӧ��VAO���󣬲��Ұ��ڶ�Ӧ1
    glGenVertexArrays(1, &VAO);
    // ����VBO���󣬲��Ұ���1
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // ������, �ֽ���, ��������, �ж��Ƿ�Ҫ�����޸�
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // ��ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ���һ��GLFW�Ƿ�Ҫ���Ƴ�
    while (!glfwWindowShouldClose(window))
    {
        // ���������¼�
        processInput(window);
        // ���ö�Ӧ�Ĵ�����ɫ
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // ���������ɫ
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ������ɫ����, ����һ�����б��������ƣ����ҽ���
        glfwSwapBuffers(window);
        
        // ���������û��ʲô�����¼������´���״̬�����ҵ��ö�Ӧ�Ļص�����
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // OpenGl��Ⱦ���ڳߴ��С�����ӿ�
    glViewport(0, 0, width, height);
}