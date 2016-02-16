#ifndef _SCORE_H_
#define _SCORE_H_
#include <fstream>
#include <sstream>

class Stats {
private:
public:
	Stats();
	~Stats();
	void AddScore(int add);
	void ResetScore();
	bool SaveScore(std::string filename, std::string playername);
	bool LoadScore(std::string filename);
	void AddLives(int change) { m_lives += change; }
	void SetLives(int change = 3) { m_lives = change; }
	int GetLives() { return m_lives; }
	int GetScore() { return m_score; }
private:
	int m_score;
	std::pair<std::string, int> m_highScores[10] = { { "", 0 } };
	int m_lives;
public:
};

#endif // !_SCORE_H_
