#include "../../../Header Files/Screens/Menu/UI.h" 

UI::UI(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_stats = stats;
	m_input = input;

	m_pressed1 = L"1";
	m_shotBinding[SHOT1].m_color = Colors::Crimson;
	m_shotBinding[SHOT1].m_origin = DirectX::SimpleMath::Vector2(0, 0);
	m_shotBinding[SHOT1].m_position = DirectX::SimpleMath::Vector2(20 * (float(m_screenWidth) / float(1058)), m_screenHeight - 190 * (float(m_screenHeight) / float(1440)));

	m_pressed2 = L"2";
	m_shotBinding[SHOT2].m_color = Colors::Crimson;
	m_shotBinding[SHOT2].m_origin = DirectX::SimpleMath::Vector2(0, 0);
	m_shotBinding[SHOT2].m_position = DirectX::SimpleMath::Vector2(20 * (float(m_screenWidth) / float(1058)), m_screenHeight - 160 * (float(m_screenHeight) / float(1440)));

	m_pressed3 = L"3";
	m_shotBinding[SHOT3].m_color = Colors::Crimson;
	m_shotBinding[SHOT3].m_origin = DirectX::SimpleMath::Vector2(0, 0);
	m_shotBinding[SHOT3].m_position = DirectX::SimpleMath::Vector2(20 * (float(m_screenWidth) / float(1058)), m_screenHeight - 130 * (float(m_screenHeight) / float(1440)));

	m_pressed4 = L"4";
	m_shotBinding[SHOT4].m_color = Colors::Crimson;
	m_shotBinding[SHOT4].m_origin = DirectX::SimpleMath::Vector2(0, 0);
	m_shotBinding[SHOT4].m_position = DirectX::SimpleMath::Vector2(20 * (float(m_screenWidth) / float(1058)), m_screenHeight - 100 * (float(m_screenHeight) / float(1440)));
}

UI::~UI() 
{
	m_score.erase();
	m_livesLeft.erase();
}

void UI::Update(double time)
{
	BulletType _bullet = m_input->CheckBullet();

	switch (_bullet)
	{
	case INPUT_DEFAULT_BULLET:
		m_shotBinding[SHOT1].m_color = Colors::Crimson;
		m_shotBinding[SHOT2].m_color = Colors::Crimson;
		m_shotBinding[SHOT3].m_color = Colors::Crimson;
		m_shotBinding[SHOT4].m_color = Colors::Crimson;
		break;
	case INPUT_BULLET2:
		m_shotBinding[SHOT1].m_color = Colors::Green;
		break;
	case INPUT_BULLET3:
		m_shotBinding[SHOT2].m_color = Colors::Green;
		break;
	case INPUT_BULLET4:
		m_shotBinding[SHOT3].m_color = Colors::Green;
		break;
	case INPUT_BULLET5:
		m_shotBinding[SHOT4].m_color = Colors::Green;
		break;
	default:
		break;
	}

	m_score = to_wstring(m_stats->GetScore());
	m_livesLeft = to_wstring(m_stats->GetLives());
	m_combo = to_wstring(m_stats->GetCombo());
}

void UI::Render(int offset)
{
	SimpleMath::Vector2 _scorePos, _livesPos, _comboPos, _offsetCountPos;
	_scorePos.x = m_screenWidth /2;
	_scorePos.y = 40.f * (float(m_screenHeight) / float(1440));
	_livesPos.x = 100 * (float(m_screenWidth) / float(1058));
	_livesPos.y = m_screenHeight - 40 * (float(m_screenHeight) / float(1440));
	_comboPos.x = m_screenWidth - 150 * (float(m_screenWidth) / float(1058)), _comboPos.y = m_screenHeight - 40 * (float(m_screenHeight) / float(1440));
	_offsetCountPos.x = m_screenWidth / 2, _offsetCountPos.y = m_screenHeight / 2;

	wstring _tempHighScore = L"High Score: " + m_score;
	wstring _tempLives = L"Lives: " + m_livesLeft;
	wstring _tempCombo = L"Combo: " + m_combo;
	wstring _tempOffset;
	if ((offset - m_stats->GetBeat() + 1) > 10)
	{
		_tempOffset = L"Take a chill pill";
	}
	else if ((offset - m_stats->GetBeat() + 1) > 0)
	{
		_tempOffset = L"Beats until start: " + to_wstring(offset - m_stats->GetBeat());
	}
	else if ((offset - m_stats->GetBeat() + 1) > -4)
	{
		_tempOffset = L"Go Go Go";
	}
	m_spriteBatch->Begin();
	if (offset - m_stats->GetBeat() >= -4)
	{
		m_font->DrawString(m_spriteBatch.get(), _tempOffset.c_str(), _offsetCountPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempOffset.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	}
	m_font->DrawString(m_spriteBatch.get(), _tempHighScore.c_str(),_scorePos, Colors::Crimson, 0.f, m_font->MeasureString(_tempHighScore.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), _tempLives.c_str(), _livesPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempLives.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), _tempCombo.c_str(), _comboPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempCombo.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), m_pressed1.c_str(), m_shotBinding[SHOT1].m_position, m_shotBinding[SHOT1].m_color, 0.f, m_font->MeasureString(m_pressed1.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), m_pressed2.c_str(), m_shotBinding[SHOT2].m_position, m_shotBinding[SHOT2].m_color, 0.f, m_font->MeasureString(m_pressed2.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), m_pressed3.c_str(), m_shotBinding[SHOT3].m_position, m_shotBinding[SHOT3].m_color, 0.f, m_font->MeasureString(m_pressed3.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), m_pressed4.c_str(), m_shotBinding[SHOT4].m_position, m_shotBinding[SHOT4].m_color, 0.f, m_font->MeasureString(m_pressed4.c_str()) / 2.f, float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), _tempBeat.c_str(), SimpleMath::Vector2(0.f), Colors::Crimson, 0.f, SimpleMath::Vector2(0.f), float(m_screenWidth) / float(1058));
	m_font->DrawString(m_spriteBatch.get(), to_wstring(m_stats->GetShit()).c_str(), SimpleMath::Vector2(0, 200), Colors::Crimson, 0.f, SimpleMath::Vector2(0.f), float(m_screenWidth) / float(1058));
	m_spriteBatch->End();

}

