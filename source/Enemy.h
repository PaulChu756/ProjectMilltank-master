#pragma once
#include "Entity.h"

//Author: Paul Chu
//Origin: Mr. Marco S.
//Date: 10-30-14
// This is the enemy header
extern int g_lives;

class Enemy : public Entity        // Enemy Class
{
public:
	static int s_maxEnemies;
	static float speedBoost;

	Enemy(int x, int y) : Entity("Enemy", x, y, 100, 50, 300, iScreenWidth - 50, iScreenHeight + 100) // Enemy Parameters
	{
		for (int i = 0; i < s_maxEnemies; ++i)
		{
			if (!m_Enemies[i])
			{
				m_Enemies[i] = this;
				break;
			}
		}
	}

	bool IsActive()
	{
		return m_y > 0 && m_y < m_h;
	}

	void Update(float dt)                   // Update Enemy
	{
		if (m_y - speed * dt < 0)
		{
			g_lives--;
		}
		m_y -= speed * dt;

	}

	void onCollide(const Entity *e)         // Enemy collide
	{
		m_y += iScreenHeight + 100;
		speedBoost += 10;
	}

	static void SpawnEnemy() // Spawn Enemy
	{

		float m_x = rand() % (iScreenWidth - 100) + 50;
		float m_y = iScreenHeight + 10;

			for (int i = 0; i < 49; ++i)
			{
				if (m_Enemies[i] && !m_Enemies[i]->IsActive())
				{
					delete m_Enemies[i];
					m_Enemies[i] = nullptr;
				}

				else if (!m_Enemies[i])
				{
					new Enemy(m_x, m_y);
					break;
				}

				if (m_Enemies[i])
					m_Enemies[i]->speed += speedBoost;
			}
	}

};
int Enemy::s_maxEnemies = 49;
float Enemy::speedBoost = 10;