#pragma once
#include "logic/ThinkThing.h"
#include <objects/Object.h>
#include <behaviors/BehaviorTarget.h>

class FollowBehavior : public ThinkThing
{
public:
	FollowBehavior() = default;
	~FollowBehavior() = default;

	void think(long timeDeltaMsec, long long timeAbsoluteMsec) override;
	void setFollowTarget(Object* object) { followTarget = object; }
	void setBehaviorTarget(BehaviorTarget* target) { behaviorTarget = target; }
	void setOffset(glm::vec3 offset) { offset = offset; }

private:
	Object* followTarget = nullptr;
	BehaviorTarget* behaviorTarget = nullptr;
	glm::vec3 offset = glm::vec3(5, 0, 5);
};
