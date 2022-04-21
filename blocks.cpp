#include <SFML/Graphics.hpp>
#include <time.h>
#include "blocks.h"
#include "title.h"
#include <string>
#include <iostream> 

using namespace sf;

const int M = 20;
const int N = 10;

int field1[M][N] = { 0 };
int field2[M][N] = { 0 };

struct Point
{
	int x, y;
} a[4], b[4], c[4], d[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check(Point z[], int field[M][N])
{
	for (int i = 0; i < 4; i++)
		if (z[i].x < 0 || z[i].x >= N || z[i].y >= M) return 0;
		else if (field[z[i].y][z[i].x]) return 0;

	return 1;
};

void blocks() {
	// Creates and initializes all needed variables and sfml components
	bool victory = false, upKey = false, downKey = false, leftKey = false, rightKey = false, wKey = false, aKey = false, sKey = false, dKey = false;
	int points1 = 0, points2 = 0;
	sf::Font font;
	if (!font.loadFromFile("resources/arial.ttf"))
		std::cout << "Can't find the font" << std::endl;

	sf::Text winnerText;
	winnerText.setFont(font);
	winnerText.setStyle(sf::Text::Bold);
	winnerText.setString("Game!");
	winnerText.setPosition(550.0f, 360.0f);
	winnerText.setFillColor(sf::Color::Black);
	winnerText.setCharacterSize(40);

	sf::Text text;
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setString("Score:");
	text.setPosition(40.0f, 590.0f);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(24);

	sf::Text text2;
	text2.setFont(font);
	text2.setStyle(sf::Text::Bold);
	text2.setString("Score:");
	text2.setPosition(1135.0f, 590.0f);
	text2.setFillColor(sf::Color::Black);
	text2.setCharacterSize(24);

	sf::Text score1;
	score1.setFont(font);
	score1.setStyle(sf::Text::Bold);
	score1.setString(std::to_string(points1));
	score1.setPosition(120.0f, 590.0f);
	score1.setFillColor(sf::Color::Black);
	score1.setCharacterSize(24);

	sf::Text score2;
	score2.setFont(font);
	score2.setStyle(sf::Text::Bold);
	score2.setString(std::to_string(points2));
	score2.setPosition(1215.0f, 590.0f);
	score2.setFillColor(sf::Color::Black);
	score2.setCharacterSize(24);

	srand(time(0));
	for (int i = M - 1; i > 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			field1[i][j] = 0;
			field2[i][j] = 0;
		}
	}

	RenderWindow blocksWindow(VideoMode(1280, 720), "blocks", sf::Style::Titlebar | sf::Style::Close);

	Texture map, bg;
	if (!map.loadFromFile("resources/tiles.png"))
		std::cout << "Can't find the image" << std::endl;
	if (!bg.loadFromFile("resources/blocksbg.png"))
		std::cout << "Can't find the image" << std::endl;

	Sprite s(map), background(bg);

	int dx1 = 0, dx2 = 0; bool rotate1 = 0, rotate2 = 0; int colorNum1 = 1, colorNum2 = 1;
	float timer1 = 0, timer2 = 0, delay1 = 0.3, delay2 = 0.3;

	Clock clock;

	colorNum1 = 1 + rand() % 7;
	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n][i] % 2;
		a[i].y = figures[n][i] / 2;
		c[i].x = figures[n][i] % 2;
		c[i].y = figures[n][i] / 2;
	}

	while (blocksWindow.isOpen() && victory == false)
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer1 += time;
		timer2 += time;

		Event Event;
		while (blocksWindow.pollEvent(Event))
		{
			switch (Event.type) {
				// Resets all variables on game close
				case sf::Event::Closed: {
					timer1 = 0;
					timer2 = 0;
					for (int i = 0; i < M; i++) {
						for (int j = 0; j < N; j++) {
							field1[i][j] = 0;
							field2[i][j] = 0;
						}
					}
					for (int i = 0; i < 4; i++) {
						a[i].x = 0;
						b[i].x = 0;
						a[i].y = 0;
						b[i].y = 0;
						c[i].x = 0;
						d[i].x = 0;
						c[i].y = 0;
						d[i].y = 0;
					}
					points1 = 0;
					points2 = 0;
					blocksWindow.close();
					title();
					return;
				}

				case sf::Event::KeyPressed:
					if (Event.key.code == sf::Keyboard::Up)
						upKey = true;
					else if (Event.key.code == sf::Keyboard::Left)
						leftKey = true;
					else if (Event.key.code == sf::Keyboard::Down)
						downKey = true;
					else if (Event.key.code == sf::Keyboard::Right)
						rightKey = true;
					else if (Event.key.code == sf::Keyboard::W)
						wKey = true;
					else if (Event.key.code == sf::Keyboard::A)
						aKey = true;
					else if (Event.key.code == sf::Keyboard::S)
						sKey = true;
					else if (Event.key.code == sf::Keyboard::D)
						dKey = true;
					break;
				case sf::Event::KeyReleased:
					if (Event.key.code == sf::Keyboard::Up)
						upKey = false;
					else if (Event.key.code == sf::Keyboard::Left)
						leftKey = false;
					else if (Event.key.code == sf::Keyboard::Down)
						downKey = false;
					else if (Event.key.code == sf::Keyboard::Right)
						rightKey = false;
					else if (Event.key.code == sf::Keyboard::W)
						wKey = false;
					else if (Event.key.code == sf::Keyboard::A)
						aKey = false;
					else if (Event.key.code == sf::Keyboard::S)
						sKey = false;
					else if (Event.key.code == sf::Keyboard::D)
						dKey = false;
					break;
				default:
					break;
			}
		}

		// Movement controls
		if (upKey) {
			rotate1 = true;
			upKey = false;
		}
		if (leftKey) {
			dx1 = -1;
			leftKey = false;
		}
		if (rightKey) {
			dx1 = 1;
			rightKey = false;
		}
		if (wKey) {
			rotate2 = true;
			wKey = false;
		}
		if (aKey) {
			dx2 = -1;
			aKey = false;
		}
		if (dKey) {
			dx2 = 1;
			dKey = false;
		}
		// Speeds the game up if down is held
		if (downKey) delay1 = 0.05;
		if (sKey) delay2 = 0.05;

		// Moves the blocks
		for (int i = 0; i < 4; i++) {
			b[i] = a[i]; a[i].x += dx1; 
			d[i] = c[i]; c[i].x += dx2;
		}
		if (!check(a, field1)) for (int i = 0; i < 4; i++) a[i] = b[i];
		if (!check(c, field2)) for (int i = 0; i < 4; i++) c[i] = d[i];

		// Rotates the blocks
		if (rotate1)
		{
			Point p = a[1]; // < Center the block rotates around
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check(a, field1)) for (int i = 0; i < 4; i++) a[i] = b[i];
		}
		if (rotate2)
		{
			Point p = c[1]; // < Center the block rotates around
			for (int i = 0; i < 4; i++)
			{
				int x = c[i].y - p.y;
				int y = c[i].x - p.x;
				c[i].x = p.x - x;
				c[i].y = p.y + y;
			}
			if (!check(c, field2)) for (int i = 0; i < 4; i++) c[i] = d[i];
		}

		// Tick system
		if (timer1 > delay1)
		{
			for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }

			if (!check(a, field1))
			{
				for (int i = 0; i < 4; i++) field1[b[i].y][b[i].x] = colorNum1;

				colorNum1 = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			timer1 = 0;
		}
		if (timer2 > delay2)
		{
			for (int i = 0; i < 4; i++) { d[i] = c[i]; c[i].y += 1; }

			if (!check(c, field2))
			{
				for (int i = 0; i < 4; i++) field2[d[i].y][d[i].x] = colorNum2;

				colorNum2 = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					c[i].x = figures[n][i] % 2;
					c[i].y = figures[n][i] / 2;
				}
			}

			timer2 = 0;
		}

		// check lines
		int k = M - 1;
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field1[i][j]) count++;
				field1[k][j] = field1[i][j];
			}
			if (count < N) {
				k--;
			}
			else {
				points1++;
				score1.setString(std::to_string(points1));
			}
		}
		k = M - 1;
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field2[i][j]) count++;
				field2[k][j] = field2[i][j];
			}
			if (count < N) {
				k--;
			}
			else {
				points2++;
				score2.setString(std::to_string(points2));
			}
		}

		for (int j = 0; j < N; j++)
		{
			if (field1[0][j] || field2[0][j]) {
				if (points1 > points2) {
					winnerText.setString("Player 1 wins!");
				}
				else if (points1 < points2) {
					winnerText.setString("Player 2 wins!");
				}
				else {
					winnerText.setString("Tie!");
				}
				victory = true;
			}
		}

		// Default values for movement/rotate/tickrate
		dx1 = 0; rotate1 = 0; delay1 = 0.3;
		dx2 = 0; rotate2 = 0; delay2 = 0.3;

		// Draw all the sprites
		blocksWindow.clear(Color::White);
		blocksWindow.draw(background);

		// Draws the blocks on the ground
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field1[i][j] == 0) continue;
				s.setTextureRect(IntRect(field1[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(28, 31); //offset
				blocksWindow.draw(s);
			}
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field2[i][j] == 0) continue;
				s.setTextureRect(IntRect(field2[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(970, 31); //offset
				blocksWindow.draw(s);
			}

		// Draws the blocks in the air
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum1 * 27, 0, 27, 27));
			s.setPosition(a[i].x * 27, a[i].y * 27);
			s.move(28, 31); //offset
			blocksWindow.draw(s);
			s.setTextureRect(IntRect(colorNum2 * 27, 0, 27, 27));
			s.setPosition(c[i].x * 27, c[i].y * 27);
			s.move(970, 31); //offset
			blocksWindow.draw(s);
		}

		blocksWindow.draw(text);
		blocksWindow.draw(text2);
		blocksWindow.draw(score1);
		blocksWindow.draw(score2);
		blocksWindow.display();
	}
	while (blocksWindow.isOpen())
	{
		Event Event;
		while (blocksWindow.pollEvent(Event))
		{
			// Resets all variables on game close
			if (Event.type == Event::Closed) {
				timer1 = 0;
				timer2 = 0;
				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++) {
						field1[i][j] = 0;
						field2[i][j] = 0;
					}
				}
				for (int i = 0; i < 4; i++) {
					a[i].x = 0;
					b[i].x = 0;
					a[i].y = 0;
					b[i].y = 0;
					c[i].x = 0;
					d[i].x = 0;
					c[i].y = 0;
					d[i].y = 0;
				}
				points1 = 0;
				points2 = 0;
				blocksWindow.close();
				title();
				return;
			}
		}
		// Draw all the sprites
		blocksWindow.clear(Color::White);
		blocksWindow.draw(background);

		// Draws the blocks on the ground
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field1[i][j] == 0) continue;
				s.setTextureRect(IntRect(field1[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(28, 31); //offset
				blocksWindow.draw(s);
			}
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field2[i][j] == 0) continue;
				s.setTextureRect(IntRect(field2[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(970, 31); //offset
				blocksWindow.draw(s);
			}

		// Draws the blocks in the air
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum1 * 27, 0, 27, 27));
			s.setPosition(a[i].x * 27, a[i].y * 27);
			s.move(28, 31); //offset
			blocksWindow.draw(s);
			s.setTextureRect(IntRect(colorNum2 * 27, 0, 27, 27));
			s.setPosition(c[i].x * 27, c[i].y * 27);
			s.move(970, 31); //offset
			blocksWindow.draw(s);
		}

		blocksWindow.draw(winnerText);
		blocksWindow.draw(text);
		blocksWindow.draw(text2);
		blocksWindow.draw(score1);
		blocksWindow.draw(score2);
		blocksWindow.display();
	}
}
