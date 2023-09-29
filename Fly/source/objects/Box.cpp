#include "objects/Box.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Box::Box(glm::vec3 position, glm::vec3 direction) : Object(position, direction)
{
    float vertices[] = {
        // Front
        -1.0f, -1.0f, 1.0f, 0, 0, 1,
         1.0f, -1.0f, 1.0f, 0, 0, 1,
         1.0f,  1.0f, 1.0f, 0, 0, 1,
        -1.0f,  1.0f, 1.0f, 0, 0, 1,

        // Right
         1.0f, -1.0f,  1.0f, 1, 0, 0,
         1.0f, -1.0f, -1.0f, 1, 0, 0,
         1.0f,  1.0f, -1.0f, 1, 0, 0,
         1.0f,  1.0f,  1.0f, 1, 0, 0,

        // Back
        1.0f, -1.0f, -1.0f, 0,0, -1.0f,
        -1.0f, -1.0f, -1.0f, 0, 0, -1.0f,
        -1.0f, 1.0f, -1.0f, 0, 0, -1.0f,
        1.0f, 1.0f, -1.0f, 0, 0, -1.0f,

        // Left
        -1.0f, -1.0f, -1.0f, -1.0f, 0, 0,
        -1.0f, -1.0f, 1.0f, -1.0f, 0, 0,
        -1.0f, 1.0f, 1.0f, -1.0f, 0, 0,
        -1.0f, 1.0f, -1.0f, -1.0f, 0, 0,

        // Top
        -1.0f, 1.0f, 1.0f, 0, 1, 0,
        1.0f, 1.0f, 1.0f, 0, 1, 0,
        1.0f, 1.0f, -1.0f, 0, 1, 0,
        -1.0f, 1.0f, -1.0f, 0, 1, 0,

        // Bottom
        1.0f, -1.0f, -1.0f, 0, -1, 0,
        -1.0f, -1.0f, -1.0f, 0, -1, 0,
        -1.0f, -1.0f, 1.0f, 0, -1, 0,
        1.0f, -1.0f, 1.0f, 0, -1, 0
    };

    unsigned int indices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Right
        4,5,6,
        6,7,4,

        // Back
        8, 9, 10,
        10, 11, 8,

        // Left
        //14, 13, 12,
        //12, 15, 14,
        12,13,14,
        14,15,12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21,22,
        22,23,20
    };

    nrTriangles = sizeof(vertices) / sizeof(vertices[0]);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    shader = new Shader("shaders/normalShader.vs", "shaders/basicLightingShader.fs");
}

Box::~Box()
{
    delete shader;
    shader = nullptr;
}

void Box::render(
    float time,
    glm::mat4& viewMatrix,
    glm::mat4& projectionMatrix,
    Camera& camera,
    glm::vec3 lightPos,
    glm::vec3 lightColor)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    shader->use();
    shader->setMatrix("model", model);
    shader->setMatrix("view", viewMatrix);
    shader->setMatrix("projection", projectionMatrix);
    shader->setVec3("lightColor", lightColor);
    shader->setVec3("lightPos", lightPos);
    shader->setVec3("viewPos", camera.getPosition());
    shader->setVec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));

    // Rendering
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glDrawElements(GL_TRIANGLES, nrTriangles, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}