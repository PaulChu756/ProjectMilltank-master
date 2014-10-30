#pragma once

//Author: Mr. Marco S.
//Origin: Mr. Marco S.
//Date: 10-30-14
// Base of operations for Score Data to be in, honesty, it's done by you Mr. Marco... 


struct ScoreData // doesn't matter what's in here
{
	int score;
	char m_name[16];	
};

class ScoreBuffer // Mainly static class for global access
{
	static int m_nScores;		// Number of scores
	static ScoreData *m_scores; // Array of scores
	static const char *m_path;
	ScoreBuffer() {}
public:
	static void load();
	static void draw(int x, int y);
	static void save();
	static void sort();
	static void addScore(ScoreData a_score);
};