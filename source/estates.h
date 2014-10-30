#pragma once

//Author: Paul Chu
//Origin: Mr. Marco S.
//Date: 10-30-14
// Game States of Program! 


enum E_State 
	{e_Menu,
	e_Pause,
	e_Score,
	e_StartGame,
	e_Lose,
	e_Exit};


 E_State g_CurrentState; // current state
//extern const int iScreenHeight, iScreenWidth;

 int g_lives;
 int g_score;

 void Play(float dt)
 {
	 ScoreData t = { g_score, "Miltank " }; // Store data
	 switch (g_CurrentState)
	 {
	 case e_Menu: // Menu, start game, score or exit program
		 DrawString("(S)tart", iScreenWidth * 0.49f, iScreenHeight * 0.3f);
		 DrawString("S(C)ORE", iScreenWidth * 0.49f, iScreenHeight * 0.25f);
		 DrawString("(E)xit", iScreenWidth * 0.49f, iScreenHeight * 0.2f);

		 if (IsKeyDown('S')) { g_CurrentState = e_StartGame; g_lives = 3; g_score = 0;  Entity::clearAll(); }
		 if (IsKeyDown('C')) g_CurrentState = e_Score;
		 if (IsKeyDown('E')) g_CurrentState = e_Exit;
		 break;


	 case e_Lose: // Lose State, Play Again, Score and exit 
		 DrawString("P(L)ay Again?", iScreenWidth * 0.49f, iScreenHeight * 0.3f);
		 DrawString("S(C)ORE", iScreenWidth * 0.49f, iScreenHeight * 0.25f);
		 DrawString("(E)xit", iScreenWidth * 0.49f, iScreenHeight * 0.2f);

		 if (IsKeyDown('L'))  { g_CurrentState = e_StartGame; g_lives = 3; g_score = 0;  Entity::clearAll(); }
		 if (IsKeyDown('C')) g_CurrentState = e_Score;
		 if (IsKeyDown('E')) g_CurrentState = e_Exit;
		 break;

	 case e_Pause: // Pause state, I'm getting tried of typing in this.
		 DrawString("(C)ontinue?", iScreenWidth * 0.49f, iScreenHeight * 0.3f);
		 DrawString("(S)core", iScreenWidth * 0.49f, iScreenHeight * 0.25f);
		 DrawString("(E)xit", iScreenWidth * 0.49f, iScreenHeight * 0.2f);

		 if (IsKeyDown('C')) { g_CurrentState = e_StartGame; g_lives = 3; g_score = 0;  Entity::clearAll(); }
		 if (IsKeyDown('S')) g_CurrentState = e_Score;
		 if (IsKeyDown('E')) g_CurrentState = e_Exit;
		 break;

	 case e_Score: // Score! WHOOP WHOOP!
		 DrawString("(M)enu", iScreenWidth * 0.2f, iScreenHeight * 0.3f);
		 if (IsKeyDown('M')) g_CurrentState = e_Menu;
		 ScoreBuffer::draw(iScreenWidth * 0.49f, iScreenHeight * 0.3f);

		 break;


	 case e_StartGame: // Start Game
		 if (IsKeyDown('P')) g_CurrentState = e_Pause;
		 if (g_lives <= 0)
		 {
			 ScoreBuffer::addScore(t); 
			 g_CurrentState = e_Lose;
		 }
		 ScoreBuffer::sort();
		 Entity::Drawall();
		 Entity::Updateall(dt);
		 break;
		


		 


	 }





 }