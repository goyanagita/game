#pragma once

#include "gameObject.h"
#include "model.h"

class Yoyo :public GameObject
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int m_SpawnTimer = 0.0f;
	int m_SpawnInterval = 5.0f; // インターバルを5秒に設定
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};