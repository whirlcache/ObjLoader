#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D outTexture;

void main() {
  FragColor = texture(outTexture, TexCoords);
}