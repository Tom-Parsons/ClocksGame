#pragma once

#include <Windows.h>

class RandomNumberGenerator
{
public:
	RandomNumberGenerator();
	int getRandomValue(int);
private:
	void seed();
};