#pragma once
#include "Entity.h"

//Author: Paul Chu
//Origin: Mr. Marco S.
//Date: 10-30-14
// This is the Bullet header
extern int g_score;

class Bullet : public Entity
{
public:
	Bullet(double x, double y) : Entity("Bullet", x, y, 400, 10, 0, 10, iScreenHeight) {}

	static const int s_maxBullet;

	void Update(float dt) // Update
	{
		m_y += speed * dt;
	}


	void onCollide(const Entity *e) // Collide Bullets to see if they kill the evil tomato
	{
		m_y = m_h + 100;
		g_score += 10;
	}


	bool IsActive() // If Bullet is active
	{
		return m_y > 0 && m_y < iScreenHeight;
	}


	static void SpawnBullet(float a_x, float a_y) // Spawn Bullet
	{
		for (int i = 0; i < s_maxBullet; ++i)
		{
			if (!m_bullets[i] || !m_bullets[i]->IsActive())
			{
				if (m_bullets[i]) delete m_bullets[i];

				m_bullets[i] = new Bullet(a_x, a_y);
				break;
			}
		}
	}

};
const int Bullet::s_maxBullet = 10;