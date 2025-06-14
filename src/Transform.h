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

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetSize() const;
    glm::mat4 GetModel();

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_size;

private:
    glm::mat4 translate(glm::mat4& model, const glm::vec3& vector);
    glm::mat4 translate(glm::mat4&& model, const glm::vec3& vector);
    glm::mat4 rotateEuler(glm::mat4& model, const glm::vec3& vector);
    glm::mat4 rotateEuler(glm::mat4&& model, const glm::vec3& vector);
    glm::mat4 scale(glm::mat4& model, const glm::vec3& vector);
    glm::mat4 scale(glm::mat4&& model, const glm::vec3& vector);
};
