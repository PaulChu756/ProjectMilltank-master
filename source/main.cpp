
#include "AIE.h"
#include <string>
#include <cmath>
#include <time.h>
#include <assert.h>
#if !defined(OSX)
	#include <crtdbg.h>
#endif
#include <iostream>
#include <list>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "AssetManager.h"
#include "Entity.h"
#include "ScoreBuffer.h"
#include "estates.h"

//Author: Paul Chu
//Origin: Mr. Marco S.
//Date: 10-30-14
// Main part of the program where  all the pieces of the puzzle is placed for special magic to work.


int main(int argc, char* argv[])
{
	srand(time(0));

	Initialise(iScreenWidth, iScreenHeight, false, "Space Invaders");
	SetBackgroundColour(SColour(0x00, 0x00, 0x00, 0xFF));
	AddFont("./fonts/invaders.fnt");
	
	// Load in all the pictures
	g_AssetManager.Load("player", "./images/Milktank.png", 60, 40);
	g_AssetManager.Load("Bullet", "./images/Milk.jpg", 20, 20);
	g_AssetManager.Load("Enemy", "./images/Tomato.jpg", 50, 30);
	g_AssetManager.Load("Background", "./images/Meadow.png", iScreenWidth, iScreenHeight);

	new Player(); // New PLayer

	Entity::init();

	float enemyTimer = 0; // Enemy timer and delay
	float Delay = rand() % 1 + 1;

	g_CurrentState = e_Menu;
	
	ScoreBuffer::load(); // Load Scores

	do
	{
		ClearScreen(); // Clear ze screen
		float fDeltaT = GetDeltaTime(); // Delta time so the computer doesn't cheat you
	 



		enemyTimer += fDeltaT;

		if (enemyTimer > Delay && g_CurrentState == e_StartGame) // Starting a brand new game so enemies spawn at top again
		{
			Enemy::SpawnEnemy();
			enemyTimer = 0;
		}

		g_AssetManager.Draw("Background", iScreenWidth / 2, iScreenHeight / 2); // Draw ze Background

		Play(fDeltaT);

		DrawLine(0, 40, iScreenWidth, 40, SColour(0x00, 0xFC, 0x00, 0xFF));
		std::string timeFrame = "DeltaTime: ";
		timeFrame.append(std::to_string(fDeltaT));
		SetFont(nullptr);

		if (g_CurrentState == e_Exit) // Exit the program
		{
			break;
		}

	} while (FrameworkUpdate() == false);

	ScoreBuffer::save(); // Save Score
	g_AssetManager.FreeAll();
	Shutdown();

	return 0;
}
