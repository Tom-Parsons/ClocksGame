#include "Time.h"



Time::Time() {
	RandomNumberGenerator rng;
	hours = rng.getRandomValue(23);
	minutes = rng.getRandomValue(59);
	seconds = getCurrentSeconds();
}
Time::Time(std::string string) {
	hours = std::stoi(string.substr(0, 2));
	minutes = std::stoi(string.substr(3, 2));
	seconds = std::stoi(string.substr(6, 2));
}
Time::Time(int h, int m, int s) {
	hours = h;
	minutes = m;
	seconds = s;
}
Time::Time(const Time &time, bool copy) {
	if (copy) {
		hours = time.getHours();
		minutes = time.getMinutes();
		seconds = time.getSeconds();
	}
	else {
		RandomNumberGenerator rng;
		hours = rng.getRandomValue(23);
		minutes = rng.getRandomValue(59);
		seconds = getCurrentSeconds();
		while (hours == time.getHours() && minutes == time.getMinutes()) {
			hours = rng.getRandomValue(23);
			minutes = rng.getRandomValue(59);
		}
	}
}
int Time::getHours() const {
	return hours;
}
int Time::getMinutes() const {
	return minutes;
}
int Time::getSeconds() const {
	return seconds;
}
std::string Time::toString() const {
	return std::to_string(hours) + ":" + std::string(2 - std::to_string(minutes).length(), '0') + std::to_string(minutes) + ":" + std::string(2 - std::to_string(seconds).length(), '0') + std::to_string(seconds);
}
void Time::setTime(int h, int m, int s) {
	hours = h;
	minutes = m;
	seconds = s;
}
void Time::addSecond() {
	seconds++;
	if (seconds >= 60) {
		seconds = 0;
		minutes++;
	}
	if (minutes >= 60) {
		minutes = 0;
		hours++;
	}
	if (hours >= 24) {
		hours = 0;
	}
}
int Time::getSecondHandAngle() {
	return (seconds / 60.0f) * 360.0f;
}
int Time::getMinuteHandAngle() {
	return (minutes / 60.0f) * 360.0f;
}
int Time::getHourHandAngle() {
	int tempHours = hours;
	if (tempHours >= 12)
		tempHours -= 12;
	return ((minutes + (60 * tempHours)) / 720.0f) * 360.0f;
}

int Time::getCurrentHours() {
	time_t now = time(0);
	struct tm& t = *localtime(&now);
	return t.tm_hour;
}
int Time::getCurrentMinutes() {
	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	return t.tm_min;
}
int Time::getCurrentSeconds() {
	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	return t.tm_sec;
}