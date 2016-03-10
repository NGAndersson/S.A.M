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
	bool SaveScore(std::wstring playername);
	bool LoadScore();
	void AddLives(int change) { m_lives += change; }
	void SetLives(int change = 5) { m_lives = change; }
	int GetLives() { return m_lives; }
	int GetCombo() { return m_combo; }
	void ResetCombo() { m_combo = 0; }
	void AddCombo() { m_combo += 1; }
	int GetScore() { return m_score; }
	void SetFile(std::string filename) { m_filename = filename; }
	std::pair<std::wstring, int>* GetHighScores() { return m_highScores; }
	int GetBeat() { return m_beat;}
	void ResetBeat() { m_beat = 0; }
	void AddBeat() { m_beat++; }
	void SetPercentage(double value) { m_comboPercentage = value; }
	double GetPrecentage() { return m_comboPercentage; }
private:
	std::string m_filename;
	int m_score;
	std::pair<std::wstring, int> m_highScores[10] = { { L"", 0 } };
	int m_lives;
	int m_combo = 0;
	int m_beat = 0;
	double m_comboPercentage;
public:
};

#endif // !_SCORE_H_
