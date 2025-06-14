#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

Camera::Camera(Transform&& transform)
    : m_transform(transform),
    m_near(0.1f),
    m_far(10.f),
    m_fovx(90.f),
    m_aspectRatio(16.f/9.f)
{
}

glm::mat4 Camera::GetPerspectiveProjection()
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

glm::mat4 Camera::GetOrthographicProjection(float halfWidth, float halfHeight)
{
    float left = -halfWidth, bottom = halfHeight;
    float right = halfWidth, top = -halfHeight;

    glm::mat4 projection = {
        {2.f/(right - left), 0, 0, 0},
        {0, 2.f/(top - bottom), 0, 0},
        {0, 0, -2.f/(m_far - m_near), 0},
        {-(right+left)/(right-left), -(top+bottom)/(top-bottom), -(m_far + m_near)/(m_far-m_near), 1},
    };

    return projection;
}

Transform Camera::GetTransform()
{
    return m_transform;
}
