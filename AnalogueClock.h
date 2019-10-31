#pragma once

#include "SFML/Graphics.hpp"

#include <iostream>

#include "Time.h"
#include "Clock.h"

 

class AnalogueClock {
public:
	AnalogueClock();
	AnalogueClock(Time t);
	Time getTime();
	void setTime(Time t);
	void setClockPosition(int, sf::Font&);
	void addSecond();
	void updateHandPositions();
	sf::Sprite getSprite();
	sf::Sprite getHourHandSprite();
	sf::Sprite getMinuteHandSprite();
	sf::Sprite getSecondHandSprite();
	sf::Text getClockNumberText();
	void draw(sf::RenderWindow&);
private:
	Time time;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Texture hourHandTexture;
	sf::Texture minuteHandTexture;
	sf::Texture secondHandTexture;
	sf::Sprite hourHandSprite;
	sf::Sprite minuteHandSprite;
	sf::Sprite secondHandSprite;
	sf::Text clockNumberText;
	void setImage();
};