#pragma once
#include <behaviors/BehaviorTarget.h>
#include <glm/glm.hpp>

class BehaviorTargetMock : public BehaviorTarget
{
public:
	BehaviorTargetMock() = default;
	~BehaviorTargetMock() = default;

	void setDestination(glm::vec3 destination) override { this->destination = destination; };
	glm::vec3 getDestination() { return destination; }

private:
	glm::vec3 destination = glm::vec3(0, 0, 0);
};