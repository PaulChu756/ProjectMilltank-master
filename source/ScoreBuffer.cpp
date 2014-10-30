#include "ScoreBuffer.h"
#include <fstream>
#include "Aie.h"
#include <cstring>

//Author: Paul Chu
//Origin: Mr. Marco S.
//Date: 10-30-14
// This cpp file is used for scores for the program. 

int ScoreBuffer::m_nScores = 0;		// Number of scores
ScoreData *ScoreBuffer::m_scores = nullptr; // Array of scores
const char *ScoreBuffer::m_path = "scores.dat";


// load in score
void ScoreBuffer::load()
{
	std::fstream fin;
	fin.open(m_path, std::ios_base::binary | std::ios_base::in);
	if (fin.is_open())
	{
		fin >> m_nScores;
		m_scores = new ScoreData[m_nScores];
		fin.read((char*)m_scores, sizeof(ScoreData)*m_nScores);
	}
	fin.close();
}
void ScoreBuffer::draw(int x, int y) // Draw Score
{
	int Scorenum;
	for (int i = 0; i < m_nScores && i < 5; ++i)
	{
		Scorenum = i + 1;
		char cnum[8];
		char c_score[8];
		char output[16];

		itoa(m_scores[i].score, c_score, 10);
		itoa(Scorenum, cnum, 10);
		cnum[1] = ':';
		cnum[2] = 0;

		strcpy_s(output, 16, m_scores[i].m_name);
		strcat_s(output, cnum);

		DrawString(output, x, y - i * 40);
		DrawString(c_score, x + 200, y - i * 40);
	}
}
void ScoreBuffer::save() // Save the score
{
	std::fstream fout;
	fout.open(m_path, std::ios_base::binary | std::ios_base::out);
	if (fout.is_open())
	{
		fout << m_nScores;
		fout.write((char*)m_scores, sizeof(ScoreData)*m_nScores);
		delete[] m_scores;
		m_scores = nullptr;
	}
	fout.close();
}

void SD_swap(ScoreData &a, ScoreData &b)  // Swap function so the score can sort from highest to low
{ 
	ScoreData t = a; a = b; b = t; 
}
bool SD_cmp(ScoreData a, ScoreData b) 
{ 
	return a.score < b.score; 
}


//  Sort 
void ScoreBuffer::sort()
{
	for (int j = 0; j < m_nScores; ++j)
		for (int i = 0; i < m_nScores - 1; ++i)
		{
		if (SD_cmp(m_scores[i], m_scores[i + 1]))
			SD_swap(m_scores[i], m_scores[i + 1]);
		}
}

// Add Scores
void ScoreBuffer::addScore(ScoreData a_score)
{
	ScoreData *old_scores  = m_scores;
	m_scores = new ScoreData[m_nScores + 1];

	for (int i = 0; i < m_nScores; ++i)
	{
		m_scores[i] = old_scores[i];
	}
	// Deleting the old scores after passes the limit of 5
	delete[] old_scores;

	m_scores[m_nScores] = a_score;
	m_nScores++;
}