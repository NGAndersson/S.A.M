#include "../../../Header Files/Screens/Menu/UI.h" 

UI::UI(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_stats = stats;
}

UI::~UI() 
{
	m_score.erase();
	m_high.erase();
	m_lives.erase();
	m_livesLeft.erase();
}

void UI::Update()
{
	m_score = to_wstring(m_stats->GetScore());
	m_livesLeft = to_wstring(m_stats->GetLives());
}

void UI::Render()
{
	SimpleMath::Vector2 _scorePos,_livesPos;
	_scorePos.x = m_screenWidth /2;
	_scorePos.y = 40;
	_livesPos.x = 100;
	_livesPos.y = m_screenHeight - 40;

	wstring _tempHighScore = m_high+m_score;
	wstring _tempLives = m_lives + m_livesLeft;
	m_spriteBatch->Begin();
	m_font->DrawString(m_spriteBatch.get(), _tempHighScore.c_str(),_scorePos, Colors::Crimson, 0.f, m_font->MeasureString(_tempHighScore.c_str()) / 2.f);
	m_font->DrawString(m_spriteBatch.get(), _tempLives.c_str(), _livesPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempLives.c_str()) / 2.f);
	
	m_spriteBatch->End();
}

