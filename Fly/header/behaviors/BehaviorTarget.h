#pragma once
#include <glm/fwd.hpp>

class BehaviorTarget
{
public:
	BehaviorTarget() = default;
	virtual ~BehaviorTarget() = default;

	virtual void setDestination(glm::vec3 destination) = 0;
};