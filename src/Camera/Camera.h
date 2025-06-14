#pragma once

#include <glm/glm.hpp>

#include "../Transform.h"

class Camera {
public:
    Camera(Transform&& transform);

    glm::mat4 GetPerspectiveProjection();
    glm::mat4 GetOrthographicProjection(float halfWidth, float halfHeight);
    Transform GetTransform();

private:
    Transform m_transform;
    float m_near;
    float m_far;
    float m_fovx;
    float m_aspectRatio;
};