#include "Camera.h"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera(Transform&& transform)
    : m_transform(transform),
    m_near(0.1f),
    m_far(10.f),
    m_fovx(90.f),
    m_aspectRatio(16.f/9.f)
{
}

glm::mat4 Camera::GetPerspectiveProjection() const
{
    const float sx = 1.0f / std::tan(m_fovx * 0.5f);
    const float sy = sx * m_aspectRatio;

    glm::mat4 P(0.0f);
    P[0][0] = sx;
    P[1][1] = -sy;
    P[2][2] = -m_far / (m_far - m_near);
    P[2][3] = -1.0f;
    P[3][2] = -(m_far * m_near) / (m_far - m_near);

    return P;
}

glm::mat4 Camera::GetOrthographicProjection(const float halfWidth, const float halfHeight) const
{
    const float left = -halfWidth, bottom = halfHeight;
    const float right = halfWidth, top = -halfHeight;

    glm::mat4 projection(0.f);
    projection[0][0] = 2.f/(right - left);
    projection[1][1] = 2.f/(top - bottom);
    projection[2][2] = -2.f/(m_far - m_near);
    projection[3] = {-(right+left)/(right-left), -(top+bottom)/(top-bottom), -(m_far + m_near)/(m_far-m_near), 1};

    return projection;
}

glm::mat4 Camera::GetView() const { return glm::inverse(m_transform.GetModel()); }
Transform Camera::GetTransform() const { return m_transform; }

void Camera::LookAt(const glm::vec3& point)
{
    glm::vec3 dir = point - m_transform.GetPosition();
    float len     = glm::length(dir);
    if (len < 1e-4f)
        return;

    dir /= len;
    glm::vec3 up(0.f, 1.f, 0.f);
    if (glm::abs(glm::dot(dir, up)) > 0.999f)
        up = glm::vec3(1.f, 0.f, 0.f);

    glm::quat q = glm::quatLookAt(dir, up);
    m_transform.SetRotation(q);
}
