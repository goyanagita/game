#pragma once

#include "gameObject.h"
//
//class Posteffect : public GameObject
//{
//private:
//	ID3D11VertexShader* m_VertexShader{};
//	ID3D11PixelShader* m_PixelShader{};
//	ID3D11InputLayout* m_VertexLayout{};
//	ID3D11Buffer* m_VertexBuffer = NULL;
//public:
//	void Init();
//	void Uninit();
//	void Update();
//	void Draw();
//
//};


#pragma once


class Posteffect
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;

	//ここに	シェーダー関連の変数を追加
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	float	m_Threshold;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


};