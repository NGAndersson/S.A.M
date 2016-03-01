#include "../../../Header Files/Screens/Menu/HighscoreMenu.h" 

HighScoreMenu::HighScoreMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_stats = stats;
	m_stats->LoadScore();

	m_highscore = m_stats->GetHighScores();	//receives 10

	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");

}

void HighScoreMenu::Update(double time)
{
	//Don't do anything here
}

void HighScoreMenu::Render()
{	
	
	m_spriteBatch->Begin();
	//Highscore list
	DirectX::SimpleMath::Vector3 _scale;
	_scale.x = float(m_screenWidth) / float(1058), _scale.y = (float(m_screenHeight) / float(1440)), _scale.z = (float(m_screenHeight) / float(1440));
	for (int i = 0; i < 10; i++)
	{
		DirectX::XMVECTOR _nameOrigin = m_font->MeasureString(m_highscore[i].first.c_str());
		_nameOrigin = DirectX::XMVectorSetIntY(_nameOrigin, 0);
		
		m_font->DrawString(
			m_spriteBatch.get(),
			m_highscore[i].first.c_str(),
			SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 4 + i * m_screenHeight / 20),
			Colors::Yellow,
			0.f,
			_nameOrigin,
			SimpleMath::Vector3(1.0-i*0.05) * _scale
			);
		m_font->DrawString(
			m_spriteBatch.get(),
			to_wstring(m_highscore[i].second).c_str(),
			SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 4 + i * m_screenHeight / 20),
			Colors::Yellow,
			0.f,
			SimpleMath::Vector2(0.f),
			SimpleMath::Vector3(1.0-i*0.05) * _scale
			);
	}
	m_spriteBatch->End();
}
