#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
// here would be a vec2 texture coordinate

out vec3 vertexWorldNormal;
out vec3 vertexWorldPosition;
// here would be where we send the texture coordinate to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexWorldNormal = (model * vec4(aNormal, 0.0)).xyz;
    vertexWorldPosition = (model * vec4(aPos, 1.0)).xyz;
}