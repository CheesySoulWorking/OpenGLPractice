#include"grid.h"
#include"shader.h"
#include "matrix4.h"

const int size = 8;
const int numVertices = (size * 2 + 1) * 4;

OpenGLResourcesGrid InitGrid() {

    OpenGLResourcesGrid glr;
    float vertices[numVertices * 3]; 
    int index = 0;

    // Lines parallel to Z axis
    for (int i = -size; i <= size; ++i) {
        vertices[index++] = (float)i;
        vertices[index++] = -1.0f;
        vertices[index++] = (float)-size;

        vertices[index++] = (float)i;
        vertices[index++] = -1.0f;
        vertices[index++] = (float)size;
    }

    // Lines parallel to X axis
    for (int i = -size; i <= size; ++i) {
        vertices[index++] = (float)-size;
        vertices[index++] = -1.0f;
        vertices[index++] = (float)i;

        vertices[index++] = (float)size;
        vertices[index++] = -1.0f;
        vertices[index++] = (float)i;
    }

    glr.worldMatrix = Matrix4();

    // Start prepping vertices and buffers for GPU
    glGenVertexArrays(1, &glr.VAO);
    glGenBuffers(1, &glr.VBO);

    glBindVertexArray(glr.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, glr.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // TODO: EVENTUALLY USE GLSL FILES FOR THE SHADERS
    // gl_Position = projection * view * modle * vec4(aPos, 1.0);
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(0.2, 0.3, 0.7, 1.0);
        }
    )";

    Shader shader(vertexShaderSource, fragmentShaderSource);
    glr.shaderProgram = shader.ID;

    return glr;
}

Matrix4 OpenGLResourcesGrid::getWorldMatrix() {
    return this->worldMatrix.clone();
}

void DrawGrid(const OpenGLResourcesGrid& glr, HDC hdc, Camera& camera, Matrix4& projectionMatrix)
{
    Matrix4 model = glr.worldMatrix;
    GLuint modelLoc = glGetUniformLocation(glr.shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(glr.shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(glr.shaderProgram, "projection");

    glUseProgram(glr.shaderProgram);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.clone().transpose().elements);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, camera.getViewMatrix().clone().transpose().elements);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projectionMatrix.clone().transpose().elements);

    glBindVertexArray(glr.VAO);
    glDrawArrays(GL_LINES, 0, numVertices);
}