#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "blocks.h"
#include "blockssolo.h"
#include "dice.h"
#include "diceai.h"
#include "title.h"
#include "marbles.h"
#include "marblesai.h"
#include <string>
#include <iostream> 
#include <fstream>

using namespace sf;

String keytotext(int key)
{
	switch (key) {
	case 0:
		return "A";
		break;
	case 1:
		return "B";
		break;
	case 2:
		return "C";
		break;
	case 3:
		return "D";
		break;
	case 4:
		return "E";
		break;
	case 5:
		return "F";
		break;
	case 6:
		return "G";
		break;
	case 7:
		return "H";
		break;
	case 8:
		return "I";
		break;
	case 9:
		return "J";
		break;
	case 10:
		return "K";
		break;
	case 11:
		return "L";
		break;
	case 12:
		return "M";
		break;
	case 13:
		return "N";
		break;
	case 14:
		return "O";
		break;
	case 15:
		return "P";
		break;
	case 16:
		return "Q";
		break;
	case 17:
		return "R";
		break;
	case 18:
		return "S";
		break;
	case 19:
		return "T";
		break;
	case 20:
		return "U";
		break;
	case 21:
		return "V";
		break;
	case 22:
		return "W";
		break;
	case 23:
		return "X";
		break;
	case 24:
		return "Y";
		break;
	case 25:
		return "Z";
		break;
	case 71:
		return "Left";
		break;
	case 72:
		return "Right";
		break;
	case 73:
		return "Up";
		break;
	case 74:
		return "Down";
		break;
	}
	return "?";
}

