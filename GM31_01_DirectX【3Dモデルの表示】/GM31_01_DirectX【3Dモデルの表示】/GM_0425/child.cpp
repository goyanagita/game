#include "main.h"
#include "renderer.h"
#include "child.h"
#include "manager.h"
#include "player.h"

void Child::Init()
{
	//m_Position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	m_Scale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
	m_Rotation = D3DXVECTOR3(0.0f, 135.0f, 0.0f);



	m_Model = new Model();
	m_Model->Load("asset\\model\\stone.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
}

void Child::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Child::Update()
{
	// 通常のUpdate処理を続行
	GameObject::Update();

	m_Rotation.y += 0.1f;
	m_Position.x = 1.0f;
	m_Position.z = -1.0f;
}

void Child::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans * m_Parent->GetMatrix();

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
