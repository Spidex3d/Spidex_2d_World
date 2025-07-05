#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
public:
    glm::vec2 Position = glm::vec2(0.0f);
    float Zoom = 1.0f;

    float ViewWidth = 800.0f;
    float ViewHeight = 600.0f;

    Camera2D(float width, float height)
        : ViewWidth(width), ViewHeight(height) {
    }

    void Resize(float width, float height) {
        ViewWidth = width;
        ViewHeight = height;
    }

    glm::mat4 GetViewMatrix() const {
        return glm::translate(glm::mat4(1.0f), glm::vec3(-Position, 0.0f));
    }
    /*glm::mat4 GetProjectionMatrix() const {
        return glm::ortho(
            0.0f,
            ViewWidth / Zoom,
            ViewHeight / Zoom,
            0.0f,
            -1.0f,
            1.0f
        );
    }*/
    glm::mat4 GetProjectionMatrix() const {
        return glm::ortho(0.0f, ViewWidth / Zoom, ViewHeight / Zoom, 0.0f, -1.0f, 1.0f);
    }
    

    /*glm::mat4 GetProjectionMatrix() const {
        float halfW = ViewWidth * 0.5f / Zoom;
        float halfH = ViewHeight * 0.5f / Zoom;
        return glm::ortho(-halfW, halfW, -halfH, halfH, -1.0f, 1.0f);
    }*/

    void Move(const glm::vec2& delta) {
        Position += delta;
    }

    void ZoomIn(float amount) {
        Zoom += amount;
        if (Zoom < 0.1f) Zoom = 0.1f;
        if (Zoom > 10.0f) Zoom = 10.0f;
    }

    void HandleKeyboard(float deltaTime, bool up, bool down, bool left, bool right) {
        float speed = 500.0f * deltaTime / Zoom;

        if (up)    Position.y += speed;
        if (down)  Position.y -= speed;
        if (left)  Position.x -= speed;
        if (right) Position.x += speed;
    }

    void HandleMouseScroll(float yoffset) {
        float zoomSpeed = 0.1f;
        Zoom += yoffset * zoomSpeed;
        if (Zoom < 0.1f) Zoom = 0.1f;
        if (Zoom > 10.0f) Zoom = 10.0f;
    }
};