int title()
{
	int blockPlayer = 1, dicePlayer = 1, marblesPlayer = 1, wind = 1, hold = 0, wait = 0,
		vol = 50, player1Rotate = 73, player1Left = 71, player1Right = 72, player1Drop = 74,
		player2Rotate = 22, player2Left = 0, player2Right = 3, player2Drop = 18;

	std::ifstream stream("games.ini");
	if (stream.peek() != std::fstream::traits_type::eof()) {
		int a, b = 0;
		while (stream >> a)
		{
			switch (b) {
			case 0:
				vol = a;
				break;
			case 1:
				player1Rotate = a;
				break;
			case 2:
				player1Left = a;
				break;
			case 3:
				player1Right = a;
				break;
			case 4:
				player1Drop = a;
				break;
			case 5:
				player2Rotate = a;
				break;
			case 6:
				player2Left = a;
				break;
			case 7:
				player2Right = a;
				break;
			case 8:
				player2Drop = a;
				break;
			}
			b++;
		}
	}
	stream.close();

	// Creates and initializes all needed variables and sfml components
	RenderWindow window(VideoMode(1280, 720), "title", sf::Style::Titlebar | sf::Style::Close);

	sf::Font font;
	if (!font.loadFromFile("resources/arial.ttf"))
		std::cout << "Can't find the font" << std::endl;

	sf::Texture bg;
	if (!bg.loadFromFile("resources/titlebg.png"))
		std::cout << "Can't find the image" << std::endl;

	sf::Texture blankButton;
	if (!blankButton.loadFromFile("resources/blankbutton.png"))
		std::cout << "Can't find the image" << std::endl;

	sf::Texture player1Button;
	if (!player1Button.loadFromFile("resources/oneplayerbutton.png"))
		std::cout << "Can't find the image" << std::endl;

	sf::Texture player2Button;
	if (!player2Button.loadFromFile("resources/twoplayerbutton.png"))
		std::cout << "Can't find the image" << std::endl;

	sf::Texture rightArrow;
	if (!rightArrow.loadFromFile("resources/rightarrow.png"))
		std::cout << "Can't find the image" << std::endl;

	sf::Texture leftArrow;
	if (!leftArrow.loadFromFile("resources/leftarrow.png"))
		std::cout << "Can't find the image" << std::endl;

	Sprite background(bg);

	sf::Texture settingsMenu;
	sf::Sprite settingsMenuImage;
	if (!settingsMenu.loadFromFile("resources/settingsmenu.png"))
		std::cout << "Can't find the image" << std::endl;
	settingsMenuImage.setPosition(15.0f, 10.0f);
	settingsMenuImage.setTexture(settingsMenu);

	sf::Texture blocksHelp;
	sf::Sprite blocksHelpImage;
	if (!blocksHelp.loadFromFile("resources/blockshelp.png"))
		std::cout << "Can't find the image" << std::endl;
	blocksHelpImage.setPosition(15.0f, 10.0f);
	blocksHelpImage.setTexture(blocksHelp);

	sf::Texture diceHelp;
	sf::Sprite diceHelpImage;
	if (!diceHelp.loadFromFile("resources/dicehelp.png"))
		std::cout << "Can't find the image" << std::endl;
	diceHelpImage.setPosition(15.0f, 10.0f);
	diceHelpImage.setTexture(diceHelp);

	sf::Texture categoriesHelp;
	sf::Sprite categoriesHelpImage;
	if (!categoriesHelp.loadFromFile("resources/categorieshelp.png"))
		std::cout << "Can't find the image" << std::endl;
	categoriesHelpImage.setPosition(15.0f, 10.0f);
	categoriesHelpImage.setTexture(categoriesHelp);

	sf::Texture marblesHelp;
	sf::Sprite marblesHelpImage;
	if (!marblesHelp.loadFromFile("resources/marbleshelp.png"))
		std::cout << "Can't find the image" << std::endl;
	marblesHelpImage.setPosition(15.0f, 10.0f);
	marblesHelpImage.setTexture(marblesHelp);

	sf::Sprite arrowButtonImage;
	arrowButtonImage.setPosition(761.0f, 590.0f);
	arrowButtonImage.setTexture(rightArrow);

	sf::Texture blocksButton;
	sf::Sprite blocksButtonImage;
	if (!blocksButton.loadFromFile("resources/Blocks.png"))
		std::cout << "Can't find the image" << std::endl;
	blocksButtonImage.setPosition(520.0f, 170.0f);
	blocksButtonImage.setTexture(blocksButton);

	sf::Texture blocksQuestionButton;
	sf::Sprite blocksQuestionButtonImage;
	if (!blocksQuestionButton.loadFromFile("resources/questionbutton.png"))
		std::cout << "Can't find the image" << std::endl;
	blocksQuestionButtonImage.setPosition(400.0f, 170.0f);
	blocksQuestionButtonImage.setTexture(blocksQuestionButton);

	sf::Sprite blocksPlayerButtonImage;
	blocksPlayerButtonImage.setPosition(761.0f, 170.0f);
	blocksPlayerButtonImage.setTexture(player1Button);

	sf::Texture diceButton;
	sf::Sprite diceButtonImage;
	if (!diceButton.loadFromFile("resources/Dice.png"))
		std::cout << "Can't find the image" << std::endl;
	diceButtonImage.setPosition(520.0f, 310.0f);
	diceButtonImage.setTexture(diceButton);

	sf::Texture diceQuestionButton;
	sf::Sprite diceQuestionButtonImage;
	if (!diceQuestionButton.loadFromFile("resources/questionbutton.png"))
		std::cout << "Can't find the image" << std::endl;
	diceQuestionButtonImage.setPosition(400.0f, 310.0f);
	diceQuestionButtonImage.setTexture(diceQuestionButton);

	sf::Sprite dicePlayerButtonImage;
	dicePlayerButtonImage.setPosition(761.0f, 310.0f);
	dicePlayerButtonImage.setTexture(player1Button);

	sf::Texture marblesButton;
	sf::Sprite marblesButtonImage;
	if (!marblesButton.loadFromFile("resources/Marbles.png"))
		std::cout << "Can't find the image" << std::endl;
	marblesButtonImage.setPosition(520.0f, 450.0f);
	marblesButtonImage.setTexture(marblesButton);

	sf::Texture marblesQuestionButton;
	sf::Sprite marblesQuestionButtonImage;
	if (!marblesQuestionButton.loadFromFile("resources/questionbutton.png"))
		std::cout << "Can't find the image" << std::endl;
	marblesQuestionButtonImage.setPosition(400.0f, 450.0f);
	marblesQuestionButtonImage.setTexture(marblesQuestionButton);

	sf::Sprite marblesPlayerButtonImage;
	marblesPlayerButtonImage.setPosition(761.0f, 450.0f);
	marblesPlayerButtonImage.setTexture(player1Button);

	sf::Texture optionButton;
	sf::Sprite optionButtonImage;
	if (!optionButton.loadFromFile("resources/settingsbutton.png"))
		std::cout << "Can't find the image" << std::endl;
	optionButtonImage.setPosition(761.0f, 590.0f);
	optionButtonImage.setTexture(optionButton);

	sf::Texture exitButton;
	sf::Sprite exitButtonImage;
	if (!exitButton.loadFromFile("resources/Exit.png"))
		std::cout << "Can't find the image" << std::endl;
	exitButtonImage.setPosition(520.0f, 590.0f);
	exitButtonImage.setTexture(exitButton);

	sf::Sprite settingsBlockPlayer1Rotate;
	settingsBlockPlayer1Rotate.setPosition(40.0f, 420.0f);
	settingsBlockPlayer1Rotate.setTexture(blankButton);

	sf::Text settingsBlockPlayer1RotateText;
	settingsBlockPlayer1RotateText.setFont(font);
	settingsBlockPlayer1RotateText.setStyle(sf::Text::Bold);
	settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
	settingsBlockPlayer1RotateText.setPosition(50.0f, 460.0f);
	settingsBlockPlayer1RotateText.setFillColor(sf::Color::Black);
	settingsBlockPlayer1RotateText.setCharacterSize(30);

	sf::Sprite settingsBlockPlayer1Left;
	settingsBlockPlayer1Left.setPosition(185.0f, 420.0f);
	settingsBlockPlayer1Left.setTexture(blankButton);

	sf::Text settingsBlockPlayer1LeftText;
	settingsBlockPlayer1LeftText.setFont(font);
	settingsBlockPlayer1LeftText.setStyle(sf::Text::Bold);
	settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
	settingsBlockPlayer1LeftText.setPosition(195.0f, 460.0f);
	settingsBlockPlayer1LeftText.setFillColor(sf::Color::Black);
	settingsBlockPlayer1LeftText.setCharacterSize(30);

	sf::Sprite settingsBlockPlayer1Right;
	settingsBlockPlayer1Right.setPosition(330.0f, 420.0f);
	settingsBlockPlayer1Right.setTexture(blankButton);

	sf::Text settingsBlockPlayer1RightText;
	settingsBlockPlayer1RightText.setFont(font);
	settingsBlockPlayer1RightText.setStyle(sf::Text::Bold);
	settingsBlockPlayer1RightText.setString(keytotext(player1Right));
	settingsBlockPlayer1RightText.setPosition(340.0f, 460.0f);
	settingsBlockPlayer1RightText.setFillColor(sf::Color::Black);
	settingsBlockPlayer1RightText.setCharacterSize(30);

	sf::Sprite settingsBlockPlayer1Drop;
	settingsBlockPlayer1Drop.setPosition(475.0f, 420.0f);
	settingsBlockPlayer1Drop.setTexture(blankButton);

	sf::Text settingsBlockPlayer1DropText;
	settingsBlockPlayer1DropText.setFont(font);
	settingsBlockPlayer1DropText.setStyle(sf::Text::Bold);
	settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
	settingsBlockPlayer1DropText.setPosition(485.0f, 460.0f);
	settingsBlockPlayer1DropText.setFillColor(sf::Color::Black);
	settingsBlockPlayer1DropText.setCharacterSize(30);

	sf::Sprite settingsBlockPlayer2Rotate;
	settingsBlockPlayer2Rotate.setPosition(695.0f, 420.0f);
	settingsBlockPlayer2Rotate.setTexture(blankButton);

	sf::Text settingsBlockPlayer2RotateText;
	settingsBlockPlayer2RotateText.setFont(font);
	settingsBlockPlayer2RotateText.setStyle(sf::Text::Bold);
	settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
	settingsBlockPlayer2RotateText.setPosition(705.0f, 460.0f);
	settingsBlockPlayer2RotateText.setFillColor(sf::Color::Black);
	settingsBlockPlayer2RotateText.setCharacterSize(30);

	sf::Sprite settingsBlockPlayer2Left;
	settingsBlockPlayer2Left.setPosition(840.0f, 420.0f);
	settingsBlockPlayer2Left.setTexture(blankButton);

	sf::Text settingsBlockPlayer2LeftText;
	settingsBlockPlayer2LeftText.setFont(font);
	settingsBlockPlayer2LeftText.setStyle(sf::Text::Bold);
	settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
	settingsBlockPlayer2LeftText.setPosition(850.0f, 460.0f);
	settingsBlockPlayer2LeftText.setFillColor(sf::Color::Black);
	settingsBlockPlayer2LeftText.setCharacterSize(30);

	sf::Sprite settingsBlockPlayer2Right;
	settingsBlockPlayer2Right.setPosition(985.0f, 420.0f);
	settingsBlockPlayer2Right.setTexture(blankButton);

	sf::Text settingsBlockPlayer2RightText;
	settingsBlockPlayer2RightText.setFont(font);
	settingsBlockPlayer2RightText.setStyle(sf::Text::Bold);
	settingsBlockPlayer2RightText.setString(keytotext(player2Right));
	settingsBlockPlayer2RightText.setPosition(995.0f, 460.0f);
	settingsBlockPlayer2RightText.setFillColor(sf::Color::Black);
	settingsBlockPlayer2RightText.setCharacterSize(30);

	sf::Sprite settingsBlockPlayer2Drop;
	settingsBlockPlayer2Drop.setPosition(1130.0f, 420.0f);
	settingsBlockPlayer2Drop.setTexture(blankButton);

	sf::Text settingsBlockPlayer2DropText;
	settingsBlockPlayer2DropText.setFont(font);
	settingsBlockPlayer2DropText.setStyle(sf::Text::Bold);
	settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
	settingsBlockPlayer2DropText.setPosition(1140.0f, 460.0f);
	settingsBlockPlayer2DropText.setFillColor(sf::Color::Black);
	settingsBlockPlayer2DropText.setCharacterSize(30);

	sf::Sprite volumeButton1;
	volumeButton1.setPosition(62.0f, 72.0f);
	volumeButton1.setTexture(blankButton);

	sf::Sprite volumeButton2;
	volumeButton2.setPosition(178.0f, 72.0f);
	volumeButton2.setTexture(blankButton);

	sf::Sprite volumeButton3;
	volumeButton3.setPosition(294.0f, 72.0f);
	volumeButton3.setTexture(blankButton);

	sf::Sprite volumeButton4;
	volumeButton4.setPosition(410.0f, 72.0f);
	volumeButton4.setTexture(blankButton);

	sf::Sprite volumeButton5;
	volumeButton5.setPosition(526.0f, 72.0f);
	volumeButton5.setTexture(blankButton);

	sf::Sprite volumeButton6;
	volumeButton6.setPosition(642.0f, 72.0f);
	volumeButton6.setTexture(blankButton);

	sf::Sprite volumeButton7;
	volumeButton7.setPosition(758.0f, 72.0f);
	volumeButton7.setTexture(blankButton);

	sf::Sprite volumeButton8;
	volumeButton8.setPosition(874.0f, 72.0f);
	volumeButton8.setTexture(blankButton);

	sf::Sprite volumeButton9;
	volumeButton9.setPosition(990.0f, 72.0f);
	volumeButton9.setTexture(blankButton);

	sf::Sprite volumeButton10;
	volumeButton10.setPosition(1106.0f, 72.0f);
	volumeButton10.setTexture(blankButton);

	while (window.isOpen())
	{
		Event Event;
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (wait != 0) {
					switch (wait)
					{
					case 1:
						player1Rotate = Event.key.code;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						wait = 0;
						break;
					case 2:
						player1Left = Event.key.code;
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						wait = 0;
						break;
					case 3:
						player1Right = Event.key.code;
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						wait = 0;
						break;
					case 4:
						player1Drop = Event.key.code;
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						wait = 0;
						break;
					case 5:
						player2Rotate = Event.key.code;
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						wait = 0;
						break;
					case 6:
						player2Left = Event.key.code;
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						wait = 0;
						break;
					case 7:
						player2Right = Event.key.code;
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						wait = 0;
						break;
					case 8:
						player2Drop = Event.key.code;
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 0;
						break;
					}
				}
				break;
			case Event::MouseMoved:
			{
				Vector2i mousePos = Mouse::getPosition(window);
				Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				// If the mouse hovers a button, colors it
				if (exitButtonImage.getGlobalBounds().contains(mousePosF))
				{
					exitButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					exitButtonImage.setColor(Color(255, 255, 255));
				}
				if (arrowButtonImage.getGlobalBounds().contains(mousePosF))
				{
					arrowButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					arrowButtonImage.setColor(Color(255, 255, 255));
				}
				if (optionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					optionButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					optionButtonImage.setColor(Color(255, 255, 255));
				}
				if (blocksButtonImage.getGlobalBounds().contains(mousePosF))
				{
					blocksButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					blocksButtonImage.setColor(Color(255, 255, 255));
				}
				if (blocksPlayerButtonImage.getGlobalBounds().contains(mousePosF))
				{
					blocksPlayerButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					blocksPlayerButtonImage.setColor(Color(255, 255, 255));
				}
				if (blocksQuestionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					blocksQuestionButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					blocksQuestionButtonImage.setColor(Color(255, 255, 255));
				}
				if (diceButtonImage.getGlobalBounds().contains(mousePosF))
				{
					diceButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					diceButtonImage.setColor(Color(255, 255, 255));
				}
				if (diceQuestionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					diceQuestionButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					diceQuestionButtonImage.setColor(Color(255, 255, 255));
				}
				if (dicePlayerButtonImage.getGlobalBounds().contains(mousePosF))
				{
					dicePlayerButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					dicePlayerButtonImage.setColor(Color(255, 255, 255));
				}
				if (marblesButtonImage.getGlobalBounds().contains(mousePosF))
				{
					marblesButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					marblesButtonImage.setColor(Color(255, 255, 255));
				}
				if (marblesQuestionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					marblesQuestionButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					marblesQuestionButtonImage.setColor(Color(255, 255, 255));
				}
				if (marblesPlayerButtonImage.getGlobalBounds().contains(mousePosF))
				{
					marblesPlayerButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					marblesPlayerButtonImage.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer1Rotate.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer1Rotate.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer1Rotate.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer1Left.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer1Left.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer1Left.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer1Right.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer1Right.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer1Right.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer1Drop.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer1Drop.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer1Drop.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer2Rotate.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer2Rotate.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer2Rotate.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer2Left.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer2Left.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer2Left.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer2Right.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer2Right.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer2Right.setColor(Color(255, 255, 255));
				}
				if (settingsBlockPlayer2Drop.getGlobalBounds().contains(mousePosF))
				{
					settingsBlockPlayer2Drop.setColor(Color(250, 20, 20));
				}
				else
				{
					settingsBlockPlayer2Drop.setColor(Color(255, 255, 255));
				}
				if (volumeButton1.getGlobalBounds().contains(mousePosF))
				{
					volumeButton1.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton1.setColor(Color(255, 255, 255));
				}
				if (volumeButton2.getGlobalBounds().contains(mousePosF))
				{
					volumeButton2.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton2.setColor(Color(255, 255, 255));
				}
				if (volumeButton3.getGlobalBounds().contains(mousePosF))
				{
					volumeButton3.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton3.setColor(Color(255, 255, 255));
				}
				if (volumeButton4.getGlobalBounds().contains(mousePosF))
				{
					volumeButton4.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton4.setColor(Color(255, 255, 255));
				}
				if (volumeButton5.getGlobalBounds().contains(mousePosF))
				{
					volumeButton5.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton5.setColor(Color(255, 255, 255));
				}
				if (volumeButton6.getGlobalBounds().contains(mousePosF))
				{
					volumeButton6.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton6.setColor(Color(255, 255, 255));
				}
				if (volumeButton7.getGlobalBounds().contains(mousePosF))
				{
					volumeButton7.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton7.setColor(Color(255, 255, 255));
				}
				if (volumeButton8.getGlobalBounds().contains(mousePosF))
				{
					volumeButton8.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton8.setColor(Color(255, 255, 255));
				}
				if (volumeButton9.getGlobalBounds().contains(mousePosF))
				{
					volumeButton9.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton9.setColor(Color(255, 255, 255));
				}
				if (volumeButton10.getGlobalBounds().contains(mousePosF))
				{
					volumeButton10.setColor(Color(250, 20, 20));
				}
				else
				{
					volumeButton10.setColor(Color(255, 255, 255));
				}
			}
			break;
			case Event::MouseButtonPressed:
			{
				Vector2i mousePos = Mouse::getPosition(window);
				Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				// If the mouse clicks a button, goes to that game
				if (exitButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						window.close();
						return 0;
					}
					else {
						wind = 1;
						arrowButtonImage.setTexture(rightArrow);
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						std::ofstream stream("games.ini");
						stream << vol << "\n";
						stream << player1Rotate << "\n";
						stream << player1Left << "\n";
						stream << player1Right << "\n";
						stream << player1Drop << "\n";
						stream << player2Rotate << "\n";
						stream << player2Left << "\n";
						stream << player2Right << "\n";
						stream << player2Drop << "\n";
						stream.close();
					}
				}
				if (volumeButton1.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 10;
					}
				}
				if (volumeButton2.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 20;
					}
				}
				if (volumeButton3.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 30;
					}
				}
				if (volumeButton4.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 40;
					}
				}
				if (volumeButton5.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 50;
					}
				}
				if (volumeButton6.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 60;
					}
				}
				if (volumeButton7.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 70;
					}
				}
				if (volumeButton8.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 80;
					}
				}
				if (volumeButton9.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 90;
					}
				}
				if (volumeButton10.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						wait = 0;
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						vol = 100;
					}
				}
				if (optionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						wind = 6;
					}
				}
				if (settingsBlockPlayer1Rotate.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 1;
						settingsBlockPlayer1RotateText.setString(" ");
					}
				}
				if (settingsBlockPlayer1Left.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 2;
						settingsBlockPlayer1LeftText.setString(" ");
					}
				}
				if (settingsBlockPlayer1Right.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 3;
						settingsBlockPlayer1RightText.setString(" ");
					}
				}
				if (settingsBlockPlayer1Drop.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 4;
						settingsBlockPlayer1DropText.setString(" ");
					}
				}
				if (settingsBlockPlayer2Rotate.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 5;
						settingsBlockPlayer2RotateText.setString(" ");
					}
				}
				if (settingsBlockPlayer2Left.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 6;
						settingsBlockPlayer2LeftText.setString(" ");
					}
				}
				if (settingsBlockPlayer2Right.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2DropText.setString(keytotext(player2Drop));
						wait = 7;
						settingsBlockPlayer2RightText.setString(" ");
					}
				}
				if (settingsBlockPlayer2Drop.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 6) {
						settingsBlockPlayer1RotateText.setString(keytotext(player1Rotate));
						settingsBlockPlayer1LeftText.setString(keytotext(player1Left));
						settingsBlockPlayer1RightText.setString(keytotext(player1Right));
						settingsBlockPlayer1DropText.setString(keytotext(player1Drop));
						settingsBlockPlayer2RotateText.setString(keytotext(player2Rotate));
						settingsBlockPlayer2LeftText.setString(keytotext(player2Left));
						settingsBlockPlayer2RightText.setString(keytotext(player2Right));
						wait = 8;
						settingsBlockPlayer2DropText.setString(" ");
					}
				}
				if (arrowButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 3) {
						wind = 4;
						arrowButtonImage.setTexture(leftArrow);
					}
					else if (wind == 4) {
						wind = 3;
						arrowButtonImage.setTexture(rightArrow);
					}
				}
				if (blocksButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						window.close();
						if (blockPlayer == 1) {
							blockssolo(vol, player1Rotate, player1Left, player1Right, player1Drop);
						}
						else {
							blocks(vol, player1Rotate, player1Left, player1Right, player1Drop, player2Rotate, player2Left, player2Right, player2Drop);
						}
					}
				}
				if (blocksQuestionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						wind = 2;
					}
				}
				if (blocksPlayerButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						if (blockPlayer == 1) {
							blocksPlayerButtonImage.setTexture(player2Button);
							blockPlayer = 2;
						}
						else {
							blocksPlayerButtonImage.setTexture(player1Button);
							blockPlayer = 1;
						}
					}
				}
				if (diceButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						window.close();
						if (dicePlayer == 1) {
							diceai(vol);
						}
						else {
							dice(vol);
						}
					}
				}
				if (diceQuestionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						wind = 3;
					}
				}
				if (dicePlayerButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						if (dicePlayer == 1) {
							dicePlayerButtonImage.setTexture(player2Button);
							dicePlayer = 2;
						}
						else {
							dicePlayerButtonImage.setTexture(player1Button);
							dicePlayer = 1;
						}
					}
				}
				if (marblesButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						window.close();
						if (marblesPlayer == 1) {
							marblesAi(vol);
						}
						else {
							marbles(vol);
						}
					}
				}
				if (marblesQuestionButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						wind = 5;
					}
				}
				if (marblesPlayerButtonImage.getGlobalBounds().contains(mousePosF))
				{
					if (wind == 1) {
						if (marblesPlayer == 1) {
							marblesPlayerButtonImage.setTexture(player2Button);
							marblesPlayer = 2;
						}
						else {
							marblesPlayerButtonImage.setTexture(player1Button);
							marblesPlayer = 1;
						}
					}
				}
				break;
			}
			}

			window.clear();
			window.draw(background);
			if (wind == 1) {
				window.draw(blocksButtonImage);
				window.draw(blocksQuestionButtonImage);
				window.draw(blocksPlayerButtonImage);
				window.draw(diceButtonImage);
				window.draw(diceQuestionButtonImage);
				window.draw(dicePlayerButtonImage);
				window.draw(marblesButtonImage);
				window.draw(marblesQuestionButtonImage);
				window.draw(marblesPlayerButtonImage);
				window.draw(optionButtonImage);
			}
			else if (wind == 2) {
				window.draw(blocksHelpImage);
			}
			else if (wind == 3) {
				window.draw(diceHelpImage);
				window.draw(arrowButtonImage);
			}
			else if (wind == 4) {
				window.draw(categoriesHelpImage);
				window.draw(arrowButtonImage);
			}
			else if (wind == 5) {
				window.draw(marblesHelpImage);
			}
			else if (wind == 6) {
				window.draw(settingsMenuImage);
				window.draw(settingsBlockPlayer1Rotate);
				window.draw(settingsBlockPlayer1RotateText);
				window.draw(settingsBlockPlayer1Left);
				window.draw(settingsBlockPlayer1LeftText);
				window.draw(settingsBlockPlayer1Right);
				window.draw(settingsBlockPlayer1RightText);
				window.draw(settingsBlockPlayer1Drop);
				window.draw(settingsBlockPlayer1DropText);
				window.draw(settingsBlockPlayer2Rotate);
				window.draw(settingsBlockPlayer2RotateText);
				window.draw(settingsBlockPlayer2Left);
				window.draw(settingsBlockPlayer2LeftText);
				window.draw(settingsBlockPlayer2Right);
				window.draw(settingsBlockPlayer2RightText);
				window.draw(settingsBlockPlayer2Drop);
				window.draw(settingsBlockPlayer2DropText);
				switch (vol)
				{
				case 10:
					volumeButton1.setColor(Color(255, 20, 20));
					break;
				case 20:
					volumeButton2.setColor(Color(255, 20, 20));
					break;
				case 30:
					volumeButton3.setColor(Color(255, 20, 20));
					break;
				case 40:
					volumeButton4.setColor(Color(255, 20, 20));
					break;
				case 50:
					volumeButton5.setColor(Color(255, 20, 20));
					break;
				case 60:
					volumeButton6.setColor(Color(255, 20, 20));
					break;
				case 70:
					volumeButton7.setColor(Color(255, 20, 20));
					break;
				case 80:
					volumeButton8.setColor(Color(255, 20, 20));
					break;
				case 90:
					volumeButton9.setColor(Color(255, 20, 20));
					break;
				case 100:
					volumeButton10.setColor(Color(255, 20, 20));
					break;
				}
				window.draw(volumeButton1);
				window.draw(volumeButton2);
				window.draw(volumeButton3);
				window.draw(volumeButton4);
				window.draw(volumeButton5);
				window.draw(volumeButton6);
				window.draw(volumeButton7);
				window.draw(volumeButton8);
				window.draw(volumeButton9);
				window.draw(volumeButton10);
			}
			window.draw(exitButtonImage);
			window.display();
		}
	}
}