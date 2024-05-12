#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{

    int  success;
    char infoLog[512];
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices1[] = {
     0.0f, -0.5f, 0.0f,
     1.0f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f
    };  
    float vertices2[] = {
    -1.0f, -0.5f, 0.0f,
     0.0f, -0.5f, 0.0f,
    -0.5f, 0.5f,  0.0f
    };  


    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 3,   // first triangle
    //     1, 2, 3    // second triangle
    // };  

    unsigned int fragmentShader, fragment2Shader;
    unsigned int vertexShader;

    //vertex shader

    std::ifstream file;


    file.open("shaders/vertex.shader");
    if(!file.is_open())
    {
        std::cout << "Failed to open vertex shader file" << std::endl;
        return -1;
    }
    else 
    {
        std::string vertexShaderSource;
        std::string line;
        while(std::getline(file, line))
        {
            vertexShaderSource += line + "\n";
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

    }

    file.close();       //close the file, I didn't do this initially and had to debug for a while :(
    //fragment shader
    
    std::string fragmentShaderSource;
    file.open("shaders/fragment.shader");
    if(!file.is_open())
    {
        std::cout << "Failed to open fragment shader file" << std::endl;
        return -1;
    }
    else 
    {
        std::string line;
        while(std::getline(file, line))
        {
            fragmentShaderSource += line + "\n";
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
    }

    file.close();       //close the file, I didn't do this initially and had to debug for a while :(

    //fragment shader 2
    std::string fragmentShaderSource2;
    file.open("shaders/fragment2.shader");
    if(!file.is_open())
    {
        std::cout << "Failed to open fragment shader file" << std::endl;
        return -1;
    }
    else 
    {
        std::string line;
        while(std::getline(file, line))
        {
            fragmentShaderSource2 += line + "\n";
        }
        const char* fragmentShaderSourcePtr2 = fragmentShaderSource2.c_str();

        //std::cout<<fragmentShaderSource;

        
        fragment2Shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment2Shader, 1, &fragmentShaderSourcePtr2, NULL);
        glCompileShader(fragment2Shader);

        glGetShaderiv(fragment2Shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment2Shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    //shader program

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    //check for linking errors
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


    //clean up

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //shader program 2

    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram(); 
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragment2Shader);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);

    glDeleteShader(vertexShader);
    glDeleteShader(fragment2Shader);

    //check for linking errors

    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    //vertex array object
    unsigned int VAO[2], VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //generate and bind EBO 
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //linking vertex attributes

    //unbind the EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unbind the VAO

    glBindVertexArray(0);

    //render loop


    while(!glfwWindowShouldClose(window))
    {

        processInput(window);

        //rendering code

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}