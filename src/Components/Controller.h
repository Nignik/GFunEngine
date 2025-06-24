#pragma once

#include <glm/glm.hpp>

struct Controller
{
	glm::vec3 direction{};
	float speed = 10.f;
	float prevMouseX = 0.f, prevMouseY = 0.f;
	float dx = 0.f, dy = 0.f;
	bool active = false;
};
