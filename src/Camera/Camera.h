#pragma once

#include <glm/glm.hpp>

#include "../Transform.h"

class Camera {
public:
    Camera(glm::vec3 pos, glm::vec3 rotation);

private:
    glm::vec4 m_pos;
    glm::vec4 m_up;
};

