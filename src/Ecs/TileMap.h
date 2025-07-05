#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "BaseModel.h"
#include "../Headers/config.h"
#include "../Headers/GlobalVars.h"
#include "../Shader/Shader.h"

static GLuint quadVAO = 0;
static GLuint quadVBO = 0;

class TileMap : public BaseModel {
public:
GLuint tileTexture;

    TileMap(int idx, const std::string& name, int MapIdx) {
        index = idx;
        objectName = name;
        objectIndex = MapIdx;
        objectTypeID = MAP_IDX;

        // Setup quad once
        if (quadVAO == 0) {
            float vertices[] = {
                // positions   // texCoords
                0.0f, 1.0f,    0.0f, 1.0f,
                1.0f, 1.0f,    1.0f, 1.0f,
                1.0f, 0.0f,    1.0f, 0.0f,
                0.0f, 0.0f,    0.0f, 0.0f
            };
            unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

            glGenVertexArrays(1, &quadVAO);
            glBindVertexArray(quadVAO);

            glGenBuffers(1, &quadVBO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            GLuint EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
    }

    ~TileMap() {

    }

    /*void LoadExampleMap() {
        mapData = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };
    }*/

    void LoadExampleMap() {
        mapData = {
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,},
        {1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
        };
    }

    void DrawMap(Shader& shader) {
        ShaderManager::SpriteShader->setInt("spriteTexture", 0);

        glBindTexture(GL_TEXTURE_2D, tileTexture);
        glBindVertexArray(quadVAO);

        float mapOffsetY = SCR_HEIGHT - (rows * tileSize + SetMapBaseHeight); // push down or up

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (mapData[y][x] == 1) {
                    glm::vec2 pos = glm::vec2(
                        x * tileSize,
                        y * tileSize + mapOffsetY
                    );

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(pos, 0.0f));
                    model = glm::scale(model, glm::vec3(tileSize, tileSize, 1.0f));

                    ShaderManager::SpriteShader->setMat4("model", model);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                }
            }
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
private:

    int rows = 10;
    //int cols = 16;
    int cols = 31;
    float tileSize = 32.0f; // pixels
    std::vector<std::vector<int>> mapData;
    

};
