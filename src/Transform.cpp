#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>

#include "Vulkan/Buffer.h"
#include "Vulkan/Buffer.h"

Transform::Transform()
    : m_position{},
    m_rotation{},
    m_size{}
{
}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : m_position(position),
    m_rotation(rotation),
    m_size(scale)
{
}

void Transform::Translate(glm::vec3 vector)
{
    m_position += vector;
}

void Transform::Rotate(glm::vec3 vector)
{
    m_rotation += vector;
    for (int i = 0; i < 3; i++)
        if (vector[i] > 2.f)
            vector[i] -= 2.f;
}

void Transform::Scale(glm::vec3 vector)
{
    m_size += vector;
}

glm::vec3 Transform::GetPosition() const { return m_position; }
glm::vec3 Transform::GetRotation() const { return m_rotation; }
glm::vec3 Transform::GetSize() const { return m_size; }
glm::mat4 Transform::GetModel() { return translate(rotateEuler(scale(glm::mat4(1.0f), m_size), m_rotation), m_position); }

glm::mat4 Transform::translate(glm::mat4& model, const glm::vec3& vector)
{
    model[3][0] += vector.x;
    model[3][1] += vector.y;
    model[3][2] += vector.z;
    return model;
}

glm::mat4 Transform::translate(glm::mat4&& model, const glm::vec3& vector)
{
    model[3][0] += vector.x;
    model[3][1] += vector.y;
    model[3][2] += vector.z;
    return model;
}

glm::mat4 Transform::rotateEuler(glm::mat4& model, const glm::vec3& vector)
{
    const float x = vector.x, y = vector.y, z = vector.z;
    const glm::mat4 rotationMatrix = {
        { cos(y) * cos(z),
          sin(x) * sin(y) * cos(z) + cos(x) * sin(z),
         -cos(x) * sin(y) * cos(z) + sin(x) * sin(z),
          0.0f },

        { -cos(y) * sin(z),
          -sin(x) * sin(y) * sin(z) + cos(x) * cos(z),
           cos(x) * sin(y) * sin(z) + sin(x) * cos(z),
           0.0f },

        { sin(y),
         -sin(x) * cos(y),
          cos(x) * cos(y),
          0.0f },

        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    model *= rotationMatrix;
    return model * rotationMatrix;
}

glm::mat4 Transform::rotateEuler(glm::mat4&& model, const glm::vec3& vector)
{
    const float x = vector.x, y = vector.y, z = vector.z;
    const glm::mat4 rotationMatrix = {
        { cos(y) * cos(z),
          sin(x) * sin(y) * cos(z) + cos(x) * sin(z),
         -cos(x) * sin(y) * cos(z) + sin(x) * sin(z),
          0.0f },

        { -cos(y) * sin(z),
          -sin(x) * sin(y) * sin(z) + cos(x) * cos(z),
           cos(x) * sin(y) * sin(z) + sin(x) * cos(z),
           0.0f },

        { sin(y),
         -sin(x) * cos(y),
          cos(x) * cos(y),
          0.0f },

        { 0.0f, 0.0f, 0.0f, 1.0f }
    };

    model *= rotationMatrix;
    return model * rotationMatrix;
}

glm::mat4 Transform::scale(glm::mat4& model, const glm::vec3& vector)
{
    model[0][0] += vector.x;
    model[1][1] += vector.y;
    model[2][2] += vector.z;
    return model;
}

glm::mat4 Transform::scale(glm::mat4&& model, const glm::vec3& vector)
{
    model[0][0] += vector.x;
    model[1][1] += vector.y;
    model[2][2] += vector.z;
    return model;
}
