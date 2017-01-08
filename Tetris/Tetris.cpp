// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>

#include <iostream>

using namespace std;
using namespace sf;


const int n = 25;
const int m = 10;
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

	RenderWindow window(VideoMode(600, 1000), "TETRIS");

	

	Texture ImaginePiese, Back;
	ImaginePiese.loadFromFile("images/piese.png");
	Back.loadFromFile("images/background.png");


	Sprite s(ImaginePiese), background(Back);
	s.setTextureRect(IntRect(0, 0, 40, 40));




	while (window.isOpen())
	{


		Event event;

		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();

		}

	
		int n = 1;
				for (int i = 0; i < 4; i++)
				{
					a[i].x = piese[n][i] % 2 ;
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