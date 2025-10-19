#include"triangle.h"
#include"shader.h"
#include "matrix4.h"

OpenGLResources InitTriangle() {

    OpenGLResources glr;

    /*float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0, 0.5f
    };*/

    float vertices[] = {
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0
    };

    float colors[] = {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0
    };

    glr.worldMatrix = Matrix4();

    // Start prepping vertices and buffers for GPU
    glGenVertexArrays(1, &glr.VAO);
    glGenBuffers(1, &glr.VBO);
    glGenBuffers(1, &glr.VBOColors);

    glBindVertexArray(glr.VAO);

    // Position
    glBindBuffer(GL_ARRAY_BUFFER, glr.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, glr.VBOColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
    
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;

        out vec3 vertexColor;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            vertexColor = aColor;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        // Normalize for safety
        in vec3 vertexColor;
        out vec4 FragColor;
        uniform float uTime;
           
        void main() {
            FragColor = vec4(
                abs(tan(uTime)) * vertexColor.x,
                abs(tan(uTime)) * vertexColor.y,
                abs(tan(uTime)) * vertexColor.z,
                1.0
            );
        }
    )";

    Shader shader(vertexShaderSource, fragmentShaderSource);
    glr.shaderProgram = shader.ID;

    return glr;
}

Matrix4 OpenGLResources::getWorldMatrix() {
    return this->worldMatrix.clone();
}

void DrawTriangle(const OpenGLResources &glr, HDC hdc, Camera &camera, Matrix4 &projectionMatrix, float &time)
{
    Matrix4 model = glr.worldMatrix;

    GLuint modelLoc = glGetUniformLocation(glr.shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(glr.shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(glr.shaderProgram, "projection");
    GLuint uTime = glGetUniformLocation(glr.shaderProgram, "uTime");

    glUseProgram(glr.shaderProgram);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.clone().transpose().elements);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, camera.getViewMatrix().clone().transpose().elements);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projectionMatrix.clone().transpose().elements);
    glUniform1f(uTime, time);

    glBindVertexArray(glr.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}