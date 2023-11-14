#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"
#include "manager.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Update()
{
    Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	//トップビュー(３Ｄマリオ)
	/*m_Target = player->GetPosition();
	m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);*/

	//サードパーソンビュー（フォートナイト）
	//m_Target = player->GetPosition() + player->GetRight() * 0.5f + +D3DXVECTOR3(0.0f, 2.0f, 0.0f);;
	//m_Position = m_Target - player->GetForward() * 5.0f + D3DXVECTOR3(0.0f, 1.0f, -1.0f);

	//ファーストパーソンビュー(ヴァロラント)
	m_Position = player->GetPosition() + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	m_Target = m_Position + player->GetForward();
}

void Camera::Draw()
{
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);
}

