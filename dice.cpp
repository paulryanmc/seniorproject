#include <SFML/Graphics.hpp>
#include <time.h>
#include "title.h"
#include <string>
#include <iostream> 

using namespace sf;


void dice() {
	// Creates and initializes all needed variables and sfml components, including all of the needed text sprites
	int board1[13];
	int board2[13];
	int turn = 1;
	for (int i = 0; i < 13; ++i) {
		board1[i] = -1;
		board2[i] = -1;
	}
	int diceResult[5] = { 0 };
	int diceFreeze[5] = { 0 };
	srand(time(0));
	int rollCount = 0, totals = 0, score = 0, check = 0, once = 0;
	bool gamecomplete = false, rolled = false;

	RenderWindow diceWindow(VideoMode(1280, 720), "dice", sf::Style::Titlebar | sf::Style::Close);

	Texture bg, dices;
	if (!bg.loadFromFile("resources/dicebg.png"))
		std::cout << "Can't find the image" << std::endl;
	if (!dices.loadFromFile("resources/DiceSprite.png"))
		std::cout << "Can't find the image" << std::endl;

	Sprite background(bg), dice1(dices), dice2(dices), dice3(dices), dice4(dices), dice5(dices);

	dice1.setPosition(344, 107);
	dice2.setPosition(479, 107);
	dice3.setPosition(614, 107);
	dice4.setPosition(749, 107);
	dice5.setPosition(884, 107);

	sf::Font font;
	if (!font.loadFromFile("resources/arial.ttf"))
		std::cout << "Can't find the font" << std::endl;

	sf::Text text;
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setOutlineThickness(4);
	text.setString("Roll to get a number!");
	text.setPosition(30.0f, 120.0f);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(28);

	sf::Text turnText;
	turnText.setFont(font);
	turnText.setStyle(sf::Text::Bold);
	turnText.setOutlineThickness(4);
	turnText.setString("Player 1 Turn");
	turnText.setPosition(1050.0f, 120.0f);
	turnText.setFillColor(sf::Color::White);
	turnText.setCharacterSize(28);

	sf::Text total;
	total.setFont(font);
	total.setStyle(sf::Text::Bold);
	total.setOutlineThickness(4);
	total.setString(std::to_string(totals));
	total.setPosition(145.0f, 180.0f);
	total.setFillColor(sf::Color::White);
	total.setCharacterSize(40);

	sf::Text player1Text;
	player1Text.setFont(font);
	player1Text.setStyle(sf::Text::Bold);
	player1Text.setOutlineThickness(4);
	player1Text.setString("Player 1");
	player1Text.setPosition(90.0f, 370.0f);
	player1Text.setFillColor(sf::Color::White);
	player1Text.setCharacterSize(20);

	sf::Text onesText;
	onesText.setFont(font);
	onesText.setStyle(sf::Text::Bold);
	onesText.setOutlineThickness(4);
	onesText.setString("Ones:");
	onesText.setPosition(20.0f, 410.0f);
	onesText.setFillColor(sf::Color::White);
	onesText.setCharacterSize(18);

	sf::Text onesNumber;
	onesNumber.setFont(font);
	onesNumber.setStyle(sf::Text::Bold);
	onesNumber.setOutlineThickness(4);
	onesNumber.setString("-");
	onesNumber.setPosition(80.0f, 410.0f);
	onesNumber.setFillColor(sf::Color::White);
	onesNumber.setCharacterSize(18);

	sf::Text twosText;
	twosText.setFont(font);
	twosText.setStyle(sf::Text::Bold);
	twosText.setOutlineThickness(4);
	twosText.setString("Twos:");
	twosText.setPosition(20.0f, 440.0f);
	twosText.setFillColor(sf::Color::White);
	twosText.setCharacterSize(18);

	sf::Text twosNumber;
	twosNumber.setFont(font);
	twosNumber.setStyle(sf::Text::Bold);
	twosNumber.setOutlineThickness(4);
	twosNumber.setString("-");
	twosNumber.setPosition(80.0f, 440.0f);
	twosNumber.setFillColor(sf::Color::White);
	twosNumber.setCharacterSize(18);

	sf::Text threesText;
	threesText.setFont(font);
	threesText.setStyle(sf::Text::Bold);
	threesText.setOutlineThickness(4);
	threesText.setString("Threes:");
	threesText.setPosition(20.0f, 470.0f);
	threesText.setFillColor(sf::Color::White);
	threesText.setCharacterSize(18);

	sf::Text threesNumber;
	threesNumber.setFont(font);
	threesNumber.setStyle(sf::Text::Bold);
	threesNumber.setOutlineThickness(4);
	threesNumber.setString("-");
	threesNumber.setPosition(100.0f, 470.0f);
	threesNumber.setFillColor(sf::Color::White);
	threesNumber.setCharacterSize(18);

	sf::Text foursText;
	foursText.setFont(font);
	foursText.setStyle(sf::Text::Bold);
	foursText.setOutlineThickness(4);
	foursText.setString("Fours:");
	foursText.setPosition(20.0f, 500.0f);
	foursText.setFillColor(sf::Color::White);
	foursText.setCharacterSize(18);

	sf::Text foursNumber;
	foursNumber.setFont(font);
	foursNumber.setStyle(sf::Text::Bold);
	foursNumber.setOutlineThickness(4);
	foursNumber.setString("-");
	foursNumber.setPosition(80.0f, 500.0f);
	foursNumber.setFillColor(sf::Color::White);
	foursNumber.setCharacterSize(18);

	sf::Text fivesText;
	fivesText.setFont(font);
	fivesText.setStyle(sf::Text::Bold);
	fivesText.setOutlineThickness(4);
	fivesText.setString("Fives:");
	fivesText.setPosition(20.0f, 530.0f);
	fivesText.setFillColor(sf::Color::White);
	fivesText.setCharacterSize(18);

	sf::Text fivesNumber;
	fivesNumber.setFont(font);
	fivesNumber.setStyle(sf::Text::Bold);
	fivesNumber.setOutlineThickness(4);
	fivesNumber.setString("-");
	fivesNumber.setPosition(80.0f, 530.0f);
	fivesNumber.setFillColor(sf::Color::White);
	fivesNumber.setCharacterSize(18);

	sf::Text sixesText;
	sixesText.setFont(font);
	sixesText.setStyle(sf::Text::Bold);
	sixesText.setOutlineThickness(4);
	sixesText.setString("Sixes:");
	sixesText.setPosition(20.0f, 560.0f);
	sixesText.setFillColor(sf::Color::White);
	sixesText.setCharacterSize(18);

	sf::Text sixesNumber;
	sixesNumber.setFont(font);
	sixesNumber.setStyle(sf::Text::Bold);
	sixesNumber.setOutlineThickness(4);
	sixesNumber.setString("-");
	sixesNumber.setPosition(80.0f, 560.0f);;
	sixesNumber.setFillColor(sf::Color::White);
	sixesNumber.setCharacterSize(18);

	sf::Text toakText;
	toakText.setFont(font);
	toakText.setStyle(sf::Text::Bold);
	toakText.setOutlineThickness(4);
	toakText.setString("3 o'Kind:");
	toakText.setPosition(180.0f, 410.0f);
	toakText.setFillColor(sf::Color::White);
	toakText.setCharacterSize(18);

	sf::Text toakNumber;
	toakNumber.setFont(font);
	toakNumber.setStyle(sf::Text::Bold);
	toakNumber.setOutlineThickness(4);
	toakNumber.setString("-");
	toakNumber.setPosition(270.0f, 410.0f);
	toakNumber.setFillColor(sf::Color::White);
	toakNumber.setCharacterSize(18);

	sf::Text foakText;
	foakText.setFont(font);
	foakText.setStyle(sf::Text::Bold);
	foakText.setOutlineThickness(4);
	foakText.setString("4 o'Kind:");
	foakText.setPosition(180.0f, 440.0f);
	foakText.setFillColor(sf::Color::White);
	foakText.setCharacterSize(18);

	sf::Text foakNumber;
	foakNumber.setFont(font);
	foakNumber.setStyle(sf::Text::Bold);
	foakNumber.setOutlineThickness(4);
	foakNumber.setString("-");
	foakNumber.setPosition(270.0f, 440.0f);
	foakNumber.setFillColor(sf::Color::White);
	foakNumber.setCharacterSize(18);

	sf::Text houseText;
	houseText.setFont(font);
	houseText.setStyle(sf::Text::Bold);
	houseText.setOutlineThickness(4);
	houseText.setString("Full House:");
	houseText.setPosition(160.0f, 470.0f);
	houseText.setFillColor(sf::Color::White);
	houseText.setCharacterSize(18);

	sf::Text houseNumber;
	houseNumber.setFont(font);
	houseNumber.setStyle(sf::Text::Bold);
	houseNumber.setOutlineThickness(4);
	houseNumber.setString("-");
	houseNumber.setPosition(270.0f, 470.0f);
	houseNumber.setFillColor(sf::Color::White);
	houseNumber.setCharacterSize(18);

	sf::Text smallText;
	smallText.setFont(font);
	smallText.setStyle(sf::Text::Bold);
	smallText.setOutlineThickness(4);
	smallText.setString("Small:");
	smallText.setPosition(200.0f, 500.0f);
	smallText.setFillColor(sf::Color::White);
	smallText.setCharacterSize(18);

	sf::Text smallNumber;
	smallNumber.setFont(font);
	smallNumber.setStyle(sf::Text::Bold);
	smallNumber.setOutlineThickness(4);
	smallNumber.setString("-");
	smallNumber.setPosition(270.0f, 500.0f);
	smallNumber.setFillColor(sf::Color::White);
	smallNumber.setCharacterSize(18);

	sf::Text largeText;
	largeText.setFont(font);
	largeText.setStyle(sf::Text::Bold);
	largeText.setOutlineThickness(4);
	largeText.setString("Large:");
	largeText.setPosition(200.0f, 530.0f);
	largeText.setFillColor(sf::Color::White);
	largeText.setCharacterSize(18);

	sf::Text largeNumber;
	largeNumber.setFont(font);
	largeNumber.setStyle(sf::Text::Bold);
	largeNumber.setOutlineThickness(4);
	largeNumber.setString("-");
	largeNumber.setPosition(270.0f, 530.0f);
	largeNumber.setFillColor(sf::Color::White);
	largeNumber.setCharacterSize(18);

	sf::Text yahtzText;
	yahtzText.setFont(font);
	yahtzText.setStyle(sf::Text::Bold);
	yahtzText.setOutlineThickness(4);
	yahtzText.setString("5 o'kind:");
	yahtzText.setPosition(180.0f, 560.0f);
	yahtzText.setFillColor(sf::Color::White);
	yahtzText.setCharacterSize(18);

	sf::Text yahtzNumber;
	yahtzNumber.setFont(font);
	yahtzNumber.setStyle(sf::Text::Bold);
	yahtzNumber.setOutlineThickness(4);
	yahtzNumber.setString("-");
	yahtzNumber.setPosition(270.0f, 560.0f);
	yahtzNumber.setFillColor(sf::Color::White);
	yahtzNumber.setCharacterSize(18);

	sf::Text chanceText;
	chanceText.setFont(font);
	chanceText.setStyle(sf::Text::Bold);
	chanceText.setOutlineThickness(4);
	chanceText.setString("Chance:");
	chanceText.setPosition(20.0f, 590.0f);
	chanceText.setFillColor(sf::Color::White);
	chanceText.setCharacterSize(18);

	sf::Text chanceNumber;
	chanceNumber.setFont(font);
	chanceNumber.setStyle(sf::Text::Bold);
	chanceNumber.setOutlineThickness(4);
	chanceNumber.setString("-");
	chanceNumber.setPosition(100.0f, 590.0f);
	chanceNumber.setFillColor(sf::Color::White);
	chanceNumber.setCharacterSize(18);

	sf::Text totalText;
	totalText.setFont(font);
	totalText.setStyle(sf::Text::Bold);
	totalText.setOutlineThickness(4);
	totalText.setString("Total:");
	totalText.setPosition(200.0f, 590.0f);
	totalText.setFillColor(sf::Color::White);
	totalText.setCharacterSize(18);

	sf::Text totalNumber;
	totalNumber.setFont(font);
	totalNumber.setStyle(sf::Text::Bold);
	totalNumber.setOutlineThickness(4);
	totalNumber.setString("-");
	totalNumber.setPosition(270.0f, 590.0f);
	totalNumber.setFillColor(sf::Color::White);
	totalNumber.setCharacterSize(18);

	sf::Text player2Text;
	player2Text.setFont(font);
	player2Text.setStyle(sf::Text::Bold);
	player2Text.setOutlineThickness(4);
	player2Text.setString("Player 2");
	player2Text.setPosition(1050.0f, 370.0f);
	player2Text.setFillColor(sf::Color::White);
	player2Text.setCharacterSize(20);

	sf::Text onesText2;
	onesText2.setFont(font);
	onesText2.setStyle(sf::Text::Bold);
	onesText2.setOutlineThickness(4);
	onesText2.setString("Ones:");
	onesText2.setPosition(970.0f, 410.0f);
	onesText2.setFillColor(sf::Color::White);
	onesText2.setCharacterSize(18);

	sf::Text onesNumber2;
	onesNumber2.setFont(font);
	onesNumber2.setStyle(sf::Text::Bold);
	onesNumber2.setOutlineThickness(4);
	onesNumber2.setString("-");
	onesNumber2.setPosition(1030.0f, 410.0f);
	onesNumber2.setFillColor(sf::Color::White);
	onesNumber2.setCharacterSize(18);

	sf::Text twosText2;
	twosText2.setFont(font);
	twosText2.setStyle(sf::Text::Bold);
	twosText2.setOutlineThickness(4);
	twosText2.setString("Twos:");
	twosText2.setPosition(970.0f, 440.0f);
	twosText2.setFillColor(sf::Color::White);
	twosText2.setCharacterSize(18);

	sf::Text twosNumber2;
	twosNumber2.setFont(font);
	twosNumber2.setStyle(sf::Text::Bold);
	twosNumber2.setOutlineThickness(4);
	twosNumber2.setString("-");
	twosNumber2.setPosition(1030.0f, 440.0f);
	twosNumber2.setFillColor(sf::Color::White);
	twosNumber2.setCharacterSize(18);

	sf::Text threesText2;
	threesText2.setFont(font);
	threesText2.setStyle(sf::Text::Bold);
	threesText2.setOutlineThickness(4);
	threesText2.setString("Threes:");
	threesText2.setPosition(970.0f, 470.0f);
	threesText2.setFillColor(sf::Color::White);
	threesText2.setCharacterSize(18);

	sf::Text threesNumber2;
	threesNumber2.setFont(font);
	threesNumber2.setStyle(sf::Text::Bold);
	threesNumber2.setOutlineThickness(4);
	threesNumber2.setString("-");
	threesNumber2.setPosition(1050.0f, 470.0f);
	threesNumber2.setFillColor(sf::Color::White);
	threesNumber2.setCharacterSize(18);

	sf::Text foursText2;
	foursText2.setFont(font);
	foursText2.setStyle(sf::Text::Bold);
	foursText2.setOutlineThickness(4);
	foursText2.setString("Fours:");
	foursText2.setPosition(970.0f, 500.0f);
	foursText2.setFillColor(sf::Color::White);
	foursText2.setCharacterSize(18);

	sf::Text foursNumber2;
	foursNumber2.setFont(font);
	foursNumber2.setStyle(sf::Text::Bold);
	foursNumber2.setOutlineThickness(4);
	foursNumber2.setString("-");
	foursNumber2.setPosition(1030.0f, 500.0f);
	foursNumber2.setFillColor(sf::Color::White);
	foursNumber2.setCharacterSize(18);

	sf::Text fivesText2;
	fivesText2.setFont(font);
	fivesText2.setStyle(sf::Text::Bold);
	fivesText2.setOutlineThickness(4);
	fivesText2.setString("Fives:");
	fivesText2.setPosition(970.0f, 530.0f);
	fivesText2.setFillColor(sf::Color::White);
	fivesText2.setCharacterSize(18);

	sf::Text fivesNumber2;
	fivesNumber2.setFont(font);
	fivesNumber2.setStyle(sf::Text::Bold);
	fivesNumber2.setOutlineThickness(4);
	fivesNumber2.setString("-");
	fivesNumber2.setPosition(1030.0f, 530.0f);
	fivesNumber2.setFillColor(sf::Color::White);
	fivesNumber2.setCharacterSize(18);

	sf::Text sixesText2;
	sixesText2.setFont(font);
	sixesText2.setStyle(sf::Text::Bold);
	sixesText2.setOutlineThickness(4);
	sixesText2.setString("Sixes:");
	sixesText2.setPosition(970.0f, 560.0f);
	sixesText2.setFillColor(sf::Color::White);
	sixesText2.setCharacterSize(18);

	sf::Text sixesNumber2;
	sixesNumber2.setFont(font);
	sixesNumber2.setStyle(sf::Text::Bold);
	sixesNumber2.setOutlineThickness(4);
	sixesNumber2.setString("-");
	sixesNumber2.setPosition(1030.0f, 560.0f);;
	sixesNumber2.setFillColor(sf::Color::White);
	sixesNumber2.setCharacterSize(18);

	sf::Text toakText2;
	toakText2.setFont(font);
	toakText2.setStyle(sf::Text::Bold);
	toakText2.setOutlineThickness(4);
	toakText2.setString("3 o'Kind:");
	toakText2.setPosition(1130.0f, 410.0f);
	toakText2.setFillColor(sf::Color::White);
	toakText2.setCharacterSize(18);

	sf::Text toakNumber2;
	toakNumber2.setFont(font);
	toakNumber2.setStyle(sf::Text::Bold);
	toakNumber2.setOutlineThickness(4);
	toakNumber2.setString("-");
	toakNumber2.setPosition(1220.0f, 410.0f);
	toakNumber2.setFillColor(sf::Color::White);
	toakNumber2.setCharacterSize(18);

	sf::Text foakText2;
	foakText2.setFont(font);
	foakText2.setStyle(sf::Text::Bold);
	foakText2.setOutlineThickness(4);
	foakText2.setString("4 o'Kind:");
	foakText2.setPosition(1130.0f, 440.0f);
	foakText2.setFillColor(sf::Color::White);
	foakText2.setCharacterSize(18);

	sf::Text foakNumber2;
	foakNumber2.setFont(font);
	foakNumber2.setStyle(sf::Text::Bold);
	foakNumber2.setOutlineThickness(4);
	foakNumber2.setString("-");
	foakNumber2.setPosition(1220.0f, 440.0f);
	foakNumber2.setFillColor(sf::Color::White);
	foakNumber2.setCharacterSize(18);

	sf::Text houseText2;
	houseText2.setFont(font);
	houseText2.setStyle(sf::Text::Bold);
	houseText2.setOutlineThickness(4);
	houseText2.setString("Full House:");
	houseText2.setPosition(1110.0f, 470.0f);
	houseText2.setFillColor(sf::Color::White);
	houseText2.setCharacterSize(18);

	sf::Text houseNumber2;
	houseNumber2.setFont(font);
	houseNumber2.setStyle(sf::Text::Bold);
	houseNumber2.setOutlineThickness(4);
	houseNumber2.setString("-");
	houseNumber2.setPosition(1220.0f, 470.0f);
	houseNumber2.setFillColor(sf::Color::White);
	houseNumber2.setCharacterSize(18);

	sf::Text smallText2;
	smallText2.setFont(font);
	smallText2.setStyle(sf::Text::Bold);
	smallText2.setOutlineThickness(4);
	smallText2.setString("Small:");
	smallText2.setPosition(1150.0f, 500.0f);
	smallText2.setFillColor(sf::Color::White);
	smallText2.setCharacterSize(18);

	sf::Text smallNumber2;
	smallNumber2.setFont(font);
	smallNumber2.setStyle(sf::Text::Bold);
	smallNumber2.setOutlineThickness(4);
	smallNumber2.setString("-");
	smallNumber2.setPosition(1220.0f, 500.0f);
	smallNumber2.setFillColor(sf::Color::White);
	smallNumber2.setCharacterSize(18);

	sf::Text largeText2;
	largeText2.setFont(font);
	largeText2.setStyle(sf::Text::Bold);
	largeText2.setOutlineThickness(4);
	largeText2.setString("Large:");
	largeText2.setPosition(1150.0f, 530.0f);
	largeText2.setFillColor(sf::Color::White);
	largeText2.setCharacterSize(18);

	sf::Text largeNumber2;
	largeNumber2.setFont(font);
	largeNumber2.setStyle(sf::Text::Bold);
	largeNumber2.setOutlineThickness(4);
	largeNumber2.setString("-");
	largeNumber2.setPosition(1220.0f, 530.0f);
	largeNumber2.setFillColor(sf::Color::White);
	largeNumber2.setCharacterSize(18);

	sf::Text yahtzText2;
	yahtzText2.setFont(font);
	yahtzText2.setStyle(sf::Text::Bold);
	yahtzText2.setOutlineThickness(4);
	yahtzText2.setString("5 o'kind:");
	yahtzText2.setPosition(1130.0f, 560.0f);
	yahtzText2.setFillColor(sf::Color::White);
	yahtzText2.setCharacterSize(18);

	sf::Text yahtzNumber2;
	yahtzNumber2.setFont(font);
	yahtzNumber2.setStyle(sf::Text::Bold);
	yahtzNumber2.setOutlineThickness(4);
	yahtzNumber2.setString("-");
	yahtzNumber2.setPosition(1220.0f, 560.0f);
	yahtzNumber2.setFillColor(sf::Color::White);
	yahtzNumber2.setCharacterSize(18);

	sf::Text chanceText2;
	chanceText2.setFont(font);
	chanceText2.setStyle(sf::Text::Bold);
	chanceText2.setOutlineThickness(4);
	chanceText2.setString("Chance:");
	chanceText2.setPosition(970.0f, 590.0f);
	chanceText2.setFillColor(sf::Color::White);
	chanceText2.setCharacterSize(18);

	sf::Text chanceNumber2;
	chanceNumber2.setFont(font);
	chanceNumber2.setStyle(sf::Text::Bold);
	chanceNumber2.setOutlineThickness(4);
	chanceNumber2.setString("-");
	chanceNumber2.setPosition(1050.0f, 590.0f);
	chanceNumber2.setFillColor(sf::Color::White);
	chanceNumber2.setCharacterSize(18);

	sf::Text totalText2;
	totalText2.setFont(font);
	totalText2.setStyle(sf::Text::Bold);
	totalText2.setOutlineThickness(4);
	totalText2.setString("Total:");
	totalText2.setPosition(1150.0f, 590.0f);
	totalText2.setFillColor(sf::Color::White);
	totalText2.setCharacterSize(18);

	sf::Text totalNumber2;
	totalNumber2.setFont(font);
	totalNumber2.setStyle(sf::Text::Bold);
	totalNumber2.setOutlineThickness(4);
	totalNumber2.setString("-");
	totalNumber2.setPosition(1220.0f, 590.0f);
	totalNumber2.setFillColor(sf::Color::White);
	totalNumber2.setCharacterSize(18);

	sf::Texture rollButton;
	sf::Sprite rollButtonImage;
	if (!rollButton.loadFromFile("resources/roll.png"))
	std::cout << "Can't find the image" << std::endl;
	rollButtonImage.setPosition(585, 275);
	float rollButtonWidth = rollButtonImage.getLocalBounds().width;
	float rollButtonHeight = rollButtonImage.getLocalBounds().height;
	rollButtonImage.setTexture(rollButton);

	sf::Texture exitButton;
	sf::Sprite exitButtonImage;
	if (!exitButton.loadFromFile("resources/diceExit.png"))
	std::cout << "Can't find the image" << std::endl;
	exitButtonImage.setPosition(565, 637);
	float exitButtonWidth = exitButtonImage.getLocalBounds().width;
	float exitButtonHeight = exitButtonImage.getLocalBounds().height;
	exitButtonImage.setTexture(exitButton);


while (diceWindow.isOpen())
{
	// Once the game is complete, determines winner and prevents further rolling
	if (gamecomplete && once == 0)
	{
		text.setPosition(75.0f, 90.0f);
		text.setString("Game Finished!");
		rolled = false;
		score = 0;
		for (int i = 0; i < 13; ++i) {
			score += board1[i];
			once += board2[i];
		}
		if (score > once) {
			turnText.setString("Player 1 Won!");
		}
		else if (once > score) {
			turnText.setString("Player 2 Won!");
		}
		else {
			turnText.setString("Tie!");
		}
		once = 17;
	}
	Event Event;
	while (diceWindow.pollEvent(Event))
	{
		switch (Event.type)
		{
		case Event::Closed:
			diceWindow.close();
			title();
			break;
		case Event::MouseMoved:
		{
			Vector2i mousePos = Mouse::getPosition(diceWindow);
			Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			// if mouse hovers over a button, colors that button
			if (exitButtonImage.getGlobalBounds().contains(mousePosF))
			{
				exitButtonImage.setColor(Color(250, 20, 20));
			}
			else
			{
				exitButtonImage.setColor(Color(255, 255, 255));
			}
			if (rollButtonImage.getGlobalBounds().contains(mousePosF))
			{
				rollButtonImage.setColor(Color(250, 20, 20));
			}
			else
			{
				rollButtonImage.setColor(Color(255, 255, 255));
			}
		}
		break;
		case Event::MouseButtonPressed:
		{
			Vector2i mousePos = Mouse::getPosition(diceWindow);
			Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
			// Sets up the capacity of the several buttons including the ability to freeze die
			if (exitButtonImage.getGlobalBounds().contains(mousePosF))
			{
				diceWindow.close();
				title();
				return;
			}
			else if (dice1.getGlobalBounds().contains(mousePosF))
			{
				if (diceFreeze[0] == false) {
					dice1.setTextureRect(IntRect((107 * diceResult[0] - 107), 107, 107, 107));
					diceFreeze[0] = true;
				}
				else {
					dice1.setTextureRect(IntRect((107 * diceResult[0] - 107), 0, 107, 107));
					diceFreeze[0] = false;
				}
			}
			else if (dice2.getGlobalBounds().contains(mousePosF))
			{
				if (diceFreeze[1] == false) {
					dice2.setTextureRect(IntRect((107 * diceResult[1] - 107), 107, 107, 107));
					diceFreeze[1] = true;
				}
				else {
					dice2.setTextureRect(IntRect((107 * diceResult[1] - 107), 0, 107, 107));
					diceFreeze[1] = false;
				}
			}
			else if (dice3.getGlobalBounds().contains(mousePosF))
			{
				if (diceFreeze[2] == false) {
					dice3.setTextureRect(IntRect((107 * diceResult[2] - 107), 107, 107, 107));
					diceFreeze[2] = true;
				}
				else {
					dice3.setTextureRect(IntRect((107 * diceResult[2] - 107), 0, 107, 107));
					diceFreeze[2] = false;
				}
			}
			else if (dice4.getGlobalBounds().contains(mousePosF))
			{
				if (diceFreeze[3] == false) {
					dice4.setTextureRect(IntRect((107 * diceResult[3] - 107), 107, 107, 107));
					diceFreeze[3] = true;
				}
				else {
					dice4.setTextureRect(IntRect((107 * diceResult[3] - 107), 0, 107, 107));
					diceFreeze[3] = false;
				}
			}
			else if (dice5.getGlobalBounds().contains(mousePosF))
			{
				if (diceFreeze[4] == false) {
					dice5.setTextureRect(IntRect((107 * diceResult[4] - 107), 107, 107, 107));
					diceFreeze[4] = true;
				}
				else {
					dice5.setTextureRect(IntRect((107 * diceResult[4] - 107), 0, 107, 107));
					diceFreeze[4] = false;
				}
			}
			// Rolls the five dice and changes the sprites to the correct numbers as well as allowing the current player to choose a category
			else if (rollButtonImage.getGlobalBounds().contains(mousePosF) /*&& rollCount < 3*/ && gamecomplete == false)
			{
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceFreeze[i] == false) {
						diceResult[i] = rand() % 6 + 1;
						switch (i) {
						case 0:
							dice1.setTextureRect(IntRect((107 * diceResult[i] - 107), 0, 107, 107));
							break;
						case 1:
							dice2.setTextureRect(IntRect((107 * diceResult[i] - 107), 0, 107, 107));
							break;
						case 2:
							dice3.setTextureRect(IntRect((107 * diceResult[i] - 107), 0, 107, 107));
							break;
						case 3:
							dice4.setTextureRect(IntRect((107 * diceResult[i] - 107), 0, 107, 107));
							break;
						case 4:
							dice5.setTextureRect(IntRect((107 * diceResult[i] - 107), 0, 107, 107));
							break;
						}
					}
					totals += diceResult[i];
				}
				total.setString(std::to_string(totals));
				text.setPosition(110.0f, 90.0f);
				text.setString("Results");
				rolled = true;
				rollCount++;
			}
			else if (rollButtonImage.getGlobalBounds().contains(mousePosF) && rollCount == 3)
			{
				text.setPosition(75.0f, 90.0f);
				text.setString("No More Rolls");
			}
			/* All of the below are the various categories the player has to pick between each turn.
			Upon being selected, resets all required variables for the turn to be passed to the next player.
			Each category has a specific condition that needs to be met in order to obtain points, otherwise it will be worth 0 points.
			Also updates the current score sheet for that player. */
			if (onesText.getGlobalBounds().contains(mousePosF) && (board1[0] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 1) {
						totals += 1;
					}
				}
				board1[0] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				onesNumber.setString(std::to_string(board1[0]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (twosText.getGlobalBounds().contains(mousePosF) && (board1[1] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 2) {
						totals += 2;
					}
				}
				board1[1] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				twosNumber.setString(std::to_string(board1[1]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (threesText.getGlobalBounds().contains(mousePosF) && (board1[2] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 3) {
						totals += 3;
					}
				}
				board1[2] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				threesNumber.setString(std::to_string(board1[2]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (foursText.getGlobalBounds().contains(mousePosF) && (board1[3] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 4) {
						totals += 4;
					}
				}
				board1[3] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				foursNumber.setString(std::to_string(board1[3]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (fivesText.getGlobalBounds().contains(mousePosF) && (board1[4] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 5) {
						totals += 5;
					}
				}
				board1[4] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				fivesNumber.setString(std::to_string(board1[4]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (sixesText.getGlobalBounds().contains(mousePosF) && (board1[5] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 6) {
						totals += 6;
					}
				}
				board1[5] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				sixesNumber.setString(std::to_string(board1[5]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (toakText.getGlobalBounds().contains(mousePosF) && (board1[6] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				int tally = 0, tally2 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j]) {
							tally++;
						}
					}
					if (tally > tally2) {
						tally2 = tally;
					}
				}
				if (tally2 < 2) {
					totals = 0;
				}
				board1[6] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				toakNumber.setString(std::to_string(board1[6]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (foakText.getGlobalBounds().contains(mousePosF) && (board1[7] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				int tally = 0, tally2 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j]) {
							tally++;
						}
					}
					if (tally > tally2) {
						tally2 = tally;
					}
				}
				if (tally2 < 3) {
					totals = 0;
				}
				board1[7] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				foakNumber.setString(std::to_string(board1[7]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (houseText.getGlobalBounds().contains(mousePosF) && (board1[8] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				int tally = 0, tally2 = 0, tally3 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j] && diceResult[j] != 17) {
							tally++;
							diceResult[j] = 17;
						}
					}
					if (tally > tally2) {
						if (tally3 == 0) {
							tally3 = tally;
						}
						else {
							tally2 = tally;
						}
					}
				}
				if (tally3 + tally2 == 5) {
					board1[8] = 25;
				}
				else {
					board1[8] = 0;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				houseNumber.setString(std::to_string(board1[8]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (smallText.getGlobalBounds().contains(mousePosF) && (board1[9] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				int tally = 0, tally2 = 1, tally3 = 0;;

				for (int i = 0; i < 4; i++)
				{
					tally2 = 1;
					tally = 0;
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[j] == (diceResult[i] + tally2)) {
							tally++;
							tally2++;
						}
					}
					if (tally > tally3) {
						tally3 = tally;
					}
				}
				if (tally3 >= 3) {
					board1[9] = 30;
				}
				else {
					board1[9] = 0;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				smallNumber.setString(std::to_string(board1[9]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (largeText.getGlobalBounds().contains(mousePosF) && (board1[10] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				int tally = 0, tally2 = 1, tally3 = 0;;

				for (int i = 0; i < 4; i++)
				{
					tally2 = 1;
					tally = 0;
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[j] == (diceResult[i] + tally2)) {
							tally++;
							tally2++;
						}
					}
					if (tally > tally3) {
						tally3 = tally;
					}
				}
				if (tally3 >= 4) {
					board1[10] = 40;
				}
				else {
					board1[10] = 0;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				largeNumber.setString(std::to_string(board1[10]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (yahtzText.getGlobalBounds().contains(mousePosF) && (board1[11] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				int tally = 0, tally2 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j]) {
							tally++;
						}
					}
					if (tally > tally2) {
						tally2 = tally;
					}
				}
				if (tally2 < 5) {
					board1[11] = 0;
				}
				else {
					board1[11] = 50;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				yahtzNumber.setString(std::to_string(board1[11]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (chanceText.getGlobalBounds().contains(mousePosF) && (board1[12] == -1) && rolled == true && turn == 1)
			{
				turnText.setString("Player 2 Turn");
				turn = 2;
				board1[12] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				chanceNumber.setString(std::to_string(board1[12]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board1[i] != -1) {
						score += board1[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber.setString(std::to_string(score));
			}
			if (onesText2.getGlobalBounds().contains(mousePosF) && (board2[0] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 1) {
						totals += 1;
					}
				}
				board2[0] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				onesNumber2.setString(std::to_string(board2[0]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (twosText2.getGlobalBounds().contains(mousePosF) && (board2[1] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 2) {
						totals += 2;
					}
				}
				board2[1] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				twosNumber2.setString(std::to_string(board2[1]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (threesText2.getGlobalBounds().contains(mousePosF) && (board2[2] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 3) {
						totals += 3;
					}
				}
				board2[2] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				threesNumber2.setString(std::to_string(board2[2]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (foursText2.getGlobalBounds().contains(mousePosF) && (board2[3] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 4) {
						totals += 4;
					}
				}
				board2[3] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				foursNumber2.setString(std::to_string(board2[3]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (fivesText2.getGlobalBounds().contains(mousePosF) && (board2[4] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 5) {
						totals += 5;
					}
				}
				board2[4] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				fivesNumber2.setString(std::to_string(board2[4]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (sixesText2.getGlobalBounds().contains(mousePosF) && (board2[5] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				totals = 0;
				for (int i = 0; i < 5; ++i) {
					if (diceResult[i] == 6) {
						totals += 6;
					}
				}
				board2[5] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				sixesNumber2.setString(std::to_string(board2[5]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (toakText2.getGlobalBounds().contains(mousePosF) && (board2[6] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				int tally = 0, tally2 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j]) {
							tally++;
						}
					}
					if (tally > tally2) {
						tally2 = tally;
					}
				}
				if (tally2 < 2) {
					totals = 0;
				}
				board2[6] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				toakNumber2.setString(std::to_string(board2[6]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (foakText2.getGlobalBounds().contains(mousePosF) && (board2[7] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				int tally = 0, tally2 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j]) {
							tally++;
						}
					}
					if (tally > tally2) {
						tally2 = tally;
					}
				}
				if (tally2 < 3) {
					totals = 0;
				}
				board2[7] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				foakNumber2.setString(std::to_string(board2[7]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (houseText2.getGlobalBounds().contains(mousePosF) && (board2[8] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				int tally = 0, tally2 = 0, tally3 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j] && diceResult[j] != 17) {
							tally++;
							diceResult[j] = 17;
						}
					}
					if (tally > tally2) {
						if (tally3 == 0) {
							tally3 = tally;
						}
						else {
							tally2 = tally;
						}
					}
				}
				if (tally3 + tally2 == 5) {
					board2[8] = 25;
				}
				else {
					board2[8] = 0;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				houseNumber2.setString(std::to_string(board2[8]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (smallText2.getGlobalBounds().contains(mousePosF) && (board2[9] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				int tally = 0, tally2 = 1, tally3 = 0;;

				for (int i = 0; i < 4; i++)
				{
					tally2 = 1;
					tally = 0;
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[j] == (diceResult[i] + tally2)) {
							tally++;
							tally2++;
						}
					}
					if (tally > tally3) {
						tally3 = tally;
					}
				}
				if (tally3 >= 3) {
					board2[9] = 30;
				}
				else {
					board2[9] = 0;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				smallNumber2.setString(std::to_string(board2[9]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (largeText2.getGlobalBounds().contains(mousePosF) && (board2[10] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				int tally = 0, tally2 = 1, tally3 = 0;;

				for (int i = 0; i < 4; i++)
				{
					tally2 = 1;
					tally = 0;
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[j] == (diceResult[i] + tally2)) {
							tally++;
							tally2++;
						}
					}
					if (tally > tally3) {
						tally3 = tally;
					}
				}
				if (tally3 >= 4) {
					board2[10] = 40;
				}
				else {
					board2[10] = 0;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				largeNumber2.setString(std::to_string(board2[10]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (yahtzText2.getGlobalBounds().contains(mousePosF) && (board2[11] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				int tally = 0, tally2 = 0;

				for (int i = 0; i < 4; i++)
				{
					for (int j = i + 1; j < 5; j++)
					{
						if (diceResult[i] == diceResult[j]) {
							tally++;
						}
					}
					if (tally > tally2) {
						tally2 = tally;
					}
				}
				if (tally2 < 5) {
					board2[11] = 0;
				}
				else {
					board2[11] = 50;
				}
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				yahtzNumber2.setString(std::to_string(board2[11]));
				score = 0;
				check++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			if (chanceText2.getGlobalBounds().contains(mousePosF) && (board2[12] == -1) && rolled == true && turn == 2)
			{
				turnText.setString("Player 1 Turn");
				turn = 1;
				board2[12] = totals;
				text.setString("Roll to get a number!");
				text.setPosition(30.0f, 120.0f);
				rolled = false;
				for (int i = 0; i < 5; ++i) {
					diceFreeze[i] = false;
				}
				rollCount = 0;
				chanceNumber2.setString(std::to_string(board2[12]));
				score = 0;
				check ++;
				for (int i = 0; i < 13; ++i) {
					if (board2[i] != -1) {
						score += board2[i];
					}
				}
				if (check == 26)
				{
					gamecomplete = true;
				}
				totalNumber2.setString(std::to_string(score));
			}
			break;
			}
		}
		// All of the sprite drawing commands.
			diceWindow.clear();
			diceWindow.draw(background);
			diceWindow.draw(rollButtonImage);
			diceWindow.draw(exitButtonImage);
			diceWindow.draw(text);
			diceWindow.draw(onesText);
			diceWindow.draw(onesNumber);
			diceWindow.draw(twosText);
			diceWindow.draw(twosNumber);
			diceWindow.draw(threesText);
			diceWindow.draw(threesNumber);
			diceWindow.draw(foursText);
			diceWindow.draw(foursNumber);
			diceWindow.draw(fivesText);
			diceWindow.draw(fivesNumber);
			diceWindow.draw(sixesText);
			diceWindow.draw(sixesNumber);
			diceWindow.draw(toakText);
			diceWindow.draw(toakNumber);
			diceWindow.draw(foakText);
			diceWindow.draw(foakNumber);
			diceWindow.draw(houseText);
			diceWindow.draw(houseNumber);
			diceWindow.draw(smallText);
			diceWindow.draw(smallNumber);
			diceWindow.draw(largeText);
			diceWindow.draw(largeNumber);
			diceWindow.draw(yahtzText);
			diceWindow.draw(yahtzNumber);
			diceWindow.draw(chanceText);
			diceWindow.draw(chanceNumber);
			diceWindow.draw(totalText);
			diceWindow.draw(totalNumber);
			diceWindow.draw(onesText2);
			diceWindow.draw(onesNumber2);
			diceWindow.draw(twosText2);
			diceWindow.draw(twosNumber2);
			diceWindow.draw(threesText2);
			diceWindow.draw(threesNumber2);
			diceWindow.draw(foursText2);
			diceWindow.draw(foursNumber2);
			diceWindow.draw(fivesText2);
			diceWindow.draw(fivesNumber2);
			diceWindow.draw(sixesText2);
			diceWindow.draw(sixesNumber2);
			diceWindow.draw(toakText2);
			diceWindow.draw(toakNumber2);
			diceWindow.draw(foakText2);
			diceWindow.draw(foakNumber2);
			diceWindow.draw(houseText2);
			diceWindow.draw(houseNumber2);
			diceWindow.draw(smallText2);
			diceWindow.draw(smallNumber2);
			diceWindow.draw(largeText2);
			diceWindow.draw(largeNumber2);
			diceWindow.draw(yahtzText2);
			diceWindow.draw(yahtzNumber2);
			diceWindow.draw(chanceText2);
			diceWindow.draw(chanceNumber2);
			diceWindow.draw(totalText2);
			diceWindow.draw(totalNumber2);
			diceWindow.draw(player1Text);
			diceWindow.draw(player2Text);
			diceWindow.draw(turnText);
			if (rolled) {
				diceWindow.draw(dice1);
				diceWindow.draw(dice2);
				diceWindow.draw(dice3);
				diceWindow.draw(dice4);
				diceWindow.draw(dice5);
				diceWindow.draw(total);
			}
			diceWindow.display();
		}
	}
}