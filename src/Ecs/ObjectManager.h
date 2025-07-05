#pragma once
#include <glm\glm.hpp>
#include "../Shader/Shader.h"
#include "BaseModel.h"
#include "../Headers/GlobalVars.h"

class Sprite : public BaseModel {

public:
    GLuint VAO, VBO, EBO;

    Sprite(int idx, const std::string& name, int SpriteIdx) {
        index = idx;
        objectName = name;
        objectIndex = SpriteIdx;
        objectTypeID = PLAYER_SPRITE;

        float vertices[] = {
             0.5f,  0.5f, 1.0f, 1.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };
        //float vertices[] = {
        //    //                   Text coords
        //     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
        //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        //    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        //    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
        //};
        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
         // Vertex positions
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture coordinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Sprite() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void DrawSprite() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // using indices
        glBindVertexArray(0);
        glUseProgram(0);
    }

private:
    
};







