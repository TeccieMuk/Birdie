#pragma once
#include "ThinkThing.h"
#include <vector>
#include <thread>
#include <mutex>

class Brain
{
public:
	Brain();
	~Brain();

	void addThinkThing(ThinkThing* thinkThing);

private:
	void Think();
	long long getMilliseconds();

	long long lastTime = 0;
	bool isRunning = true;
	std::thread* thread = nullptr;
	std::vector<ThinkThing*> thinkThings = std::vector<ThinkThing*>();
	std::mutex* mutex = new std::mutex();

private:
	Brain(const Brain&) = delete;
};