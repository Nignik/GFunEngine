#pragma once
#include <glm/glm.hpp>

class Transform 
{
public:
    Transform();
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

    void Translate(glm::vec3 vector);
    void Rotate(glm::vec3 vector);
    void Scale(glm::vec3 vector);

    glm::mat4 GetModel();

public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

private:
    glm::mat4 rotateEuler(glm::mat4& model);
};
