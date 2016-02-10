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
private:
	int m_score;
	std::pair<std::string, int> m_highScores[10] = { { "", 0 } };
public:
};

#endif // !_SCORE_H_
