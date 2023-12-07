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
	// �v���C���[�̈ʒu���擾
	Scene* scene = Manager::GetScene();
	Player* player = Manager::GetScene()->GetGameObject<Player>();
	D3DXVECTOR3 playerPosition = player->GetPosition();

	// �G����v���C���[�ւ̃x�N�g�����v�Z
	D3DXVECTOR3 direction = playerPosition - GetPosition();
	D3DXVec3Normalize(&direction, &direction); // �x�N�g���𐳋K��

	// ���̑��x�ňړ�
	float speed = 0.1f; // �K�؂ȑ��x��ݒ肵�Ă�������
	D3DXVECTOR3 newPosition = GetPosition() + direction * speed;

	// �V�����ʒu���Z�b�g
	SetPosition(newPosition);

	// �ʏ��Update�����𑱍s
	GameObject::Update();
}

void Yoyo::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
