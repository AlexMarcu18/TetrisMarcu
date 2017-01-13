// Tetris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include<sstream>
#include<string>
#include<Windows.h>
#include<mmsystem.h>
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
}a[4], b[4],c[4];




bool verificare()
{
	for (int i = 0; i<4; i++)
		if (a[i].x < 0 || a[i].x >= m || a[i].y >= n) return false;
		else if (board[a[i].y][a[i].x]) return false;

		return true;
}

RenderWindow window(VideoMode(650, 960), "TETRIS", Style::Close | Style::Titlebar);



void Tetris()
{
	int dx = 0;
	bool rotatie = false;
	int culoare = 0;
	double timer = 0, delay = 0.3;
	Clock clock;
	Music music;
	Music sound;
	Music fail;
	fail.openFromFile("Fail.ogg");
	bool stop = false;
	bool solo = false;


	if (!music.openFromFile("Wicked.ogg"))
	{
		cout << "ERROR" << endl;

	}
	sound.openFromFile("GunShot.ogg");
	

	music.play();

	int scor = 0;
	ostringstream ss;
	ss<< "Score"<<endl<<"   "<< scor;

	Font arial;
	arial.loadFromFile("impact.ttf");

	Text ScorActual;
	ScorActual.setCharacterSize(30);
	ScorActual.setPosition({ 525,70 });
	ScorActual.setFont(arial);
	ScorActual.setString(ss.str());
	
	
	srand(time(0));


	Texture ImaginePiese, Back, GameOv;
	ImaginePiese.loadFromFile("images/piese2.png");
	Back.loadFromFile("images/background.png");
	GameOv.loadFromFile("images/GameOver.png");
	
	
	Sprite s(ImaginePiese), background(Back), finish(GameOv);
	
	

	
	int Random = rand() % 7;

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
				else if (event.key.code == Keyboard::P) wait = true;

		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
		if (Keyboard::isKeyPressed(Keyboard::Q)) window.close();
		if (Keyboard::isKeyPressed(Keyboard::LShift)) delay=0.004;
		



	if(!stop){

		if (!wait) {

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
				sound.play();
				if (!verificare())
					for (int i = 0; i < 4; i++) a[i] = b[i];
			
				
			}



			int p = Random;

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


					for (int i = 0; i < 4; i++)
					{
						a[i].x = piese[p][i] % 2 + 6;
						a[i].y = piese[p][i] / 2 - 2;

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

				if (nr == m)
				{
					scor = scor + 50;
					ss.str("");
					ss << "Score" << endl << "   " << scor;
					ScorActual.setString(ss.str());
				}


				if (nr < m) {

					k--;

				}
			}

			int  nr = 0;
			for (int i = n - 1; i >= 0; i--)
			{

				for (int j = 0; j <= m - 1; j++)


					if (board[i][j])
					{
						nr++;
						break;
					}

				if (nr == n)
				{	
					stop = true;
					window.draw(finish);
					music.stop();
					fail.play();

				}

			}



			dx = 0;
			rotatie = false;
			delay = 0.3;
			Random = rand() % 7;



		
			window.clear();
			window.draw(background);
			
		
			//<--Culoare si dimensiuni-->//

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
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

			
			


		}
			else if (Keyboard::isKeyPressed(Keyboard::R)) wait = false;



			window.draw(ScorActual);
			window.display();
			
		}
	else {
			window.draw(finish);
			window.display();
		}
	}


	
}


	void main()
	{
		Texture menuTex;
		menuTex.loadFromFile("images/meniu.png");
		Sprite menu;
		menu.setTexture(menuTex);

		window.clear(Color::Black);
		window.draw(menu);
		window.display();
		while (window.isOpen())
		{
			Event windowMenu;
			while (window.pollEvent(windowMenu))
			{
				if (windowMenu.type == Event::Closed)
					window.close();
				if (windowMenu.type == Event::KeyPressed)
					if (windowMenu.key.code == Keyboard::S)
					{
						Tetris();

					}
				
					else if (windowMenu.key.code == Keyboard::Q) window.close();
			}

		}
	}

