#include "Score.h"

void Score::initialise() {
	amount = 0;
}
int Score::getAmount() const {
	return amount;
}
//increment when value>0, decrement otherwise
void Score::updateAmount(int value) {
	amount += value;
}