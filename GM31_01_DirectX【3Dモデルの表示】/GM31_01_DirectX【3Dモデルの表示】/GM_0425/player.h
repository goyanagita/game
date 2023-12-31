#pragma once

#include <string>
#include "model.h"

#include "gameObject.h"

enum PLAYER_STATE
{
	PLAYER_STATE_GROUND,
	PLAYER_STATE_JUMP
};

class Player : public GameObject
{
private:
	PLAYER_STATE m_PlayerState = PLAYER_STATE_GROUND;
	bool m_IsGround = false;

	//class Model* m_Model{};
	class AnimationModel* m_Model{};

	ID3D11ShaderResourceView* m_ToonTexture = {};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3 m_Velocity{};

	class Audio* m_ShotSE{};
	class Shadow* m_Shadow{};
	class Audio* m_Jump{};

	D3DXMATRIX m_Matrix;

	int m_Time{};
	float m_BlendRate{};
	std::string m_AnimationName;
	std::string m_NextAnimationName;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void UpdateGround();
	void UpdateJump();

	D3DXMATRIX GetMatrix() { return m_Matrix; }

};
