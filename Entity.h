#pragma once
#include "AIE.h" 
#include <vector> 
#include <random>
#include <ctime>
#include "AssetManager.h"
using namespace std;

//Author: Paul Chu
//Origin: Mr. Marco S.
//Date: 10-30-14
// Entity class is where Bullet, Enemy and Player get their basic information from.

class Entity // Basic set-up for Player, Enemy and Bullet
{
protected:
	static std::vector<Entity*> s_entities;

	// x, y, width, height
	float m_x, m_y;
	int m_w, m_h;
	int xmin, ymin;
	
	unsigned sprite;
	// Bullets, enemies and ze player
	static Entity *m_bullets[100];
	static Entity *m_Enemies[49];
	static Entity *m_Player;

	string m_name;

public: 
	float speed;

	static void clearAll()
	{
		for (int i = 0; i < 100; ++i)
		{
			delete m_bullets[i];
			m_bullets[i] = nullptr;
		}
		for (int i = 0; i < 49; ++i)
		{
			delete m_Enemies[i];
			m_Enemies[i] = nullptr;
		}

	}


	Entity(const char *name, float a_x, float a_y, float sp, int a_xmin, int a_ymin, int a_w, int a_h)
	{
		
		m_name = name;
		m_x = a_x;
		m_y = a_y;
		speed = sp;
		xmin = a_xmin;
		ymin = a_ymin;
		m_w = a_w;
		m_h = a_h;
	}

	virtual bool IsActive() { return true;}
	void draw() { g_AssetManager.Draw(m_name.c_str(), m_x, m_y);}
	virtual void Update(float dt) = 0;
	virtual void onCollide(const Entity *e)
	{

	}

	bool Active;
	// use this formula for distance and detect collide
	float Distance(const Entity *b)
	{
		return sqrt((m_x - b->m_x) * (m_x - b->m_x) + (m_y - b->m_y) * (m_y - b->m_y));
	}
	// Draw bullets and enemies and player
	static void Drawall()
	{
		for (int i = 0; i < 10; ++i)
			if (m_bullets[i] && m_bullets[i]->IsActive())
				m_bullets[i]->draw();
		for (int i = 0; i < 49; ++i)
			if (m_Enemies[i])
				m_Enemies[i]->draw();

		if (m_Player)
			m_Player->draw();

	}
	// Update all
	static void Updateall(float dt)
	{
		for (int i = 0; i < 10; ++i)
			if (m_bullets[i] && m_bullets[i]->IsActive())
				m_bullets[i]->Update(dt);

		for (int i = 0; i < 49; ++i)
			if (m_Enemies[i] && m_Enemies[i]->IsActive())
				m_Enemies[i]->Update(dt);


		for (int i = 0; i < 10; ++i)
			if (m_bullets[i] && m_bullets[i]->IsActive())
				for (int j = 0; j < 49; ++j)
					if (m_Enemies[j] && m_Enemies[j]->IsActive())
						if (m_bullets[i]->Distance(m_Enemies[j]) < 30)
						{
							m_bullets[i]->onCollide(m_Enemies[j]);
							m_Enemies[j]->onCollide(m_bullets[i]);
					
						}
		if (m_Player)
			m_Player->Update(dt);
	}
	// I don't know what this does....
	static void init()
	{
		for (int i = 0; i < 49; ++i)
			m_Enemies[i] = nullptr;
	}

};

Entity *Entity::m_bullets[100];
Entity *Entity::m_Enemies[49];
Entity *Entity::m_Player;