#include <SFML/Graphics.hpp>
#include <time.h>
#include "blocks.h"
#include "dice.h"
#include "diceai.h"
#include "title.h"
#include "marbles.h"
#include "marblesai.h"
#include <string>
#include <iostream> 

using namespace sf;

int title()
{
	// Creates and initializes all needed variables and sfml components
	RenderWindow window(VideoMode(1280, 720), "title", sf::Style::Titlebar | sf::Style::Close);

	Texture bg;
	if (!bg.loadFromFile("resources/titlebg.png"))
		std::cout << "Can't find the image" << std::endl;

	Sprite background(bg);

	sf::Texture blocksButton;
	sf::Sprite blocksButtonImage;
	if (!blocksButton.loadFromFile("resources/Blocks.png"))
		std::cout << "Can't find the image" << std::endl;
	blocksButtonImage.setPosition(520.0f, 170.0f);
	float blocksButtonWidth = blocksButtonImage.getLocalBounds().width;
	float blocksButtonHeight = blocksButtonImage.getLocalBounds().height;
	blocksButtonImage.setTexture(blocksButton);

	sf::Texture diceButton;
	sf::Sprite diceButtonImage;
	if (!diceButton.loadFromFile("resources/Dice.png"))
		std::cout << "Can't find the image" << std::endl;
	diceButtonImage.setPosition(520.0f, 310.0f);
	float diceButtonWidth = diceButtonImage.getLocalBounds().width;
	float diceButtonHeight = diceButtonImage.getLocalBounds().height;
	diceButtonImage.setTexture(diceButton);

	sf::Texture marblesButton;
	sf::Sprite marblesButtonImage;
	if (!marblesButton.loadFromFile("resources/Marbles.png"))
		std::cout << "Can't find the image" << std::endl;
	marblesButtonImage.setPosition(520.0f, 450.0f);
	float marblsButtonWidth = marblesButtonImage.getLocalBounds().width;
	float marblesButtonHeight = marblesButtonImage.getLocalBounds().height;
	marblesButtonImage.setTexture(marblesButton);

	sf::Texture exitButton;
	sf::Sprite exitButtonImage;
	if (!exitButton.loadFromFile("resources/Exit.png"))
		std::cout << "Can't find the image" << std::endl;
	exitButtonImage.setPosition(520.0f, 590.0f);
	float exitButtonWidth = exitButtonImage.getLocalBounds().width;
	float exitButtonHeight = exitButtonImage.getLocalBounds().height;
	exitButtonImage.setTexture(exitButton);

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
				if (blocksButtonImage.getGlobalBounds().contains(mousePosF))
				{
					blocksButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					blocksButtonImage.setColor(Color(255, 255, 255));
				}
				if (diceButtonImage.getGlobalBounds().contains(mousePosF))
				{
					diceButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					diceButtonImage.setColor(Color(255, 255, 255));
				}
				if (marblesButtonImage.getGlobalBounds().contains(mousePosF))
				{
					marblesButtonImage.setColor(Color(250, 20, 20));
				}
				else
				{
					marblesButtonImage.setColor(Color(255, 255, 255));
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
					window.close();
					return 0;
				}
				if (blocksButtonImage.getGlobalBounds().contains(mousePosF))
				{
					window.close();
					blocks();
				}
				if (diceButtonImage.getGlobalBounds().contains(mousePosF))
				{
					window.close();
					diceai();
				}
				if (marblesButtonImage.getGlobalBounds().contains(mousePosF))
				{
					window.close();
					marblesAi();
				}
				break;
			}
			}
			window.clear();
			window.draw(background);
			window.draw(blocksButtonImage);
			window.draw(diceButtonImage);
			window.draw(marblesButtonImage);
			window.draw(exitButtonImage);
			window.display();
		}
	}
}