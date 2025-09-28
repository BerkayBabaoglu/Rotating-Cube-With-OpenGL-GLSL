#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Button.h"
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] = {
    // positions
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

float triangleVertices[] = {
    0.0f,0.5f,0.0f,
    -0.5f,-0.5f,0.0f,
    0.5f,-0.5f,0.0f,

    0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,-0.5f,

    -0.5f, -0.5f,-0.5f,
    -0.5f, -0.5f, 0.5f,
     0.0f,  0.5f, 0.0f,

     0.5f, -0.5f,-0.5f,
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.5f,

     -0.5f, -0.5f, -0.5f,
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, -0.5f,

     -0.5f,-0.5f,0.5f,
     0.5f, -0.5f,0.5f,
     0.0f, 0.5f, 0.0f
};

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed!\n";
        return -1;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Rotating Cube", monitor, NULL); //tam ekran

    //GLFWwindow* window = glfwCreateWindow(1920, 1080, "Rotating Cube", NULL, NULL); //pencere
    
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW init failed\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    
    Shader shader("Shaders/cube.vert", "Shaders/cube.frag"); //shader yukle

    //kup icin vbo ve vao
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //ucgen icin
    GLuint triangleVBO, triangleVAO;
    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);

    //kup icin
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //ucgen icin
    glBindVertexArray(triangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Button exitButton(0.7f, 0.8f, 0.2f, 0.1f, "EXIT");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // matrisler
        glm::mat4 model = glm::mat4(1.0f);

        float verticalMovement = sin((float)glfwGetTime()) * .2f;
        model = glm::translate(model, glm::vec3(1.0f, verticalMovement, 0.0f));


        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); //rotate

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        
        //ucgen icin
        glm::mat4 triangleModel = glm::mat4(1.0f);

        triangleModel = glm::translate(triangleModel, glm::vec3(-1.0f, verticalMovement, 0.0f));
        triangleModel = glm::rotate(triangleModel, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); //rotate


        shader.setMat4("model", triangleModel);
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 18);


        exitButton.update(window);
        exitButton.draw();

        if (exitButton.wasClicked()) {
            glfwSetWindowShouldClose(window, true);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
