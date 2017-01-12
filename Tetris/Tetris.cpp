// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>

#include <iostream>

using namespace std;
using namespace sf;


const int n = 24;
const int m = 12;
int board[n][m] = { 0 };


int piese[7][4] =
{
	{ 3,5,7,9 }, //I
	{ 2,4,5,7 }, //Z
	{ 3,5,4,6 }, //Z-reverse
	{ 2,3,5,7 }, //L
	{ 3,5,7,6 }, //L-reverse
	{ 2,3,4,5 }, //O
	{ 3,5,4,7 }, //T
};




struct Coordonate
{
	int x;
	int y;
}a[4], b[4];


bool verificare()
{
	for (int i = 0; i<4; i++)
		if (a[i].x < 0 || a[i].x >= m || a[i].y >= n) return false;
		else if (board[a[i].y][a[i].x]) return false;

		return true;
}



int main()
{
	int dx = 0;
	bool rotatie = false;
	int culoare = 0;
	float timer = 0, delay = 0.3;
	Clock clock;
	
	srand(time(0));

	RenderWindow window(VideoMode(650, 960), "TETRIS");

	

	Texture ImaginePiese, Back;
	ImaginePiese.loadFromFile("images/piese2.png");
	Back.loadFromFile("images/background.png");


	Sprite s(ImaginePiese), background(Back);
	s.setTextureRect(IntRect(0, 0, 40, 40));




	while (window.isOpen())
	{


		float time = clock.getElapsedTime().asSeconds();

		clock.restart();
		timer = timer + time;


		Event event;

		while(window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space) rotatie = true;
				else if (event.key.code == Keyboard::Left) dx = -1;
				else if (event.key.code == Keyboard::Right) dx = 1;

		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
		if (Keyboard::isKeyPressed(Keyboard::Q)) window.close();
		if (Keyboard::isKeyPressed(Keyboard::S)) delay=0.004;

		//<---Mutare--->//
		for (int i = 0; i < 4; i++)
		{
			b[i] = a[i];
			a[i].x = a[i].x + dx;

		}
		if (!verificare())
			for (int i = 0; i < 4; i++) a[i] = b[i];
	

		//<--Rotire-->//
		if (rotatie) {
			Coordonate rot = a[1]; //punctul de rotire
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - rot.y;
				int y = a[i].x - rot.x;
				a[i].x = rot.x - x;
				a[i].y = rot.y + y;

			}		
			if (!verificare())
				for (int i = 0; i < 4; i++) a[i] = b[i];
		}



	

		//<--Cadere-->//
		if (timer > delay)
		{
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].y += 1;
			}
			if (!verificare())
			{
				for (int i = 0; i < 4; i++) board[b[i].y][b[i].x] = culoare;

				culoare = 1 + rand() % 7;
				int n = rand() % 7;
			
				for (int i = 0; i < 4; i++)
				{
					a[i].x = piese[n][i] % 2 + 6;
					a[i].y = piese[n][i] / 2 - 2;

				}
			}
			timer = 0;
		}
		
	
	


		//<--Verificare ultima linie-->//
		int k = n - 1;
		for (int i = n - 1; i > 0; i--)
		{
			int nr = 0;
			for (int j = 0; j < m; j++) {

				if (board[i][j]) nr++;

				board[k][j] = board[i][j];

				
			}
			if (nr < m) {

				k--;

			}
		}

		

			dx = 0;
			rotatie = false;
			delay = 0.3;

			
			window.clear();
			window.draw(background);

			//<--Culoare si dimensiuni-->//

			for (int i = 0; i<n; i++)
				for (int j = 0; j<m; j++)
				{
					if (board[i][j] == 0) continue;
					//<--Dimensiunea si culoarea dupa ce au ajuns la final-->//
					s.setTextureRect(IntRect(board[i][j] * 40, 0, 40, 40));
					//<--Pozitia finala a pieselor-->//
					s.setPosition(j * 40, i * 40);
					window.draw(s);
				}


		for (int i = 0; i < 4; i++)
		{
			s.setTextureRect(IntRect(culoare * 40, 0, 40, 40));
			s.setPosition(a[i].x * 40, a[i].y * 40);
			window.draw(s);
		}

		window.display();

	}


	return 0;
}