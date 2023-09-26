#pragma once
#include "logic/ThinkThing.h"
#include <objects/Object.h>
#include <behaviors/BehaviorTarget.h>

class GoToRandomPointBehavior : public ThinkThing
{
public:
	GoToRandomPointBehavior() = default;
	~GoToRandomPointBehavior() = default;

	void think(long timeDeltaMsec, long long timeAbsoluteMsec) override;
	void setBehaviorTarget(BehaviorTarget* target) { behaviorTarget = target; }

private:
	BehaviorTarget* behaviorTarget = nullptr;
	glm::vec2 fieldSize = glm::vec2(20, 20);
	long long lastTick = 0;
	long timeBetweenDirectionChanges = 10000;
};
