#pragma once

#include <string>
#include <ctime>

#include "RandomNumberGenerator.h"

class Time {
public:
	Time();
	Time(int, int, int);
	Time(std::string);
	Time(const Time&, bool copy); // If it isn't copy, then make sure that the new time isn't equal to the one passed in
	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;
	std::string toString() const;
	void setTime(int, int, int);
	void addSecond();
	int getSecondHandAngle();
	int getMinuteHandAngle();
	int getHourHandAngle();
	static int getCurrentHours();
	static int getCurrentMinutes();
	static int getCurrentSeconds();
private:
	int hours, minutes, seconds;
};
