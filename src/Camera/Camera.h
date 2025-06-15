#pragma once

#include <glm/glm.hpp>

#include "../Transform.h"

class Camera {
public:
    Camera(Transform&& transform);

    glm::mat4 GetPerspectiveProjection() const;
    glm::mat4 GetOrthographicProjection(float halfWidth, float halfHeight) const;
    glm::mat4 GetView() const;
    Transform GetTransform() const;

    void LookAt(const glm::vec3& point);

private:
    Transform m_transform;
    float m_near;
    float m_far;
    float m_fovx;
    float m_aspectRatio;
};