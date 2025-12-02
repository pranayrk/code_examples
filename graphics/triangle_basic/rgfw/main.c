#include "file.h"
#include "linmath.h"

#define RGFW_OPENGL
#define RGFW_USE_XDL // feel free to remove this line if you don't want to use XDL (-lX11 -lXrandr -lGLX will be required)
#define RGFW_ALLOC_DROPFILES
#define RGFW_IMPLEMENTATION
#define RGFW_PRINT_ERRORS
#define RGFW_DEBUG
#define GL_SILENCE_DEPRECATION
#include <RGFW.h>

#define RGL_LOAD_IMPLEMENTATION
#include "rglLoad.h"

#include <stdbool.h>

typedef struct Vertex {
    vec2 pos;
    vec3 col;
} Vertex;

static const Vertex vertices[3] = {
    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
};


// settings
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


RGFW_window* setupRGFW() {
    RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
    hints->major = 3;
    hints->minor = 3;
    RGFW_setGlobalHints_OpenGL(hints);
	RGFW_window* window = RGFW_createWindow("LearnOpenGL", SCR_WIDTH, SCR_HEIGHT, SCR_WIDTH, SCR_HEIGHT, RGFW_windowAllowDND | RGFW_windowCenter | RGFW_windowScaleToMonitor | RGFW_windowOpenGL);
    if (window == NULL)
    {
        printf("Failed to create RGFW window\n");
        exit(0);
    }
    RGFW_window_setExitKey(window, RGFW_escape);
    RGFW_window_makeCurrentContext_OpenGL(window);

    if (RGL_loadGL3((RGLloadfunc)RGFW_getProcAddress_OpenGL)) {
        printf("Failed to initialize GLAD\n");
        exit(0);
    }
    return window;
}

GLuint setupProgram() {
    const char* vertexShaderSource = read_file("shader.vert");
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
        return -1;
    }
    const char *fragmentShaderSource = read_file("shader.frag");
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
        return -1;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        return -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

int main(void) {
    RGFW_window* window = setupRGFW();
    GLuint program = setupProgram();

    
    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetUniformLocation(program, "vPos");
    const GLint vcol_location = glGetUniformLocation(program, "vCol");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (void*) offsetof(Vertex, col));

    while (RGFW_window_shouldClose(window) == RGFW_FALSE) {
        RGFW_event event;

        while (RGFW_window_checkEvent(window, &event)) {
            if (event.type == RGFW_quit) {
                break;
            }
        }

        int width, height;
        RGFW_window_getSize(window, &width, &height);
        const float ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        mat4x4 m, p, mvp;
        mat4x4_identity(m);
//        mat4x4_rotate_Z(m, m, (float) glXGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        RGFW_window_swapBuffers_OpenGL(window);
        RGFW_pollEvents();
    }

    glDeleteVertexArrays(1, &vertex_array);
    glDeleteProgram(program);

    RGFW_window_close(window);
    return 0;
}
