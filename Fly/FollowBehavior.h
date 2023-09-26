#pragma once
#include "ThinkThing.h"

class FollowBehavior : public ThinkThing
{
public:
	FollowBehavior() = default;
	~FollowBehavior() = default;

	void think(long timeDeltaMsec, long long timeAbsoluteMsec) override;
};
