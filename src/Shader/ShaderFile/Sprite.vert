#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main() {
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
}