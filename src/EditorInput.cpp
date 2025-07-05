#include "Headers\EditorInput.h"
#include "Headers\Config.h"
#include "Camera\Camera2D.h"  // <-- your 2D camera header

Camera2D camera(SCR_WIDTH, SCR_HEIGHT);  //  Replace old 3D vec3 constructor
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool dragging = false;  // for mouse drag-to-pan

// Update this each frame
void updateDeltaTime() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

// GLFW input handling
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // WASD for movement
    camera.HandleKeyboard(
        deltaTime,
        glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS,
        glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS,
        glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS,
        glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
    );

    // Optional: Zoom in/out via keyboard too
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ZoomIn(0.05f);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ZoomIn(-0.05f);

    // Optional: Window opacity shortcut
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        glfwSetWindowOpacity(window, 0.5f);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        glfwSetWindowOpacity(window, 1.0f);
}

// Mouse drag to pan the camera
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = ypos - lastY;

    lastX = xpos;
    lastY = ypos;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS ||
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        camera.Move(glm::vec2(-xoffset, yoffset) / camera.Zoom);
    }
}

// Scroll to zoom
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.HandleMouseScroll(static_cast<float>(yoffset));
}



//#include "Headers\EditorInput.h"
//#include "Headers\Config.h"
//
//Camera2D camera(glm::vec3(0.0f, 0.0f, 5.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//bool mouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//float fov = 45.0f;
//
////void processInput(GLFWwindow* window, Camera& camera) // this changed
//void processInput(GLFWwindow* window) // this changed
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    // UP - Down
//    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
//        camera.ProcessKeyboard(UP, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
//        camera.ProcessKeyboard(UP, -deltaTime);
//
//    // change widows Opacity 
//    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
//        glfwSetWindowOpacity(window, 0.5f);
//
//    // change widows Opacity back to normat
//    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//        glfwSetWindowOpacity(window, 1.0f);
//
//}
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//
//    if (mouse == true) {
//
//        float xpos = static_cast<float>(xposIn);
//        float ypos = static_cast<float>(yposIn);
//
//        if (firstMouse)
//        {
//            lastX = xpos;
//            lastY = ypos;
//            firstMouse = false;
//        }
//
//        float xoffset = xpos - lastX;
//        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//        lastX = xpos;
//        lastY = ypos;
//
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_TRUE)
//            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//            camera.ProcessMouseMovement(xoffset, yoffset);
//    }
//}
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}


