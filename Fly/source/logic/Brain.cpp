#include "logic/Brain.h"
#include <chrono>
#include <iostream>

using namespace std::chrono;

Brain::Brain()
{
	thread = new std::thread(&Brain::Think, this);
}

Brain::~Brain()
{
	isRunning = false;
	thread->join();
	delete mutex;
}

void Brain::Think()
{
	while (isRunning)
	{
		long long milliseconds = getMilliseconds();
		std::lock_guard<std::mutex> lock(*mutex);
		for (ThinkThing* thing : thinkThings)
		{
			thing->think(milliseconds - lastTime, milliseconds);
		}

		lastTime = milliseconds;
	}
}

void Brain::addThinkThing(ThinkThing* thinkThing)
{
	std::lock_guard<std::mutex> lock(*mutex);
	thinkThings.push_back(thinkThing);
}

long long  Brain::getMilliseconds() {
	std::chrono::milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	return ms.count();
}