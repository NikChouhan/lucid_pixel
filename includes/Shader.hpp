
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    //~Shader();
    void use(); 
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec3(const std::string& name, const glm::vec3 &value) const;
};