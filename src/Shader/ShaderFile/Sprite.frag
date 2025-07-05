#version 460
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D spriteTexture;

void main()
{
    FragColor = texture(spriteTexture, TexCoord);
}