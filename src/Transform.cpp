#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>

#include "Vulkan/Buffer.h"
#include "Vulkan/Buffer.h"

Transform::Transform()
    : position{},
    rotation{},
    scale{}
{
}

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : position(position),
    rotation(rotation),
    scale(scale)
{
}

void Transform::Translate(glm::vec3 vector)
{
    position += vector;
}

void Transform::Rotate(glm::vec3 vector)
{
    rotation += vector;
}

void Transform::Scale(glm::vec3 vector)
{
    scale += vector;
}

glm::mat4 Transform::GetModel()
{
    glm::mat4 model(1.f);
    return glm::translate(glm::scale(rotateEuler(model), scale), position);
}

glm::mat4 Transform::rotateEuler(glm::mat4& model)
{
    float x = rotation.x, y = rotation.y, z = rotation.z;
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
    return model;
}
