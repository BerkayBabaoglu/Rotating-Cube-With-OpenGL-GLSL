#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

class Button {
public:
    float x, y, width, height;
    bool isPressed;
    std::string text;
    
    Button(float x, float y, float w, float h, std::string text);
    bool isMouseOver(float mouseX, float mouseY);
    void draw();
    void update(GLFWwindow* window);
    bool wasClicked();
};