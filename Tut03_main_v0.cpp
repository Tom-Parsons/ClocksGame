
#include "SFML/Graphics.hpp"

#include <iostream>

#include "Time.h"
#include "AnalogueClock.h"
#include "RandomNumberGenerator.h"
#include "Score.h"
#include "Clock.h"

using namespace std;

enum GameState {
	GENERATING_CLOCKS,
	WAITING_FOR_NUMBER_INPUT,
	WAITING_FOR_CONTINUE_INPUT
};


// GAMEDATA STRUCT
struct GameData {
	sf::Text titleText;
	sf::Text messageText;
	AnalogueClock clock1;
	AnalogueClock clock2;
	AnalogueClock clock3;
	int realClock; // The number id of the clock that shows the real time
	sf::Text mainClockText;
	sf::Sprite alarmClock;
	GameState state;
};

int main()
{
	void renderWindow(sf::RenderWindow &window, GameData &gameData);
	void setText(sf::Text &text, sf::Font &font, const string &displayText, const int fontSize, const int posX, const int posY);
	void resetGame(GameData &gameData);

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(Clock::SCREEN_WIDTH, Clock::SCREEN_HEIGHT), "What time is it?");

	sf::Font fontArial;
	sf::Font fontClock;
	if (!fontArial.loadFromFile("assets/Arial.ttf")) {
		cout << "Error: Could not load Arial.ttf" << endl;
	}
	if (!fontClock.loadFromFile("assets/digital-7.ttf")) {
		cout << "Error: Could not load Arial.ttf" << endl;
	}

	sf::Text titleText;
	setText(titleText, fontClock, "TIME TO PLAY? ", 32, 30, 30);

	sf::Text mainClockText;
	setText(mainClockText, fontClock, "12:00:00", 72, (Clock::SCREEN_WIDTH / 2), Clock::SCREEN_HEIGHT / 4);
	mainClockText.setPosition((Clock::SCREEN_WIDTH / 2) - mainClockText.getLocalBounds().width / 2, (Clock::SCREEN_HEIGHT / 4) - mainClockText.getLocalBounds().height / 2);

	sf::Text messageText;
	setText(messageText, fontArial, "Which clock shows the same time as the digital one? 1 or 2 or 3", 32, 30, (Clock::SCREEN_HEIGHT - 60));

	sf::Texture alarmClockTexure;
	if (!alarmClockTexure.loadFromFile("assets/digital_clock.png")) {
		cout << "Error: could not load digital_clock.png" << endl;
	}
	sf::Sprite alarmClockSprite;
	alarmClockSprite.setTexture(alarmClockTexure);
	alarmClockSprite.setScale(0.75f, 0.75f);
	alarmClockSprite.setOrigin(alarmClockSprite.getLocalBounds().width / 2, alarmClockSprite.getLocalBounds().height / 2);
	alarmClockSprite.setPosition((Clock::SCREEN_WIDTH / 2), Clock::SCREEN_HEIGHT / 4);

	AnalogueClock clock1;
	clock1.setClockPosition(1, fontArial);
	clock1.updateHandPositions();

	AnalogueClock clock2;
	clock2.setClockPosition(2, fontArial);
	clock2.updateHandPositions();

	AnalogueClock clock3;
	clock3.setClockPosition(3, fontArial);
	clock3.updateHandPositions();

	int realClock = 1;

	GameState state = GameState::WAITING_FOR_NUMBER_INPUT;
	GameData gameData = { titleText, messageText, clock1, clock2, clock3, realClock, mainClockText, alarmClockSprite, state };

	resetGame(gameData);

	renderWindow(window, gameData);

	return EXIT_SUCCESS;
}

void resetGame(GameData &gameData) {
	RandomNumberGenerator rng;
	gameData.realClock = rng.getRandomValue(3);

	Time newTime(Time::getCurrentHours(), Time::getCurrentMinutes(), Time::getCurrentSeconds());

	switch (gameData.realClock) {
	case 1:
		gameData.clock1.setTime(newTime);
		gameData.clock2.setTime(Time());
		gameData.clock3.setTime(Time(gameData.clock2.getTime(), false));
		break;
	case 2:
		gameData.clock2.setTime(newTime);
		gameData.clock1.setTime(Time());
		gameData.clock3.setTime(Time(gameData.clock1.getTime(), false));
		break;
	case 3:
		gameData.clock3.setTime(newTime);
		gameData.clock1.setTime(Time());
		gameData.clock2.setTime(Time(gameData.clock1.getTime(), false));
		break;
	}

	gameData.messageText.setString("Which clock shows the same time as the digital one? 1 or 2 or 3");
	gameData.state = GameState::WAITING_FOR_NUMBER_INPUT;
}

void setText(sf::Text &text, sf::Font &font, const string &displayText, const int fontSize, const int posX, const int posY) {
	text.setPosition(posX, posY);
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color::White);
	text.setString(displayText);
}

void checkKeyPress(sf::RenderWindow &window, sf::Event event, GameData &gameData) {
	if (gameData.state == GameState::WAITING_FOR_NUMBER_INPUT) {
		if (event.key.code == sf::Keyboard::Num1) {
			gameData.state = GameState::WAITING_FOR_CONTINUE_INPUT;
			if (gameData.realClock == 1) {
				gameData.messageText.setString("Correct! Try again? <y or n>");
			}
			else {
				gameData.messageText.setString("Incorrect! Try again? <y or n>");
			}
		}else if (event.key.code == sf::Keyboard::Num2) {
			gameData.state = GameState::WAITING_FOR_CONTINUE_INPUT;
			if (gameData.realClock == 2) {
				gameData.messageText.setString("Correct! Try again? <y or n>");
			}
			else {
				gameData.messageText.setString("Incorrect! Try again? <y or n>");
			}
		}else if (event.key.code == sf::Keyboard::Num3) {
			gameData.state = GameState::WAITING_FOR_CONTINUE_INPUT;
			if (gameData.realClock == 3) {
				gameData.messageText.setString("Correct! Try again? <y or n>");
			}
			else {
				gameData.messageText.setString("Incorrect! Try again? <y or n>");
			}
		}
	}
	else if (gameData.state == GameState::WAITING_FOR_CONTINUE_INPUT) {
		if (event.key.code == sf::Keyboard::Y) {
			resetGame(gameData);
		}
		else if (event.key.code == sf::Keyboard::N) {
			window.close();
		}
	}
}

void renderWindow(sf::RenderWindow &window, GameData &gameData) {

	time_t prevTime = time(0);

	// Start the game loop
	while (window.isOpen())
	{
		if (to_string(prevTime) != to_string(time(0))) {
			gameData.clock1.addSecond();
			gameData.clock2.addSecond();
			gameData.clock3.addSecond();
			gameData.clock1.updateHandPositions();
			gameData.clock2.updateHandPositions();
			gameData.clock3.updateHandPositions();
			if (gameData.realClock == 1) gameData.mainClockText.setString(gameData.clock1.getTime().toString());
			if (gameData.realClock == 2) gameData.mainClockText.setString(gameData.clock2.getTime().toString());
			if (gameData.realClock == 3) gameData.mainClockText.setString(gameData.clock3.getTime().toString());
			prevTime = time(0);
		}
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				checkKeyPress(window, event, gameData);
			}
		}

		// Clear screen
		window.clear();

		window.draw(gameData.titleText);
		window.draw(gameData.messageText);
		window.draw(gameData.alarmClock);
		window.draw(gameData.mainClockText);

		gameData.clock1.draw(window);
		gameData.clock2.draw(window);
		gameData.clock3.draw(window);

		// Update the window
		window.display();
	}
}
