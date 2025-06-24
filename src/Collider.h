#pragma once

struct SphereCollider
{
	SphereCollider(const float radius, const bool isTrigger = false)
		: radius{radius},
		isTrigger{isTrigger}
	{
	}

	float radius;
	bool isTrigger;
};


