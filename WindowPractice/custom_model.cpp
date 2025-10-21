#include "custom_model.h"
#include "shader.h"
#include "matrix4.h"

int positionSize = 0;
int normalSize = 0;

OpenGLModel InitModel(Model& model, const char* vertexShaderSource, const char* fragmentShaderSource) {

    OpenGLModel glr;
    positionSize = model.positions.size();
    normalSize = model.normals.size();

    glr.worldMatrix = Matrix4();

    // Start prepping vertices and buffers for GPU
    glGenVertexArrays(1, &glr.VAO);
    glGenBuffers(1, &glr.VBO);
    glGenBuffers(1, &glr.VBOColors);
    glGenBuffers(1, &glr.VBONormals);

    glBindVertexArray(glr.VAO);

    // Position
    glBindBuffer(GL_ARRAY_BUFFER, glr.VBO);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(Vector3), model.positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normals (COMMENT OUT WHEN NOT USING PHONG)
    glBindBuffer(GL_ARRAY_BUFFER, glr.VBONormals);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(Vector3), model.normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    Shader shader(vertexShaderSource, fragmentShaderSource);
    glr.shaderProgram = shader.ID;

    return glr;
}

Matrix4 OpenGLModel::getWorldMatrix() {
    return this->worldMatrix.clone();
}

void DrawModel(const OpenGLModel& glr, HDC hdc, Camera& camera, Matrix4& projectionMatrix, float& time, Vector3& directionalLightDir, Vector3& positionalLightSrc)
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

    GLuint cameraPos = glGetUniformLocation(glr.shaderProgram, "uCameraPosition");
    GLuint lightDirection = glGetUniformLocation(glr.shaderProgram, "uLightDirection");
    GLuint lightPosition = glGetUniformLocation(glr.shaderProgram, "uLightPosition");

    glUniform3f(cameraPos, cameraPosition.x, cameraPosition.y, cameraPosition.z);
    glUniform3f(lightDirection, directionalLightDir.x, directionalLightDir.y, directionalLightDir.z);
    glUniform3f(lightPosition, positionalLightSrc.x, positionalLightSrc.y, positionalLightSrc.z);

    // Draw the triangle =========================================
    glBindVertexArray(glr.VAO);
    glDrawArrays(GL_TRIANGLES, 0, positionSize);
}