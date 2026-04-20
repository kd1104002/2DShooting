#pragma once

class Scene;

class C_Player
{
public:

	C_Player() {}
	~C_Player() {}

	void Init();
	void Update();
	void Draw();

	void SetTex(KdTexture* tex);
	void Set0wner(Scene* oner);


	void SetPlayerTex(KdTexture* tex) { m_playertex = tex; }


private:

	Scene* m_owner;

	Math::Vector2 m_move;
	Math::Vector2 m_pos;

	KdTexture* m_playertex;
	Math::Matrix m_playerscalemat;
	Math::Matrix m_playertransmat;
	Math::Matrix m_playermat;
	
};