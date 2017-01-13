Pentru rularea programului veti avea nevoie de Visual Studio (2015) si SFML(2.4.1) 64-bit.

Dupa downloadarea proiectului urmati pasii:

1.Accesati "TetrisMarcu-master"->Tetris.sln
2.Setati programul pe x64 din bara de sus
Din Visual Studio:
3.Click dreapta pe "Solutia" Tetris->Properties
4.Configuration: All Configurations
5.C/C++ -> General -> Additional Include Directories -> link catre fisierul "include" din SFML
6 Linker-> General -> Additional Library Directories -> link catre fisierul "lib" din SFML
7.Configuration: Debug
8.Linker->Input->Additional Dependencies adaugati urmatoarele linii: 
			sfml-system-d.lib
			sfml-audio-d.lib
			sfml-graphics-d.lib
			sfml-network-d.lib
			sfml-window-d.lib
9.Configuration: Release
10.Linker->Input->Additional Dependencies adaugati urmatoarele linii:
			sfml-system.lib
			sfml-audio.lib
			sfml-graphics.lib
			sfml-network.lib
			sfml-window.lib

11.CTRL + F5 pentru a porni programul

Sau

1.Accesati folderul Release game
2.Deschideti Tetris.exe