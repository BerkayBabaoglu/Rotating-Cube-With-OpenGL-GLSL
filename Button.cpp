#include "Button.h"
#include <iostream>

Button::Button(float x, float y, float w, float h, std::string text) 
    : x(x), y(y), width(w), height(h), text(text), isPressed(false) {}

bool Button::isMouseOver(float mouseX, float mouseY) {
    return (mouseX >= x && mouseX <= x + width && 
            mouseY >= y && mouseY <= y + height);
}

void Button::draw() {

    glUseProgram(0);
    

    glDisable(GL_DEPTH_TEST);
    

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    

    glBegin(GL_QUADS);
    if (isPressed) {
        glColor3f(0.8f, 0.2f, 0.2f); // Kırmızı (basılı)
    } else {
        glColor3f(0.2f, 0.8f, 0.2f); // Yeşil (normal)
    }
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
    

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

void Button::update(GLFWwindow* window) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float glMouseX = (mouseX / width) * 2.0f - 1.0f;
    float glMouseY = 1.0f - (mouseY / height) * 2.0f;
    
    if (isMouseOver(glMouseX, glMouseY)) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            isPressed = true;
        } else {
            isPressed = false;
        }
    } else {
        isPressed = false;
    }
}

bool Button::wasClicked() {
    return isPressed;
}