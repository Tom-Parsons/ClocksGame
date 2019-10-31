#pragma once

class Score {
public:
	void initialise();
	int getAmount() const;
	void updateAmount(int);
private:
	int amount;
};
