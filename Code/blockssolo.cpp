#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "blockssolo.h"
#include "title.h"
#include <string>
#include <iostream> 

using namespace sf;

const int M = 20;
const int N = 10;
const int O = 4;

int field3[M][N] = { 0 };
int hold3[O][O] = { 0 };

struct Point
{
	int x, y;
} e[4], f[4];

int figures2[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check2(Point z[], int field[M][N])
{
	for (int i = 0; i < 4; i++)
		if (z[i].x < 0 || z[i].x >= N || z[i].y >= M) return 0;
		else if (field[z[i].y][z[i].x]) return 0;

	return 1;
};

void blockssolo(int vol, int player1Rotate, int player1Left, int player1Right, int player1Drop) {
	// Creates and initializes all needed variables and sfml components
	bool victory = false, upKey = false, downKey = false, leftKey = false, rightKey = false;
	int points = 0, musicnum = 1 + rand() % 3;
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
	winnerText.setPosition(890.0f, 360.0f);
	winnerText.setFillColor(sf::Color::Black);
	winnerText.setCharacterSize(40);

	sf::Text text;
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setString("Score:");
	text.setPosition(610.0f, 590.0f);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(24);

	sf::Text score;
	score.setFont(font);
	score.setStyle(sf::Text::Bold);
	score.setString(std::to_string(points));
	score.setPosition(690.0f, 590.0f);
	score.setFillColor(sf::Color::Black);
	score.setCharacterSize(24);

	sf::Text clocktimer;
	clocktimer.setFont(font);
	clocktimer.setStyle(sf::Text::Bold);
	clocktimer.setString(std::to_string(0));
	clocktimer.setPosition(910.0f, 100.0f);
	clocktimer.setFillColor(sf::Color::Black);
	clocktimer.setCharacterSize(24);

	sf::Text clocktext;
	clocktext.setFont(font);
	clocktext.setStyle(sf::Text::Bold);
	clocktext.setString("Time:");
	clocktext.setPosition(820.0f, 100.0f);
	clocktext.setFillColor(sf::Color::Black);
	clocktext.setCharacterSize(24);

	srand(time(0));
	for (int i = M - 1; i > 0; i--)
	{
		for (int j = 0; j < N; j++)
		{
			field3[i][j] = 0;
		}
	}
	for (int i = O - 1; i > 0; i--)
	{
		for (int j = 0; j < O; j++)
		{
			hold3[i][j] = 0;
		}
	}

	RenderWindow blocksWindow(VideoMode(1280, 720), "blocks", sf::Style::Titlebar | sf::Style::Close);

	Texture map, bg;
	if (!map.loadFromFile("resources/tiles.png"))
		std::cout << "Can't find the image" << std::endl;
	if (!bg.loadFromFile("resources/blockssp.png"))
		std::cout << "Can't find the image" << std::endl;

	Sprite s(map), background(bg);

	int dx = 0; bool rotate = 0; int colorNum = 1, colorNumb = 1;
	float timer = 0, delay = 0.3, countdown = 0, intensity = 0;

	Clock clock;

	colorNum = 1 + rand() % 7;
	int n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		e[i].x = figures2[n][i] % 2 + 4;
		e[i].y = figures2[n][i] / 2;
	}
	n = rand() % 7;
	colorNumb = 1 + rand() % 7;
	for (int i = 0; i < O; i++) {
		for (int j = 0; j < O; j++) {
			hold3[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) hold3[figures2[n][i] / 2][figures2[n][i] % 2] = colorNumb;

	while (blocksWindow.isOpen() && victory == false)
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
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
				timer = 0;
				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++) {
						field3[i][j] = 0;
					}
				}
				for (int i = 0; i < O; i++) {
					for (int j = 0; j < O; j++) {
						hold3[i][j] = 0;
					}
				}
				for (int i = 0; i < 4; i++) {
					e[i].x = 0;
					f[i].x = 0;
					e[i].y = 0;
					f[i].y = 0;
				}
				points = 0;
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
				break;
			default:
				break;
			}
		}

		// Movement controls
		if (upKey) {
			rotate = true;
			upKey = false;
		}
		if (leftKey) {
			dx = -1;
			leftKey = false;
		}
		if (rightKey) {
			dx = 1;
			rightKey = false;
		}
		// Speeds the game up if down is held
		if (downKey && ((0.05 - intensity) > 0.04)) delay = (0.05 - intensity);
		else if (downKey && 0.04 < (0.3 - intensity)) delay = 0.04;
		else delay = (0.3 - intensity);

		// Moves the blocks
		for (int i = 0; i < 4; i++) {
			f[i] = e[i]; e[i].x += dx;
		}
		if (!check2(e, field3)) for (int i = 0; i < 4; i++) e[i] = f[i];

		// Rotates the blocks
		if (rotate)
		{
			Point p = e[1]; // < Center the block rotates around
			for (int i = 0; i < 4; i++)
			{
				int x = e[i].y - p.y;
				int y = e[i].x - p.x;
				e[i].x = p.x - x;
				e[i].y = p.y + y;
			}
			if (!check2(e, field3)) for (int i = 0; i < 4; i++) e[i] = f[i];
		}
		// Tick system
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) { f[i] = e[i]; e[i].y += 1; }

			if (!check2(e, field3))
			{
				for (int i = 0; i < 4; i++) field3[f[i].y][f[i].x] = colorNum;

				for (int i = 0; i < 4; i++)
				{
					e[i].x = figures2[n][i] % 2 + 4;
					e[i].y = figures2[n][i] / 2 - 1;
				}

				n = rand() % 7;
				colorNum = colorNumb;
				colorNumb = 1 + rand() % 7;
				for (int i = 0; i < O; i++) {
					for (int j = 0; j < O; j++) {
						hold3[i][j] = 0;
					}
				}
				for (int i = 0; i < 4; i++) hold3[figures2[n][i] / 2][figures2[n][i] % 2] = colorNumb;
			}
			timer = 0;
		}

		// check lines
		int k = M - 1;
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field3[i][j]) count++;
				field3[k][j] = field3[i][j];
			}
			if (count < N) {
				k--;
			}
			else {
				points++;
				score.setString(std::to_string(points));
			}
		}
		k = M - 1;

		for (int j = 0; j < N; j++)
		{
			if (field3[0][j]) {
				winnerText.setString("Game Over");
				music.stop();
				music.openFromFile("resources/SHOP5.ogg");
				music.play();
				victory = true;
			}
		}

		// Default values for movement/rotate/tickrate
		dx = 0; rotate = 0;

		// Draw all the sprites
		blocksWindow.clear(Color::White);
		blocksWindow.draw(background);

		// Draws the blocks in the hold
		for (int i = 0; i < O; i++)
			for (int j = 0; j < O; j++)
			{
				if (hold3[i][j] == 0) continue;
				s.setTextureRect(IntRect(hold3[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(394, 31); //offset
				blocksWindow.draw(s);
			}

		// Draws the blocks on the ground
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field3[i][j] == 0) continue;
				s.setTextureRect(IntRect(field3[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(530, 31); //offset
				blocksWindow.draw(s);
			}

		// Draws the blocks in the air
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 27, 0, 27, 27));
			s.setPosition(e[i].x * 27, e[i].y * 27);
			s.move(530, 31); //offset
			blocksWindow.draw(s);
		}
		clocktimer.setString(std::to_string(countdown));
		blocksWindow.draw(clocktimer);
		blocksWindow.draw(clocktext);
		blocksWindow.draw(text);
		blocksWindow.draw(score);
		blocksWindow.display();
	}
	while (blocksWindow.isOpen())
	{
		sf::Event Event;
		while (blocksWindow.pollEvent(Event))
		{
			// Resets all variables on game close
			if (Event.type == Event::Closed) {
				timer = 0;
				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++) {
						field3[i][j] = 0;
					}
				}
				for (int i = 0; i < 4; i++) {
					e[i].x = 0;
					f[i].x = 0;
					e[i].y = 0;
					f[i].y = 0;
				}
				points = 0;
				blocksWindow.close();
				title();
				return;
			}
		}
		// Draw all the sprites
		blocksWindow.clear(Color::White);
		blocksWindow.draw(background);

		// Draws the blocks in the hold
		for (int i = 0; i < O; i++)
			for (int j = 0; j < O; j++)
			{
				if (hold3[i][j] == 0) continue;
				s.setTextureRect(IntRect(hold3[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(394, 31); //offset
				blocksWindow.draw(s);
			}

		// Draws the blocks on the ground
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field3[i][j] == 0) continue;
				s.setTextureRect(IntRect(field3[i][j] * 27, 0, 27, 27));
				s.setPosition(j * 27, i * 27);
				s.move(530, 31); //offset
				blocksWindow.draw(s);
			}

		// Draws the blocks in the air
		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 27, 0, 27, 27));
			s.setPosition(e[i].x * 27, e[i].y * 27);
			s.move(530, 31); //offset
			blocksWindow.draw(s);
		}

		blocksWindow.draw(winnerText);
		blocksWindow.draw(clocktimer);
		blocksWindow.draw(clocktext);
		blocksWindow.draw(text);
		blocksWindow.draw(score);
		blocksWindow.display();
	}
}
