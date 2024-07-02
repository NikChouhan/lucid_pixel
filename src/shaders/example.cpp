while(!glfwWindowShouldClose(window))
{
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;  
    processInput(window, deltaTime);


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

    float red = (float)sin(glfwGetTime());

    cubeShader.use();

    glm::vec3 lightColor = glm::vec3(red, 1.f, 1.f);

    cubeShader.setVec3("lightColor",lightColor);

    cubeShader.setVec3("material.ambient", ambient);
    cubeShader.setVec3("material.diffuse", diffuse);
    cubeShader.setVec3("material.specular", specular);
    cubeShader.setFloat("material.shininess", shininess);

    cubeShader.setVec3("lightPos", lightPos);
    cubeShader.setVec3("viewPos", cameraPos);

    cubeShader.setMat4("view", view);
    cubeShader.setMat4("projection", projection);
    cubeShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);

    //lamp options

    lampShader.use();

    lampShader.setFloat("red", red);

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
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, fps);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //check and call events and swap the buffers

    // Rendering
    //(Your code clears your framebuffer, renders your other stuff etc.)
    // (Your code calls glfwSwapBuffers() etc.)
    glfwSwapBuffers(window);
}