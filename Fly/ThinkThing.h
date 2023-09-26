#pragma once

class ThinkThing {
public:
	virtual void think(long timeDeltaMsec, long long timeAbsoluteMsec) = 0;
};
