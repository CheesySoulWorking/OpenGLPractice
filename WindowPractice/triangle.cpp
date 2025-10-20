#include"triangle.h"
#include"shader.h"
#include "matrix4.h"

OpenGLResources InitTriangle(const char* vertexShaderSource, const char* fragmentShaderSource) {

    OpenGLResources glr;

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

    float normals[] = {
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
    };

    glr.worldMatrix = Matrix4();

    // Start prepping vertices and buffers for GPU
    glGenVertexArrays(1, &glr.VAO);
    glGenBuffers(1, &glr.VBO);
    glGenBuffers(1, &glr.VBOColors);
    glGenBuffers(1, &glr.VBONormals);

    glBindVertexArray(glr.VAO);

    // Position
    glBindBuffer(GL_ARRAY_BUFFER, glr.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colors
    glBindBuffer(GL_ARRAY_BUFFER, glr.VBOColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    // Normals (COMMENT OUT WHEN NOT USING PHONG)
    glBindBuffer(GL_ARRAY_BUFFER, glr.VBONormals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    Shader shader(vertexShaderSource, fragmentShaderSource);
    glr.shaderProgram = shader.ID;

    return glr;
}

Matrix4 OpenGLResources::getWorldMatrix() {
    return this->worldMatrix.clone();
}

void DrawTriangle(const OpenGLResources &glr, HDC hdc, Camera &camera, Matrix4 &projectionMatrix, float &time)
{
    // Necessary for all shaders ================================
    Matrix4 model = glr.worldMatrix;
    GLuint modelLoc = glGetUniformLocation(glr.shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(glr.shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(glr.shaderProgram, "projection");
    
    glUseProgram(glr.shaderProgram);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.clone().transpose().elements);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, camera.getViewMatrix().clone().transpose().elements);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projectionMatrix.clone().transpose().elements);

    // Specific to rainbow shader ================================
    GLuint uTime = glGetUniformLocation(glr.shaderProgram, "uTime");
    glUniform1f(uTime, time);

    // Specific to phong shader ==================================
    Vector4 cameraPosition = camera.getPosition();
    Vector3 lightDir = Vector3(0, 0, 3).normalize();

    GLuint cameraPos = glGetUniformLocation(glr.shaderProgram, "uCameraPosition");
    GLuint lightDirection = glGetUniformLocation(glr.shaderProgram, "uLightDirection");
    
    glUniform3f(cameraPos, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(lightDirection, lightDir.x, lightDir.y, lightDir.z);

    // Draw the triangle =========================================
    glBindVertexArray(glr.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}