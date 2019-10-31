#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator() {
	seed();	//reset the random number generator from current system time
}
void RandomNumberGenerator::seed() {
	// Seed with GetTickCount() as this updates a lot more frequently than time(0) does meaning the random numbers are more likely to be different quicker
	srand(static_cast<unsigned int>(GetTickCount()));
}
int RandomNumberGenerator::getRandomValue(int max) {
	return (rand() % max) + 1; //produce a random number in range [1..max]
}