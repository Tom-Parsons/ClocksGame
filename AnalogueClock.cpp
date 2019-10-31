#include "AnalogueClock.h"

AnalogueClock::AnalogueClock() {
	setTime(Time());
	setImage();
	updateHandPositions();
}
AnalogueClock::AnalogueClock(Time t) {
	setTime(t);
	setImage();
	updateHandPositions();
}
Time AnalogueClock::getTime() {
	return time;
}
void AnalogueClock::setTime(Time t) {
	time = t;
	updateHandPositions();
}
void AnalogueClock::setImage() {
	if (!texture.loadFromFile("assets/clock_face.png")) {
		std::cout << "Error: could not load clock_face.png" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(0.5f, 0.5f);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	if (!hourHandTexture.loadFromFile("assets/clock_hands.png", sf::IntRect(5, 135, 80, 350))) {
		std::cout << "Error: could not load clock_hands.png" << std::endl;
	}
	if (!minuteHandTexture.loadFromFile("assets/clock_hands.png", sf::IntRect(90, 5, 65, 475))) {
		std::cout << "Error: could not load clock_hands.png" << std::endl;
	}

	hourHandSprite.setTexture(hourHandTexture);
	hourHandSprite.setScale(0.23f, 0.23f);
	hourHandSprite.setOrigin(hourHandSprite.getLocalBounds().width / 2, hourHandSprite.getLocalBounds().height - (hourHandSprite.getLocalBounds().height / 23.75f));

	minuteHandSprite.setTexture(minuteHandTexture);
	minuteHandSprite.setScale(0.23f, 0.23f);
	minuteHandSprite.setOrigin(minuteHandSprite.getLocalBounds().width / 2, minuteHandSprite.getLocalBounds().height - (minuteHandSprite.getLocalBounds().height / 23.75f));

	secondHandSprite.setTexture(minuteHandTexture);
	secondHandSprite.setScale(0.07f, 0.23f);
	secondHandSprite.setOrigin(secondHandSprite.getLocalBounds().width / 2, secondHandSprite.getLocalBounds().height - (secondHandSprite.getLocalBounds().height / 23.75f));

}
void AnalogueClock::setClockPosition(int position, sf::Font &font) {
	clockNumberText.setString(std::to_string(position));
	clockNumberText.setFont(font);
	clockNumberText.setCharacterSize(32);
	clockNumberText.setFillColor(sf::Color::White);
	float xPos;
	float yPos = Clock::SCREEN_HEIGHT - sprite.getGlobalBounds().height;
	switch (position) {
	case 1:
		xPos = (Clock::SCREEN_WIDTH / 2) - Clock::PIXELS_BETWEEN_CLOCKS - sprite.getGlobalBounds().width;
		break;
	case 2:
		xPos = Clock::SCREEN_WIDTH / 2;
		break;
	case 3:
		xPos = (Clock::SCREEN_WIDTH / 2) + Clock::PIXELS_BETWEEN_CLOCKS + sprite.getGlobalBounds().width;
		break;
	}

	sprite.setPosition(xPos, yPos);
	hourHandSprite.setPosition(xPos, yPos);
	minuteHandSprite.setPosition(xPos, yPos);
	secondHandSprite.setPosition(xPos, yPos);
	clockNumberText.setPosition(xPos, yPos * 1.75);
}
void AnalogueClock::addSecond() {
	time.addSecond();
	updateHandPositions();
}
void AnalogueClock::updateHandPositions() {
	hourHandSprite.setRotation(time.getHourHandAngle());
	minuteHandSprite.setRotation(time.getMinuteHandAngle());
	secondHandSprite.setRotation(time.getSecondHandAngle());
}
sf::Sprite AnalogueClock::getSprite() {
	return sprite;
}
sf::Sprite AnalogueClock::getHourHandSprite() {
	return hourHandSprite;
}
sf::Sprite AnalogueClock::getMinuteHandSprite() {
	return minuteHandSprite;
}
sf::Sprite AnalogueClock::getSecondHandSprite() {
	return secondHandSprite;
}
sf::Text AnalogueClock::getClockNumberText() {
	return clockNumberText;
}
void AnalogueClock::draw(sf::RenderWindow &window) {
	window.draw(getSprite());
	window.draw(getSecondHandSprite());
	window.draw(getMinuteHandSprite());
	window.draw(getHourHandSprite());
	window.draw(getClockNumberText());
}
