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




int main()
{
	int dx = 0;
	bool rotatie = false;
	

	RenderWindow window(VideoMode(650, 960), "TETRIS");

	

	Texture ImaginePiese, Back;
	ImaginePiese.loadFromFile("images/piese.png");
	Back.loadFromFile("images/background.png");


	Sprite s(ImaginePiese), background(Back);
	s.setTextureRect(IntRect(0, 0, 40, 40));




	while (window.isOpen())
	{


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

		

		//<---Mutare--->//
		for (int i = 0; i < 4; i++)
		{
			
			a[i].x = a[i].x + dx;

		}

		//<--Rotire-->//
		if (rotatie) {
			Coordonate p = a[1]; //punctul de rotire
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;

			}

		}

		dx = 0;
		rotatie = false;



	
		int n = 1;
		if(a[0].x==0)
				for (int i = 0; i < 4; i++)
				{
					a[i].x = piese[n][i] % 2 + 5;
					a[i].y = piese[n][i] / 2 ;
				}

		window.clear();
		window.draw(background);
		for (int i = 0; i < 4; i++)
		{
			
			s.setPosition(a[i].x * 40, a[i].y * 40);
			window.draw(s);
		}

		window.display();

	}


	return 0;
}