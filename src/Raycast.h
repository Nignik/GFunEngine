#pragma once

struct RayHit
{
    Hori::Entity e;
    glm::vec3 pos;
    float dist;
};

struct RayData {
    glm::vec3 origin;
    glm::vec3 dir;
    RayHit hit;
    bool active;
};


