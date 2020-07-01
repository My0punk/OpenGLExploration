#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;
    int width, height;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "GL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW INIT FAILED" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLuint vertBufferName;
    GLfloat vertBuf[] = {
        +0.0f, +0.0f,
        +1.0f, +0.0f, +0.0f,
        +1.0f, +1.0f,
        +1.0f, +0.0f, +0.0f,
        -1.0f, +1.0f,
        +1.0f, +0.0f, +0.0f,
        -1.0f, -1.0f,
        +1.0f, +0.0f, +0.0f,
        +1.0f, -1.0f,
        +1.0f, +0.0f, +0.0f,
    };

    glGenBuffers(1, &vertBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferName);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertBuf), vertBuf, GL_STATIC_DRAW);

    //Set up vertex data in vertex buffer.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

    //set up color data in vertex buffer
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));

    GLushort indices[] = { 0,1,2,0,3,4 };
    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //get window size in pixels for viewport
        glfwGetFramebufferSize(window, &width, &height);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, width, height);
        /*glDrawArrays(GL_TRIANGLES, 0,6);*/
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}