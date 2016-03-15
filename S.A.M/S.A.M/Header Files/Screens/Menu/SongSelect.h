#ifndef _SONGSELECT_H
#define _SONGSELECT_H

#include "../Screen.h"
#include "../../Gamelogic/Stats.h"
#include "../SongElement.h"
#include "../../Audio/SoundManager.h"

class SongSelect : public Screen
{
private:
	SongSelect() {}
	~SongSelect();

public:
	SongSelect(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats, SoundManager* soundManager);
	void Update(double time);
	void Render();
	string GetSelectedSongFile() { return string(m_songElements[m_selection]->GetDataFile()); }
	string GetScoreFile() { return m_songElements[m_selection]->GetScoreFile(); }
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;
	vector<SongElement*> m_songElements;
	SongElement* m_visibleElements[5];
	int m_selection;

	SoundManager* m_soundManager;
	Stats* m_stats;
	
	std::unique_ptr<DirectX::CommonStates> m_states;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_arrows[4];
};
#endif