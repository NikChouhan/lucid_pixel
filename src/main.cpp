#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "load_texture.hpp"


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

    //triangle vertices with colors

    // float vertices[] = {
    //     // positions         // colors
    //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    //    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    //     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    // };       

    //texture coordinates

    
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };



    //load and create a texture

    int width, height, nrChannels; 
    unsigned int texture = load_texture("textures/maxresdefault.jpg", &width, &height, &nrChannels);
    
    int width1, height1, nrChannels1;
    unsigned int texture1 = load_texture("textures/wall.jpg", &width1, &height1, &nrChannels1);

    

    //triangle vertices

    // float vertices[] = {
    // -0.5f, -0.5f, 0.0f,
    //  0.5f, -0.5f, 0.0f,
    //  0.0f,  0.5f, 0.0f
    // };  

    // for making a rectangle

    
    // float vertices[] = {
    //  0.5f,  0.5f, 0.0f,  // top right
    //  0.5f, -0.5f, 0.0f,  // bottom right
    // -0.5f, -0.5f, 0.0f,  // bottom left
    // -0.5f,  0.5f, 0.0f   // top left 
    // };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    Shader shader("shaders/vertex.shader", "shaders/fragment.shader");
    
    //vertex array object
    unsigned int VAO[2], VBO;
    glGenVertexArrays(2, VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    //generate and bind EBO 
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //linking vertex attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    //second rectangle

    glBindVertexArray(VAO[1]);

    unsigned int VBO1;

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    //generate and bind EBO 
    unsigned int EBO1;
    glGenBuffers(1, &EBO1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //linking vertex attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    //unbind the EBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unbind the VAO

    glBindVertexArray(0);


    //matrices transformations

    //

    unsigned int transformLOC = glGetUniformLocation(shader.ID, "transform");


    //render loop

    while(!glfwWindowShouldClose(window))
    {

        processInput(window);

        //rendering code

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // double time = glfwGetTime();
        // std::cout<<time<<std::endl;
        // float greenValue = (sin(time) / 2.0f) + 0.5f;
        // float redValue = (cos(time) / 2.0f) + 0.5f;
        // //float blueValue = (tan(time) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        float time = glfwGetTime();
        trans = glm::rotate(trans, time*sin(time), glm::vec3(0.0f, 0.0f, 1.0f));
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        //draw triangle
        shader.use();

        glUniformMatrix4fv(transformLOC, 1, GL_FALSE, glm::value_ptr(trans));

        shader.setInt("textures", 0);
        //glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f);



        glBindVertexArray(VAO[0]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        //draw rectangle2

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glm::mat4 trans1 = glm::mat4(1.0f);
        trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0.0f));
        trans1 = glm::rotate(trans1, time*sin(time), glm::vec3(0.0f, 0.0f, 1.0f));



        glUniformMatrix4fv(transformLOC, 1, GL_FALSE, glm::value_ptr(trans1));

        shader.use();
        shader.setInt("textures", 1);

        glBindVertexArray(VAO[1]);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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