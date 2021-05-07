#ifndef _SHADER_H_
#define _SHADER_H_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#pragma warning(disable:4996)

GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint shaderProgram;

static char* readShaderSource(const char* shaderFile) {
    std::ifstream myfile(shaderFile);
    myfile.seekg(0, std::ios::end);
    size_t size = myfile.tellg();
    std::string buffer(size, ' ');
    myfile.seekg(0);
    myfile.read(&buffer[0], size);

    char* cstr = new char[buffer.length()];
    strcpy(cstr, buffer.c_str());

    return cstr;
}

void CreateVertexBuffer() {
    float vertices2[] = {
     1.f,  1.f, 0.0f,  // 우측 상단
     1.f, -1.f, 0.0f,  // 우측 하단
    -1.f, -1.f, 0.0f,  // 좌측 하단
    -1.f,  1.f, 0.0f,   // 좌측 상단
    1.f,  1.f, 0.0f,  // 우측 상단
     1.f, -1.f, 0.0f,  // 우측 하단
    -1.f, -1.f, 0.0f,  // 좌측 하단
    -1.f,  1.f, 0.0f   // 좌측 상단
    };
    unsigned int indices2[] = {  // 0부터 시작한다는 것을 명심하세요!
    0, 1, 3,   // 첫 번째 삼각형
    1, 2, 3    // 두 번째 삼각형
    };

    GLuint indices[] = {  // note that we start from 0!
        0, 1, 2,
        1, 2, 3,

        4, 5, 6,
        5, 6, 7,

        0, 2, 4,
        2, 4, 6,

        1, 5, 3,
        3, 5, 7,

        0, 1, 4,
        1, 4, 5,

        2, 3, 6,
        3, 6, 7
    };

    GLfloat vertices[] =
    {
        -1.f, 1.f, -1.f,
        -1.f, 1.f, 1.f,
        1.f, 1.f, -1.f,
        1.f, 1.f, 1.f,
        -1.f, -1.f, -1.f,
        -1.f, -1.f, 1.f, 
        1.f, -1.f, -1.f,
        1.f, -1.f, 1.f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CompileShaders() {
    shaderProgram = glCreateProgram();

    GLuint vertexShader;
    GLchar ss[] = "v_shader.glsl";
    GLchar* str = readShaderSource(ss);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &str, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar ff[] = "f_shader.glsl";
    GLchar* str2 = readShaderSource(ff);
    glShaderSource(fragmentShader, 1, &str2, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);


    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glLinkProgram(shaderProgram);
}

#endif