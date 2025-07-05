#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "Shader.h"

class ShaderManager {
public:
    static void SetupShaders();
    static Shader* SpriteShader; // Declare the shader as a static member
    
};
