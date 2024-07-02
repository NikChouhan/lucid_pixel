// At the beginning of your loop, you should initialize `lastFrame` outside of your loop.
// float lastFrame = glfwGetTime(); // Initialize this before your loop starts

while(!glfwWindowShouldClose(window))
{
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;  
    float fps = 1.f / deltaTime;

    processInput(window, deltaTime);

    // Your rendering and ImGui code here...

    ImGui::Begin("FPS");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, fps);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();

    // Update lastFrame at the end of the loop
    lastFrame = currentFrame;
}