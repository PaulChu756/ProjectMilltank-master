#pragma once
#include "Entity.h"
#include "Bullet.h"
//Author: Paul Chu
//Origin: Mr. Marco S.
//Date: 10-30-14
// This is the Player header
class Player : public Entity
{
private:

public:
	Player() : Entity("player", iScreenWidth / 2, 71, 600, 32, 0, iScreenWidth - 32, 80), m_fire(true) // Basic set up for the player
	{
		m_Player = this;
	}



		bool m_fire; // Fire

		void Update(float dt) // Update
		{
			if (IsKeyDown('A')) // Move Left
				m_x-= speed *dt;
			if (m_x > iScreenWidth - 1)
				m_x = xmin;
			
			if (IsKeyDown('D')) // Move right
				m_x += speed *dt;
			if (m_x < 1)
				m_x = iScreenWidth - 32;
		

			if (!IsKeyDown (KEY_SPACE)) // Shoot the Tomato people
				m_fire = true;
			if (IsKeyDown(KEY_SPACE) && m_fire)
			{
				Bullet::SpawnBullet(m_x, m_y); 
				m_fire = false;
			}
		}


};

