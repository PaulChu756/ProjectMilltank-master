#pragma once
#include <map>
#include <string>
#include "AIE.h"
using namespace std;

 //Author: Totally Mr. Marco S.
 //Origin: Mr. Marco S.
 //Date: 10-30-14
 // This AssetManager.h is used for special voodoo... Ummm, I would say it's about the screen
// program, drawing and moving textures to the screen.

const int iScreenWidth = 672;
const int iScreenHeight = 780;

class
{

	struct TextureData { unsigned  m_handle, m_width, m_height; };
	map<string, TextureData> m_textures;

public:
	void Draw(const char *name, float x, float y)
	{
		if (m_textures.count(name) > 0) // make sure the key
		{
			MoveSprite(m_textures[name].m_handle, x, y);
			DrawSprite(m_textures[name].m_handle);
		}
	}
	void Load(const char *name, const char *path, unsigned a_width, unsigned a_height)
	{
		if (m_textures.count(name) > 0)
			DestroySprite(m_textures[name].m_handle);

		TextureData temp;
		temp.m_handle = CreateSprite(path, a_width, a_height, true);
		temp.m_width = a_width;
		temp.m_height = a_height;

		m_textures[name] = temp;
	}
	void FreeAll()
	{
		for (auto t : m_textures) // Special voodoo, don't worry		
			DestroySprite(t.second.m_handle);
	}
} g_AssetManager;