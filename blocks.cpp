#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "blocks.h"
#include "title.h"
#include <string>
#include <iostream> 

using namespace sf;

const int M = 20;
const int N = 10;
const int O = 4;

int field1[M][N] = { 0 };
int field2[M][N] = { 0 };
int hold1[O][O] = { 0 };
int hold2[O][O] = { 0 };

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

void blocks(int vol, int player1Rotate, int player1Left, int player1Right, int player1Drop, int player2Rotate, int player2Left, int player2Right, int player2Drop) {
	// Creates and initializes all needed variables and sfml components
	bool victory = false, upKey = false, downKey = false, leftKey = false, rightKey = false, wKey = false, aKey = false, sKey = false, dKey = false;
	int points1 = 0, points2 = 0, musicnum = 1 + rand() % 3;
	float tempcount = 60;

	sf::Font font;
	if (!font.loadFromFile("resources/arial.ttf"))
		std::cout << "Can't find the font" << std::endl;

	String musicfile = "blank";
	sf::Music music;
	music.setVolume(vol);
	switch (musicnum) {
	case 1:
		music.openFromFile("resources/SHOP1.ogg");
		break;
	case 2:
		music.openFromFile("resources/TWISTA.ogg");
		break;
	case 3:
		music.openFromFile("resources/PDB1.ogg");
		break;
	}
	music.play();

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

	sf::Text clocktimer;
	clocktimer.setFont(font);
	clocktimer.setStyle(sf::Text::Bold);
	clocktimer.setString(std::to_string(0));
	clocktimer.setPosition(635.0f, 100.0f);
	clocktimer.setFillColor(sf::Color::Black);
	clocktimer.setCharacterSize(24);

	sf::Text clocktext;
	clocktext.setFont(font);
	clocktext.setStyle(sf::Text::Bold);
	clocktext.setString("Time:");
	clocktext.setPosition(545.0f, 100.0f);
	clocktext.setFillColor(sf::Color::Black);
	clocktext.setCharacterSize(24);

	srand(time(0));
	for (int i = M - 1; i > 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			field1[i][j] = 0;
			field2[i][j] = 0;
		}
	}
	for (int i = O - 1; i > 0; i--)
	{
		for (int j = 0; j < O; j++)
		{
			hold1[i][j] = 0;
			hold2[i][j] = 0;
		}
	}

	RenderWindow blocksWindow(VideoMode(1280, 720), "blocks", sf::Style::Titlebar | sf::Style::Close);

	Texture map, bg;
	if (!map.loadFromFile("resources/tiles.png"))
		std::cout << "Can't find the image" << std::endl;
	if (!bg.loadFromFile("resources/blocksbg.png"))
		std::cout << "Can't find the image" << std::endl;

	Sprite s(map), background(bg);

	int dx1 = 0, dx2 = 0; bool rotate1 = 0, rotate2 = 0; int colorNum1 = 1, colorNum2 = 1, colorNum1b = 1, colorNum2b = 1;
	float timer1 = 0, timer2 = 0, delay1 = 0.3, delay2 = 0.3, countdown = 0, intensity = 0;

	Clock clock;

	colorNum1 = 1 + rand() % 7;
	colorNum2 = 1 + rand() % 7;
	int n1 = rand() % 7;
	int n2 = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[n1][i] % 2 + 4;
		a[i].y = figures[n1][i] / 2;
		c[i].x = figures[n2][i] % 2 + 4;
		c[i].y = figures[n2][i] / 2;
	}
	n1 = rand() % 7;
	colorNum1b = 1 + rand() % 7;
	for (int i = 0; i < O; i++) {
		for (int j = 0; j < O; j++) {
			hold1[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) hold1[figures[n2][i] / 2][figures[n2][i] % 2] = colorNum1b;
	n2 = rand() % 7;
	colorNum2b = 1 + rand() % 7;
	for (int i = 0; i < O; i++) {
		for (int j = 0; j < O; j++) {
			hold2[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) hold2[figures[n2][i] / 2][figures[n2][i] % 2] = colorNum2b;

	while (blocksWindow.isOpen() && victory == false)
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer1 += time;
		timer2 += time;
		countdown += time;
		intensity = countdown / 1000;

		if (music.getStatus() == music.Stopped) {
			if ((countdown - tempcount) > 0) {
				int tempnum = musicnum;
				do musicnum = 1 + rand() % 3;
				while (musicnum == tempnum);
				tempcount = countdown + 60;
			}
			switch (musicnum) {
			case 1:
				switch (1 + rand() % 4) {
				case 1:
					musicfile = "resources/SHOP1.ogg";
					break;
				case 2:
					musicfile = "resources/SHOP2.ogg";
					break;
				case 3:
					musicfile = "resources/SHOP3.ogg";
					break;
				case 4:
					musicfile = "resources/SHOP4.ogg";
					break;
				}
				break;
			case 2:
				switch (1 + rand() % 5) {
				case 1:
					musicfile = "resources/TWISTA.ogg";
					break;
				case 2:
					musicfile = "resources/TWISTB.ogg";
					break;
				case 3:
					musicfile = "resources/TWISTC.ogg";
					break;
				case 4:
					musicfile = "resources/TWISTD.ogg";
					break;
				case 5:
					musicfile = "resources/TWISTE.ogg";
					break;
				}
				break;
			case 3:
				switch (1 + rand() % 7) {
				case 1:
					musicfile = "resources/PDB1.ogg";
					break;
				case 2:
					musicfile = "resources/PDB2.ogg";
					break;
				case 3:
					musicfile = "resources/PDB3.ogg";
					break;
				case 4:
					musicfile = "resources/PDB4.ogg";
					break;
				case 5:
					musicfile = "resources/PDB5.ogg";
					break;
				case 6:
					musicfile = "resources/PDB6.ogg";
					break;
				case 7:
					musicfile = "resources/PDB7.ogg";
					break;
				}
				break;
			}
			music.openFromFile(musicfile);
			music.play();
		}

		sf::Event Event;
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
					for (int i = 0; i < O; i++) {
						for (int j = 0; j < O; j++) {
							hold1[i][j] = 0;
							hold2[i][j] = 0;
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
					music.stop();
					blocksWindow.close();
					title();
					return;
				}

				case sf::Event::KeyPressed:
					if (Event.key.code == player1Rotate)
						upKey = true;
					else if (Event.key.code == player1Left)
						leftKey = true;
					else if (Event.key.code == player1Drop)
						downKey = true;
					else if (Event.key.code == player1Right)
						rightKey = true;
					else if (Event.key.code == player2Rotate)
						wKey = true;
					else if (Event.key.code == player2Left)
						aKey = true;
					else if (Event.key.code == player2Drop)
						sKey = true;
					else if (Event.key.code == player2Right)
						dKey = true;
					break;
				case sf::Event::KeyReleased:
					if (Event.key.code == player1Rotate)
						upKey = false;
					else if (Event.key.code == player1Left)
						leftKey = false;
					else if (Event.key.code == player1Drop)
						downKey = false;
					else if (Event.key.code == player1Right)
						rightKey = false;
					else if (Event.key.code == player2Rotate)
						wKey = false;
					else if (Event.key.code == player2Left)
						aKey = false;
					else if (Event.key.code == player2Drop)
						sKey = false;
					else if (Event.key.code == player2Right)
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
		if (downKey && ((0.05 - intensity) > 0.04)) delay1 = (0.05 - intensity);
		else if (downKey && 0.04 < (0.3 - intensity)) delay1 = 0.04;
		else delay1 = (0.3 - intensity);
		if (sKey && ((0.05 - intensity) > 0.04)) delay2 = (0.05 - intensity);
		else if (sKey && 0.04 < (0.3 - intensity)) delay2 = 0.04;
		else delay2 = (0.3 - intensity);

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

				for (int i = 0; i < 4; i++)
				{
					a[i].x = figures[n1][i] % 2 + 4;
					a[i].y = figures[n1][i] / 2 - 1;
				}

				n1 = rand() % 7;
				colorNum1 = colorNum1b;
				colorNum1b = 1 + rand() % 7;
				for (int i = 0; i < O; i++) {
					for (int j = 0; j < O; j++) {
						hold1[i][j] = 0;
					}
				}
				for (int i = 0; i < 4; i++) hold1[figures[n1][i] / 2][figures[n1][i] % 2] = colorNum1b;
			}
			timer1 = 0;
		}
		if (timer2 > delay2)
		{
			for (int i = 0; i < 4; i++) { d[i] = c[i]; c[i].y += 1; }

			if (!check(c, field2))
			{
				for (int i = 0; i < 4; i++) field2[d[i].y][d[i].x] = colorNum2;

				for (int i = 0; i < 4; i++)
				{
					c[i].x = figures[n2][i] % 2 + 4;
					c[i].y = figures[n2][i] / 2 - 1;
				}

				n2 = rand() % 7;
				colorNum2 = colorNum2b;
				colorNum2b = 1 + rand() % 7;
				for (int i = 0; i < O; i++) {
					for (int j = 0; j < O; j++) {
						hold2[i][j] = 0;
					}
				}
				for (int i = 0; i < 4; i++) hold2[figures[n2][i] / 2][figures[n2][i] % 2] = colorNum2b;
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
				music.stop();
				music.openFromFile("resources/SHOP5.ogg");
				music.play();
				victory = true;
			}
		}

		// Default values for movement/rotate/tickrate
		dx1 = 0; rotate1 = 0;
		dx2 = 0; rotate2 = 0;

		// Draw all the sprites
		blocksWindow.clear(Color::White);
		blocksWindow.draw(background);

		// Draws the blocks in the hold
		for (int i = 0; i < O; i++) {
			for (int j = 0; j < O; j++)
			{
				if (hold1[i][j] == 0) continue;
				s.setTextureRect(IntRect(hold1[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(326, 31); //offset
				blocksWindow.draw(s);
			}
			for (int j = 0; j < O; j++)
			{
				if (hold2[i][j] == 0) continue;
				s.setTextureRect(IntRect(hold2[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(835, 31); //offset
				blocksWindow.draw(s);
			}
		}

		// Draws the blocks on the ground
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++)
			{
				if (field1[i][j] == 0) continue;
				s.setTextureRect(IntRect(field1[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(28, 31); //offset
				blocksWindow.draw(s);
			}
			for (int j = 0; j < N; j++)
			{
				if (field2[i][j] == 0) continue;
				s.setTextureRect(IntRect(field2[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(970, 31); //offset
				blocksWindow.draw(s);
			}
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

		clocktimer.setString(std::to_string(countdown));
		blocksWindow.draw(clocktimer);
		blocksWindow.draw(clocktext);
		blocksWindow.draw(text);
		blocksWindow.draw(text2);
		blocksWindow.draw(score1);
		blocksWindow.draw(score2);
		blocksWindow.display();
	}
	while (blocksWindow.isOpen())
	{
		sf::Event Event;
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

		// Draws the blocks in the hold
		for (int i = 0; i < O; i++) {
			for (int j = 0; j < O; j++)
			{
				if (hold1[i][j] == 0) continue;
				s.setTextureRect(IntRect(hold1[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(328, 31); //offset
				blocksWindow.draw(s);
			}
			for (int j = 0; j < O; j++)
			{
				if (hold2[i][j] == 0) continue;
				s.setTextureRect(IntRect(hold2[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(835, 31); //offset
				blocksWindow.draw(s);
			}
		}

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
		blocksWindow.draw(clocktimer);
		blocksWindow.draw(clocktext);
		blocksWindow.draw(text);
		blocksWindow.draw(text2);
		blocksWindow.draw(score1);
		blocksWindow.draw(score2);
		blocksWindow.display();
	}
}
