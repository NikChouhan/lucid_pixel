
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>

#pragma once

#include <string>

class Shader
{
private:
    /* data */

    std::string vertexShaderSource;
    std::string line;
    std::string fragmentShaderSource;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    int success;
    char infoLog[512];

public:
    unsigned int ID;
    
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    ~Shader();
    void use(); 
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};


Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    //vertex shader
    std::ifstream file;
    file.open(vertexShaderPath);
    if(!file.is_open())
    {
        std::cout << "Failed to open vertex shader file" << std::endl;
        // Remove the following line
        //return -1;
    }
    else 
    {
        while(std::getline(file, line))
        {
            vertexShaderSource += line + "\n";
        }
    }

    const char* vertexShaderSourcePtr = vertexShaderSource.c_str();

    //std::cout<<vertexShaderSource;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    file.close();

    //fragment shader
    file.open(fragmentShaderPath);
    if(!file.is_open())
    {
        std::cout << "Failed to open fragment shader file" << std::endl;
        //return -1;
    }
    else 
    {
        while(std::getline(file, line))
        {
            fragmentShaderSource += line + "\n";
        }
    }

    const char* fragmentShaderSourcePtr = fragmentShaderSource.c_str();

    //std::cout<<fragmentShaderSource;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    file.close();  
    //shader program

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::use()
{
    //use shader program
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

Shader::~Shader()
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}