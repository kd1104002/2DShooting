#include "Player.h"
#include "Scene.h"

void C_Player::Init()
{
	m_pos = { 0,0 };
	
	//ˆÚ“®
	m_move.x = 0.0f;
	m_move.y = 0.0f;
}

void C_Player::Update()
{

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_pos.x += 5;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_pos.x -= 5;
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pos.y += 5;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pos.y -= 5;
	}


	m_playerscalemat = Math::Matrix::CreateScale(30, 1.0f, 1.0f);
	m_playertransmat = Math::Matrix::CreateTranslation(m_move.x , m_move.y, 0);
	m_playermat = m_playerscalemat * m_playertransmat;//Šg‘å*‰ñ“]*ˆÚ“®


}

void C_Player::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, Math::Rectangle(0, 0, 64, 64), 1.0f);


	SHADER.m_spriteShader.SetMatrix(m_playermat);
	SHADER.m_spriteShader.DrawTex(m_playertex, Math::Rectangle{ 0,0,64,64 });

}

void C_Player::SetTex(KdTexture* tex)
{
	m_playertex = tex;
}

void C_Player::Set0wner(Scene* owner)
{
	m_owner = owner;
}