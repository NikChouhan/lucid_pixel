#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h" 

#include <glad/glad.h>

#include <glfw/glfw3.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include "includes/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "includes/load_texture.hpp"
#include "includes/Camera.hpp"


const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

double lastX = 400, lastY = 300;
bool firstMouse = true;

float yaw = -90.0f;
float pitch = 0.0f;

bool cursor = false;

float fov = 45.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{

    Camera camera(cameraPos, cameraUp, yaw, pitch);

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

    //coordinate system

    // glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    // glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // glm::mat4 projection = glm::mat4(1.0f);
    // projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, 0.1f, 100.0f);



    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };




    //load and create a texture

    //int width, height, nrChannels; 
    unsigned int diffuseMap = load_texture("src/textures/container2.png");
    unsigned int specularMap = load_texture("src/textures/container2_specular.png");
    unsigned int emmisionMap = load_texture("src/textures/matrix.jpg");

    // int width1, height1, nrChannels1;
    // unsigned int texture1 = load_texture("textures/cat.png", &width1, &height1, &nrCha nnels1);

  
    Shader cubeShader("src/shaders/cube.vertex", "src/shaders/cube.fragment");
    Shader lampShader("src/shaders/lamp.vertex", "src/shaders/lamp.fragment");
    
    //vertex array object
    unsigned int cubeVAO, VBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    //generate and bind EBO 
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //linking vertex attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0); 
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    //unbind the EBO
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unbind the cubeVAO

    glBindVertexArray(0);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //matrices transformations

    //

    //unsigned int transformLOC = glGetUniformLocation(shader.ID, "transform");

    glEnable(GL_DEPTH_TEST);  

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback); 


    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    float red = 1.f;
    float blue = 0.5f;
    float green = 0.31f;


    //cube material properties
    //glm::vec3 ambient = { 1.f, 0.5f, 0.31f };
    //glm::vec3 diffuse = { 1.f, 0.5f, 0.31f };
    glm::vec3 specular = { 0.5f, 0.5f, 0.5f };
    //glm::vec3 specular = { red, blue, green };

    float shininess = 64.0f;

    //light properties
    glm::vec3 lightAmbient = { 0.2f, 0.2f, 0.2f };
    glm::vec3 lightDiffuse = { 0.5f, 0.5f, 0.5f };
    glm::vec3 lightSpecular = { 1.f, 1.f, 1.f };
    //glm::vec3 lightSpecular = { red, blue, green };


    //Imgui

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark;
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplOpenGL3_Init();

    float lastFrame = 0.0f; // Time of last frame

    //accumulator for FPS update delay

    float fpsUpdate = 0.5f;
    float accumulator = 0.0f;
    float displayFPS = 0.0f;


    cubeShader.use();
    cubeShader.setInt("material.diffuse", 0);

    cubeShader.setInt("material.specular", 1);
    
    cubeShader.setInt("material.emission", 2);


    //render loop

    while(!glfwWindowShouldClose(window))
    {
        float deltaTime = 0.0f;	// Time between current frame and last frame

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        processInput(window, deltaTime);

        accumulator += deltaTime;

        if (accumulator >= fpsUpdate) {
            // Update the FPS display value
            displayFPS = 1.f / deltaTime;
            accumulator = 0.0f; // Reset accumulator
        }

        float fps = 1.f / deltaTime;
        //rendering code

        glfwPollEvents();


        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // double time = glfwGetTime();
        // std::cout<<time<<std::endl;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        //glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        float time = (glfwGetTime()) * 0.1f;
        //trans = glm::rotate(trans, time, glm::vec3(0.0f, 0.0f, 1.0f));
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        //draw triangle

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glm::mat4 model = glm::mat4(1.f);

        lightDiffuse = { red, blue, green };

        cubeShader.use();

        ImGui::Begin("Material Colors Diffuse Light: ");
        ImGui::SliderFloat("Red: ", &red, 0.f, 1.f);
        ImGui::SliderFloat("Blue: ", &blue, 0.f, 1.f);
        ImGui::SliderFloat("Green: ", &green, 0.f, 1.f);
        ImGui::End();

        //glm::vec3 lightColor = glm::vec3(red, blue, green);

        //cubeShader.setVec3("lightColor",lightColor);

        //cubeShader.setVec3("material.ambient", ambient);
        //cubeShader.setVec3("material.specular", specular);
        cubeShader.setFloat("material.shininess", shininess);

        //cubeShader.setInt("material.diffuse", 0);

        cubeShader.setVec3("light.position", lightPos);
        cubeShader.setVec3("light.ambient", lightAmbient);
        cubeShader.setVec3("light.diffuse", lightDiffuse);
        cubeShader.setVec3("light.specular", lightSpecular);

        cubeShader.setFloat("time", time);

        cubeShader.setVec3("lightPos", lightPos);
        cubeShader.setVec3("viewPos", cameraPos);

        cubeShader.setMat4("view", view);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, emmisionMap);

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        //lamp options

        lampShader.use();

        lampShader.setFloat("red", red);
        lampShader.setFloat("blue", blue);
        lampShader.setFloat("green", green);


        model = glm::mat4(1.f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        lampShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        /*ImGui::Begin("Material");
        ImGui::Text("hello");
        ImGui::End();*/

        ImGui::Begin("FPS");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / displayFPS, displayFPS);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //check and call events and swap the buffers

        // Rendering
        //(Your code clears your framebuffer, renders your other stuff etc.)
        // (Your code calls glfwSwapBuffers() etc.)
        glfwSwapBuffers(window);

        lastFrame = currentFrame;
    }

     ImGui_ImplOpenGL3_Shutdown();
     ImGui_ImplGlfw_Shutdown();

     ImGui::DestroyContext();

     glDeleteVertexArrays(1, &cubeVAO);
     glDeleteVertexArrays(1, &lightVAO);
     glDeleteBuffers(1, &VBO);
     
     glfwDestroyWindow(window);

     glfwTerminate();
     return 0;
}


static bool cursorEnabled = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    //std::cerr << "framebuffer_size_callback called" << std::endl; //Test code
} 

void processInput(GLFWwindow *window, float deltaTime)
{

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed =  deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;

    // In your processInput function:
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !cursor)
    {
        cursorEnabled = !cursorEnabled;
        glfwSetInputMode(window, GLFW_CURSOR, cursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

        if (!cursorEnabled) // If we are disabling the cursor, capture the current mouse position
        {
            glfwGetCursorPos(window, &lastX, &lastY);
            firstMouse = true; // Ensures the camera doesn't jump on the next mouse movement
        }

        cursor = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
    {
        cursor = false;
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!cursorEnabled)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.06f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }    
}  


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f; 
}