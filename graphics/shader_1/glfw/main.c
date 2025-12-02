#include "file.h"
#define GLAD_GL_IMPLEMENTATION
#include "glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    3.0f, -1.0f, 0.0f,
    -1.0f,  3.0f, 0.0f,
};

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void checkSuccess(GLuint shader, GLuint infoType) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, infoType, &success);

    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error:\n");
        printf(infoLog);
        exit(EXIT_FAILURE);
    }
}

GLFWwindow* setupGLFW() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    return window;
}

const GLuint setupProgram() {
    const char* vertexShaderText = read_file("shader.vert");
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
    glCompileShader(vertexShader);
    checkSuccess(vertexShader, GL_COMPILE_STATUS);

    const char* fragmentShaderText = read_file("shader.frag");
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
    glCompileShader(fragmentShader);
    checkSuccess(fragmentShader, GL_COMPILE_STATUS);

    const GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glUseProgram(program);

    checkSuccess(program, GL_LINK_STATUS);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}


const GLuint setupVAO() {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    return VAO;
}


int main(void)
{
    GLFWwindow* window = setupGLFW();
    GLuint program = setupProgram();
    GLuint VAO = setupVAO();


    float deltaTime = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0,0, width, height);


        vec2 screen = { width, height };
        glUniform2fv(glGetUniformLocation(program, "iResolution"), 1, &screen[0]);


        double currentFrame = glfwGetTime();
        printf("%d\n", currentFrame);
        glUniform1f(glGetUniformLocation(program, "iTime"), (int) currentFrame);


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

