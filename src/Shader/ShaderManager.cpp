#include "ShaderManager.h"
#include <iostream>


// Define the static member
Shader * ShaderManager::SpriteShader = nullptr; // the grid shader


glm::vec3 lightPos(1.2f, 1.5f, 2.0f);

extern glm::vec3 amb_light;
extern float deltaTime;
extern float angel;

void ShaderManager::SetupShaders() {
    // Initialize the shader
    SpriteShader = new Shader("src/Shader/ShaderFile/Sprite.vert", "src/Shader/ShaderFile/Sprite.frag");

}


