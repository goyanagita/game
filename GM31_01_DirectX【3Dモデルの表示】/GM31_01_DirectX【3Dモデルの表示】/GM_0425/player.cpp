#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "scene.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "shadow.h"
#include "animationModel.h"
#include "meshField.h"
#include "gameObject.h"
#include "office.h"
void Player::Init()
{
	/*m_Model = new Model();
	m_Model->Load("asset\\model\\Car.obj");*/

	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Remy.fbx"); 
	m_Model->LoadAnimation("asset\\model\\Walking.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\Walking.fbx", "Idle");
	//m_Model->LoadAnimation("asset\\model\\Bot_Run.fbx", "Run");
	//m_Model->LoadAnimation("asset\\model\\Bot_Idle.fbx","Idle");

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.007f, 0.007f, 0.007f);

	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,"shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,"shader\\vertexLightingPS.cso");*/

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/toon.png",
		NULL,
		NULL,
		&m_ToonTexture,
		NULL);
	assert(m_ToonTexture);
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\toonVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\toonPS.cso");

	


	m_ShotSE = AddComponent<Audio>();
	m_ShotSE->Load("asset\\bgm\\jyuu.wav");

	m_Jump = AddComponent<Audio>();
	m_Jump->Load("asset\\bgm\\Jump.wav");

	m_Shadow = AddComponent<Shadow>();

}

void Player::Uninit()
{
	GameObject::Uninit();

	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	/*m_ToonTexture->Release();*/
}

void Player::Update()
{
	GameObject::Update();


	D3DXVECTOR3 oldPosition = m_Position;

	//�g�b�v�r���[
	/*if (Input::GetKeyPress('A'))
	{
		m_Position.x -= 0.1f;
	}

	if (Input::GetKeyPress('D'))
	{
		m_Position.x += 0.1f;
	}

	if (Input::GetKeyPress('W'))
	{
		m_Position.z += 0.1f;
	}

	if (Input::GetKeyPress('S'))
	{
		m_Position.z -= 0.1f;
	}*/

	//�e����

	Scene* scene = Manager::GetScene();
	if (Input::GetKeyTrigger('L'))
	{
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		bullet->SetVelocity(GetForward() * 0.2f);

		//m_ShotSE->Play();
	}

	//�X�e�[�g�}�V��
	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;
	case PLAYER_STATE_JUMP:
		UpdateJump();
		break;
	default:
		break;
	}

	//�d��
	m_Velocity.y -= 0.015f;

	//�ړ�
	m_Position += m_Velocity;


	//��Q���Ƃ̏Փ˔���

	float groundHeight;

	MeshField* meshField = scene->GetGameObject<MeshField>();
	groundHeight = meshField->GetHeight(m_Position);

	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();

	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 position = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();
		D3DXVECTOR3 rifht = cylinder->GetRight();//X������
		D3DXVECTOR3 forward = cylinder->GetForward();//Z������
		D3DXVECTOR3 direction = m_Position - position;//�~�`����v���C���[�܂ł̕����x�N�g��
		//obbx�͔��̒��S����v���C���[�܂ł̂�����

		direction.y = 0.0f;
		float lenght = D3DXVec3Length(&direction);

		if (lenght < scale.x)
		{
			if (m_Position.y < position.y + scale.y - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;

			}
			else
			{
				groundHeight = position.y + scale.y;
			}

			break;
		}


	}


	std::vector<Box*> boxes = scene->GetGameObjects<Box>();

	for (Box* box : boxes)
	{
		D3DXVECTOR3 position = box->GetPosition();
		D3DXVECTOR3 scale = box->GetScale();

		if (position.x - scale.x - 0.5f < m_Position.x &&
			m_Position.x < position.x + scale.x + 0.5f &&
			position.z - scale.z - 0.5f < m_Position.z &&
			m_Position.z < position.z + scale.z + 0.5f)
		{
			if (m_Position.y < position.y + scale.y *  2.0f - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y * 2.0f;
			}

			break;
		}


	}

	std::vector<Office*> office = scene->GetGameObjects<Office>();

	for (Office* office : office)
	{
		D3DXVECTOR3 position = office ->GetPosition();
		D3DXVECTOR3 scale = office->GetScale();

		if (position.x - scale.x - 0.1f < m_Position.x &&
			m_Position.x < position.x + scale.x + 0.1f &&
			position.z - scale.z - 0.1f < m_Position.z &&
			m_Position.z < position.z + scale.z + 0.1f)
		{
			if (m_Position.y < position.y + scale.y *  2.0f - 0.1f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}
			else
			{
				groundHeight = position.y + scale.y * 2.0f;
			}

			break;
		}


	}
	//�ڒn
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;

		m_IsGround = true;
	}
	else
	{
		m_IsGround = false;
	}

	D3DXVECTOR3 shadowPosition = m_Position;
	shadowPosition.y = groundHeight;
	m_Shadow->SetPosition(shadowPosition);

	/*
	g_TexAnime += 0.01f;
	if (g_TexAnime > 1.1f)
		g_TexAnime - 0.0f;*/
}

void Player::Draw()
{
	GameObject::Draw();

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
	m_Matrix = world;

	Renderer::SetWorldMatrix(&world);
	// �g�D�[���e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_ToonTexture);
	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);

	//m_Model->Update("Idle", m_Time, "Run", m_Time, m_BlendRate);
	m_Time++;
	m_BlendRate += 0.05f;

	if (m_BlendRate > 1.0f)
	{
		m_BlendRate = 1.0f;
	}
	////�X�V�����p�����[�^���V�F�[�_�[�֓n��
	//PARAMETER param;
	//param.Parameter.X = g_TexAnimme;
	//Renderer::SetParameter(param);

	m_Model->Draw();
}

void Player::UpdateGround()
{
	bool move = false;

	//�T�[�h�p�[�\���r���[

	if (Input::GetKeyPress('A'))
	{
		m_Position -= GetRight() * 0.1;
		move = true;
	}

	if (Input::GetKeyPress('D'))
	{
		m_Position += GetRight() * 0.1f;
		move = true;

	}

	if (Input::GetKeyPress('W'))
	{
		if (m_NextAnimationName != "Run")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Run";
			m_BlendRate = 0.0f;
		}

		m_Position += GetForward() * 0.1f;
		move = true;
	}

	if (Input::GetKeyPress('S'))
	{
		m_Position -= GetForward() * 0.1f;
		move = true;
	}

	if (move == false)
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}
	}


	if (Input::GetKeyPress('Q'))
	{
		m_Rotation.y -= 0.1f;
	}

	if (Input::GetKeyPress('E'))
	{
		m_Rotation.y += 0.1f;
	}


	//�W�����v
	if (Input::GetKeyTrigger('J'))
	{
		m_Velocity.y = 0.35f;
		//m_Jump->Play();

		m_PlayerState = PLAYER_STATE_JUMP;
	}
}

void Player::UpdateJump()
{
	if (m_IsGround == true)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}
