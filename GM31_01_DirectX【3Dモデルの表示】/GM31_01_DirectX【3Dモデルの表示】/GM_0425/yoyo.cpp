#include "main.h"
#include "renderer.h"
#include "enemy.h"
#include "manager.h"
#include "player.h"
#include"yoyo.h"

void Yoyo::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
	m_Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	m_Rotation = D3DXVECTOR3(0.0f, 135.0f, 0.0f);



	m_Model = new Model();
	m_Model->Load("asset\\model\\yoyo.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
}

void Yoyo::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Yoyo::Update()
{
	// プレイヤーの位置を取得
	Scene* scene = Manager::GetScene();
	Player* player = Manager::GetScene()->GetGameObject<Player>();
	D3DXVECTOR3 playerPosition = player->GetPosition();

	// 敵からプレイヤーへのベクトルを計算
	D3DXVECTOR3 direction = playerPosition - GetPosition();
	D3DXVec3Normalize(&direction, &direction); // ベクトルを正規化

	// 一定の速度で移動
	float speed = 0.1f; // 適切な速度を設定してください
	D3DXVECTOR3 newPosition = GetPosition() + direction * speed;

	// 新しい位置をセット
	SetPosition(newPosition);

	// 通常のUpdate処理を続行
	GameObject::Update();
}

void Yoyo::Draw()
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
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
