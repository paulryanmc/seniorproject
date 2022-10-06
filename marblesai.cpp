#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "title.h"
#include <string>
#include <iostream> 

using namespace sf;

void marblesAi(int vol) {

	int p1Marbles[6];
	int p2Marbles[6];
	int p1Rotate[13];
	int p2Rotate[13];
	for (int i = 0; i < 6; i++) {
		p1Marbles[i] = 4;
		p2Marbles[i] = 4;
	}
	for (int i = 0; i < 13; i++) {
		p1Rotate[i] = 0;
		p2Rotate[i] = 0;
	}
	int p1Storage = 0;
	int p2Storage = 0;
	int counter = 0;
	int finals = 0;
	bool change = true;
	int turn = 1;
	int jax = 0;
	bool victory1 = false;
	bool victory2 = false;
	bool victory3 = false;
	int aiturn = 0;
	bool valid = false;

	sf::Music music;
	music.setVolume(vol);
	music.openFromFile("resources/Smooth.ogg");
	music.setLoop(true);
	music.play();

	RenderWindow marblesWindow(VideoMode(1280, 720), "marbles", sf::Style::Titlebar | sf::Style::Close);

	Texture bg, s, rec1, rec2, marb;
	if (!bg.loadFromFile("resources/marblesbg.png"))
		std::cout << "Can't find the image" << std::endl;
	if (!rec1.loadFromFile("resources/p1Rectangle.png"))
		std::cout << "Can't find the image" << std::endl;
	if (!rec2.loadFromFile("resources/p2Rectangle.png"))
		std::cout << "Can't find the image" << std::endl;
	if (!marb.loadFromFile("resources/tilesSmall.png"))
		std::cout << "Can't find the image" << std::endl;

	Sprite background(bg), marbles(marb), p1Rec1(rec1), p1Rec2(rec1), p1Rec3(rec1), p1Rec4(rec1), p1Rec5(rec1), p1Rec6(rec1), p2Rec1(rec2), p2Rec2(rec2), p2Rec3(rec2), p2Rec4(rec2), p2Rec5(rec2), p2Rec6(rec2);
	marbles.setTextureRect(IntRect(67, 0, 14, 14));

	sf::Font font;
	if (!font.loadFromFile("resources/arial.ttf"))
		std::cout << "Can't find the font" << std::endl;

	p1Rec1.setPosition(291, 155);
	p1Rec2.setPosition(397, 22);
	p1Rec3.setPosition(508, 155);
	p1Rec4.setPosition(291, 447);
	p1Rec5.setPosition(397, 579);
	p1Rec6.setPosition(508, 447);
	p2Rec1.setPosition(652, 155);
	p2Rec2.setPosition(761, 22);
	p2Rec3.setPosition(868, 155);
	p2Rec4.setPosition(652, 447);
	p2Rec5.setPosition(761, 579);
	p2Rec6.setPosition(868, 447);

	sf::Text turnText;
	turnText.setFont(font);
	turnText.setStyle(sf::Text::Bold);
	turnText.setOutlineThickness(4);
	turnText.setString("Player 1 Turn");
	turnText.setPosition(540.0f, 10.0f);
	turnText.setFillColor(sf::Color::White);
	turnText.setCharacterSize(24);

	sf::Text p1Text;
	p1Text.setFont(font);
	p1Text.setStyle(sf::Text::Bold);
	p1Text.setOutlineThickness(4);
	p1Text.setString("Player 1");
	p1Text.setPosition(90.0f, 70.0f);
	p1Text.setFillColor(sf::Color::White);
	p1Text.setCharacterSize(24);

	sf::Text p2Text;
	p2Text.setFont(font);
	p2Text.setStyle(sf::Text::Bold);
	p2Text.setOutlineThickness(4);
	p2Text.setString("Player 2");
	p2Text.setPosition(1080.0f, 70.0f);
	p2Text.setFillColor(sf::Color::White);
	p2Text.setCharacterSize(24);

	sf::Text p1Score;
	p1Score.setFont(font);
	p1Score.setStyle(sf::Text::Bold);
	p1Score.setOutlineThickness(4);
	p1Score.setString(std::to_string(p1Storage));
	p1Score.setPosition(140.0f, 620.0f);
	p1Score.setFillColor(sf::Color::White);
	p1Score.setCharacterSize(24);

	sf::Text p2Score;
	p2Score.setFont(font);
	p2Score.setStyle(sf::Text::Bold);
	p2Score.setOutlineThickness(4);
	p2Score.setString(std::to_string(p2Storage));
	p2Score.setPosition(1120.0f, 620.0f);
	p2Score.setFillColor(sf::Color::White);
	p2Score.setCharacterSize(24);


	while (marblesWindow.isOpen())
	{
		if (turn == 2 && victory3 == false) {
			do {
				aiturn = rand() % 6;
				if (p2Marbles[aiturn] > 0) {
					valid = true;
					if (p2Marbles[aiturn] < 3 &&(rand() % 10) > 4) {
						valid = false;
					}
				}
			} while (!valid);
			switch (aiturn) {
			case 0:
				turn = 1;
				turnText.setString("Player 1 Turn");
				jax = 0;
				if (p2Marbles[0] == 10) {
					turn = 2;
					turnText.setString("Player 2 Turn");
				}
				for (int i = 0; i < p2Marbles[0]; i++) {
					jax++;
					if (jax == 13)
						jax -= 13;
					p2Rotate[jax]++;
					finals = jax;
				}
				p2Marbles[0] = 0;
				change = true;
				counter = 2;
				break;
			case 1:
				turn = 1;
				turnText.setString("Player 1 Turn");
				jax = 12;
				if (p2Marbles[1] == 11) {
					turn = 2;
					turnText.setString("Player 2 Turn");
				}
				for (int i = 0; i < p2Marbles[1]; i++) {
					jax++;
					if (jax == 13)
						jax -= 13;
					p2Rotate[jax]++;
					finals = jax;
				}
				p2Marbles[1] = 0;
				change = true;
				counter = 2;
				break;
			case 2:
				turn = 1;
				turnText.setString("Player 1 Turn");
				jax = 11;
				if (p2Marbles[2] == 12) {
					turn = 2;
					turnText.setString("Player 2 Turn");
				}
				for (int i = 0; i < p2Marbles[2]; i++) {
					jax++;
					if (jax == 13)
						jax -= 13;
					p2Rotate[jax]++;
					finals = jax;
				}
				p2Marbles[2] = 0;
				change = true;
				counter = 2;
				break;
			case 3:
				turn = 1;
				turnText.setString("Player 1 Turn");
				jax = 7;
				if (p2Marbles[3] == 3) {
					turn = 2;
					turnText.setString("Player 2 Turn");
				}
				for (int i = 0; i < p2Marbles[3]; i++) {
					jax++;
					if (jax == 13)
						jax -= 13;
					p2Rotate[jax]++;
					finals = jax;
				}
				p2Marbles[3] = 0;
				change = true;
				counter = 2;
				break;
			case 4:
				turn = 1;
				turnText.setString("Player 1 Turn");
				jax = 8;
				if (p2Marbles[4] == 2) {
					turn = 2;
					turnText.setString("Player 2 Turn");
				}
				for (int i = 0; i < p2Marbles[4]; i++) {
					jax++;
					if (jax == 13)
						jax -= 13;
					p2Rotate[jax]++;
					finals = jax;
				}
				p2Marbles[4] = 0;
				change = true;
				counter = 2;
				break;
			case 5:
				turn = 1;
				turnText.setString("Player 1 Turn");
				jax = 9;
				if (p2Marbles[5] == 1) {
					turn = 2;
					turnText.setString("Player 2 Turn");
				}
				for (int i = 0; i < p2Marbles[5]; i++) {
					jax++;
					if (jax == 13)
						jax -= 13;
					p2Rotate[jax]++;
					finals = jax;
				}
				p2Marbles[5] = 0;
				change = true;
				counter = 2;
				break;
			}
		}

		Event Event;
		while (marblesWindow.pollEvent(Event))
		{
			switch (Event.type) {
			case Event::Closed:
				music.stop();
				marblesWindow.close();
				title();
				break;
			case Event::MouseMoved:
			{
				Vector2i mousePos = Mouse::getPosition(marblesWindow);
				Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

			}
			break;
			case Event::MouseButtonPressed:
			{
				Vector2i mousePos = Mouse::getPosition(marblesWindow);
				Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
				if (p1Rec1.getGlobalBounds().contains(mousePosF) && p1Marbles[0] > 0 && turn == 1 && victory3 == false) {
					turn = 2;
					turnText.setString("Player 2 Turn");
					jax = 0;
					if (p1Marbles[0] == 1) {
						turn = 1;
						turnText.setString("Player 1 Turn");
					}
					for (int i = 0; i < p1Marbles[0]; i++) {
						jax++;
						if (jax == 13)
							jax -= 13;
						p1Rotate[jax]++;
						finals = jax;
					}
					p1Marbles[0] = 0;
					change = true;
					counter = 1;

				}
				if (p1Rec2.getGlobalBounds().contains(mousePosF) && p1Marbles[1] > 0 && turn == 1 && victory3 == false) {
					turn = 2;
					turnText.setString("Player 2 Turn");
					jax = 12;
					if (p1Marbles[1] == 2) {
						turn = 1;
						turnText.setString("Player 1 Turn");
					}
					for (int i = 0; i < p1Marbles[1]; i++) {
						jax++;
						if (jax == 13)
							jax -= 13;
						p1Rotate[jax]++;
						finals = jax;
					}
					p1Marbles[1] = 0;
					change = true;
					counter = 1;

				}
				if (p1Rec3.getGlobalBounds().contains(mousePosF) && p1Marbles[2] > 0 && turn == 1 && victory3 == false) {
					turn = 2;
					turnText.setString("Player 2 Turn");
					jax = 11;
					if (p1Marbles[2] == 3) {
						turn = 1;
						turnText.setString("Player 1 Turn");
					}
					for (int i = 0; i < p1Marbles[2]; i++) {
						jax++;
						if (jax == 13)
							jax -= 13;
						p1Rotate[jax]++;
						finals = jax;
					}
					p1Marbles[2] = 0;
					change = true;
					counter = 1;

				}
				if (p1Rec4.getGlobalBounds().contains(mousePosF) && p1Marbles[3] > 0 && turn == 1 && victory3 == false) {
					turn = 2;
					turnText.setString("Player 2 Turn");
					jax = 2;
					if (p1Marbles[3] == 12) {
						turn = 1;
						turnText.setString("Player 1 Turn");
					}
					for (int i = 0; i < p1Marbles[3]; i++) {
						jax++;
						if (jax == 13)
							jax -= 13;
						p1Rotate[jax]++;
						finals = jax;
					}
					p1Marbles[3] = 0;
					change = true;
					counter = 1;

				}
				if (p1Rec5.getGlobalBounds().contains(mousePosF) && p1Marbles[4] > 0 && turn == 1 && victory3 == false) {
					turn = 2;
					turnText.setString("Player 2 Turn");
					jax = 3;
					if (p1Marbles[4] == 11) {
						turn = 1;
						turnText.setString("Player 1 Turn");
					}
					for (int i = 0; i < p1Marbles[4]; i++) {
						jax++;
						if (jax == 13)
							jax -= 13;
						p1Rotate[jax]++;
						finals = jax;
					}
					p1Marbles[4] = 0;
					change = true;
					counter = 1;

				}
				if (p1Rec6.getGlobalBounds().contains(mousePosF) && p1Marbles[5] > 0 && turn == 1 && victory3 == false) {
					turn = 2;
					turnText.setString("Player 2 Turn");
					jax = 4;
					if (p1Marbles[5] == 10) {
						turn = 1;
						turnText.setString("Player 1 Turn");
					}
					for (int i = 0; i < p1Marbles[5]; i++) {
						jax++;
						if (jax == 13)
							jax -= 13;
						p1Rotate[jax]++;
						finals = jax;
					}
					p1Marbles[5] = 0;
					change = true;
					counter = 1;

				}
				break;
			}
			}
		}

		if (counter == 1) {
			for (int i = 0; i < 13; i++) {
				if (p1Rotate[i] > 0) {
					switch (i) {
					case 0:
						p1Marbles[0]++;
						p1Rotate[i]--;
						break;
					case 1:
						p1Storage++;
						p1Rotate[i]--;
						break;
					case 2:
						p1Marbles[3]++;
						p1Rotate[i]--;
						break;
					case 3:
						p1Marbles[4]++;
						p1Rotate[i]--;
						break;
					case 4:
						p1Marbles[5]++;
						p1Rotate[i]--;
						break;
					case 5:
						p2Marbles[3]++;
						p1Rotate[i]--;
						break;
					case 6:
						p2Marbles[4]++;
						p1Rotate[i]--;
						break;
					case 7:
						p2Marbles[5]++;
						p1Rotate[i]--;
						break;
					case 8:
						p2Marbles[2]++;
						p1Rotate[i]--;
						break;
					case 9:
						p2Marbles[1]++;
						p1Rotate[i]--;
						break;
					case 10:
						p2Marbles[0]++;
						p1Rotate[i]--;
						break;
					case 11:
						p1Marbles[2]++;
						p1Rotate[i]--;
						break;
					case 12:
						p1Marbles[1]++;
						p1Rotate[i]--;
						break;
					}
				}
				counter = 0;
			}
			switch (finals) {
			case 0:
				if (p1Marbles[0] == 1) {
					p1Marbles[0]--;
					p1Storage++;
					p1Storage += p2Marbles[2];
					p2Marbles[2] = 0;
					break;
				}
			case 2:
				if (p1Marbles[3] == 1) {
					p1Marbles[3]--;
					p1Storage++;
					p1Storage += p2Marbles[5];
					p2Marbles[5] = 0;
					break;
				}
			case 3:
				if (p1Marbles[4] == 1) {
					p1Marbles[4]--;
					p1Storage++;
					p1Storage += p2Marbles[4];
					p2Marbles[4] = 0;
					break;
				}
			case 4:
				if (p1Marbles[5] == 1) {
					p1Marbles[5]--;
					p1Storage++;
					p1Storage += p2Marbles[3];
					p2Marbles[3] = 0;
					break;
				}
			case 11:
				if (p1Marbles[2] == 1) {
					p1Marbles[2]--;
					p1Storage++;
					p1Storage += p2Marbles[0];
					p2Marbles[0] = 0;
					break;
				}
			case 12:
				if (p1Marbles[1] == 1) {
					p1Marbles[1]--;
					p1Storage++;
					p1Storage += p2Marbles[1];
					p2Marbles[1] = 0;
					break;
				}
			default:
				break;
			}

		}
		else if (counter == 2) {
			for (int i = 0; i < 13; i++) {
				if (p2Rotate[i] > 0) {
					switch (i) {
					case 0:
						p2Marbles[0]++;
						p2Rotate[i]--;
						break;
					case 1:
						p1Marbles[2]++;
						p2Rotate[i]--;
						break;
					case 2:
						p1Marbles[1]++;
						p2Rotate[i]--;
						break;
					case 3:
						p1Marbles[0]++;
						p2Rotate[i]--;
						break;
					case 4:
						p1Marbles[3]++;
						p2Rotate[i]--;
						break;
					case 5:
						p1Marbles[4]++;
						p2Rotate[i]--;
						break;
					case 6:
						p1Marbles[5]++;
						p2Rotate[i]--;
						break;
					case 7:
						p2Marbles[3]++;
						p2Rotate[i]--;
						break;
					case 8:
						p2Marbles[4]++;
						p2Rotate[i]--;
						break;
					case 9:
						p2Marbles[5]++;
						p2Rotate[i]--;
						break;
					case 10:
						p2Storage++;
						p2Rotate[i]--;
						break;
					case 11:
						p2Marbles[2]++;
						p2Rotate[i]--;
						break;
					case 12:
						p2Marbles[1]++;
						p2Rotate[i]--;
						break;
					}
				}
				counter = 0;
			}
			switch (finals) {
			case 0:
				if (p2Marbles[0] == 1) {
					p2Marbles[0]--;
					p2Storage++;
					p2Storage += p1Marbles[2];
					p1Marbles[2] = 0;
					break;
				}
			case 7:
				if (p2Marbles[3] == 1) {
					p2Marbles[3]--;
					p2Storage++;
					p2Storage += p1Marbles[5];
					p1Marbles[5] = 0;
					break;
				}
			case 8:
				if (p2Marbles[4] == 1) {
					p2Marbles[4]--;
					p2Storage++;
					p2Storage += p1Marbles[4];
					p1Marbles[4] = 0;
					break;
				}
			case 9:
				if (p2Marbles[5] == 1) {
					p2Marbles[5]--;
					p2Storage++;
					p2Storage += p1Marbles[3];
					p1Marbles[3] = 0;
					break;
				}
			case 11:
				if (p2Marbles[2] == 1) {
					p2Marbles[2]--;
					p2Storage++;
					p2Storage += p1Marbles[0];
					p1Marbles[0] = 0;
					break;
				}
			case 12:
				if (p2Marbles[1] == 1) {
					p2Marbles[1]--;
					p2Storage++;
					p2Storage += p1Marbles[1];
					p1Marbles[1] = 0;
					break;
				}
			default:
				break;
			}

		}
		if (change == true) {
			victory1 = true;
			victory2 = true;
			for (int x = 0; x < 6; x++) {
				if (p1Marbles[x] != 0) {
					victory1 = false;
				}
				if (p2Marbles[x] != 0) {
					victory2 = false;
				}
			}
			if (victory1 || victory2) {
				victory3 = true;
				if (p1Storage > p2Storage) {
					turnText.setString("Player 1 Wins!");
				}
				else if (p1Storage < p2Storage) {
					turnText.setString("Player 2 Wins!");
				}
				else {
					turnText.setString("Tie!");
				}
			}
			marblesWindow.clear();
			marblesWindow.draw(background);
			marblesWindow.draw(p1Text);
			marblesWindow.draw(p2Text);
			marblesWindow.draw(turnText);
			p1Score.setString(std::to_string(p1Storage));
			p2Score.setString(std::to_string(p2Storage));
			marblesWindow.draw(p1Score);
			marblesWindow.draw(p2Score);
			marblesWindow.draw(p1Rec1);
			marblesWindow.draw(p1Rec2);
			marblesWindow.draw(p1Rec3);
			marblesWindow.draw(p1Rec4);
			marblesWindow.draw(p1Rec5);
			marblesWindow.draw(p1Rec6);
			marblesWindow.draw(p2Rec1);
			marblesWindow.draw(p2Rec2);
			marblesWindow.draw(p2Rec3);
			marblesWindow.draw(p2Rec4);
			marblesWindow.draw(p2Rec5);
			marblesWindow.draw(p2Rec6);
			if (p1Marbles[0] > 0) {
				for (int i = 0; i < p1Marbles[0]; i++) {
					marbles.setPosition(300 + rand() % 90, 165 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p1Marbles[1] > 0) {
				for (int i = 0; i < p1Marbles[1]; i++) {
					marbles.setPosition(410 + rand() % 90, 32 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p1Marbles[2] > 0) {
				for (int i = 0; i < p1Marbles[2]; i++) {
					marbles.setPosition(518 + rand() % 90, 165 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p1Marbles[3] > 0) {
				for (int i = 0; i < p1Marbles[3]; i++) {
					marbles.setPosition(300 + rand() % 90, 460 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p1Marbles[4] > 0) {
				for (int i = 0; i < p1Marbles[4]; i++) {
					marbles.setPosition(410 + rand() % 90, 590 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p1Marbles[5] > 0) {
				for (int i = 0; i < p1Marbles[5]; i++) {
					marbles.setPosition(518 + rand() % 90, 460 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p2Marbles[0] > 0) {
				for (int i = 0; i < p2Marbles[0]; i++) {
					marbles.setPosition(660 + rand() % 90, 165 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p2Marbles[1] > 0) {
				for (int i = 0; i < p2Marbles[1]; i++) {
					marbles.setPosition(771 + rand() % 90, 32 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p2Marbles[2] > 0) {
				for (int i = 0; i < p2Marbles[2]; i++) {
					marbles.setPosition(878 + rand() % 90, 165 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p2Marbles[3] > 0) {
				for (int i = 0; i < p2Marbles[3]; i++) {
					marbles.setPosition(662 + rand() % 90, 457 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p2Marbles[4] > 0) {
				for (int i = 0; i < p2Marbles[4]; i++) {
					marbles.setPosition(771 + rand() % 90, 590 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p2Marbles[5] > 0) {
				for (int i = 0; i < p2Marbles[5]; i++) {
					marbles.setPosition(878 + rand() % 90, 457 + rand() % 90);
					marblesWindow.draw(marbles);
				}
			}
			if (p1Storage > 0) {
				for (int i = 0; i < p1Storage; i++) {
					marbles.setPosition(50 + rand() % 200, 130 + rand() % 400);
					marblesWindow.draw(marbles);
				}
			}
			if (p2Storage > 0) {
				for (int i = 0; i < p2Storage; i++) {
					marbles.setPosition(1020 + rand() % 200, 130 + rand() % 400);
					marblesWindow.draw(marbles);
				}
			}
			change = false;
			marblesWindow.display();
		}
	}
}