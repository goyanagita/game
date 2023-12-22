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

	// テクスチャ読み込み
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

	//トップビュー
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

	//弾発射

	Scene* scene = Manager::GetScene();
	if (Input::GetKeyTrigger('L'))
	{
		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		bullet->SetVelocity(GetForward() * 0.2f);

		//m_ShotSE->Play();
	}

	//ステートマシン
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

	//重力
	m_Velocity.y -= 0.015f;

	//移動
	m_Position += m_Velocity;


	//障害物との衝突判定

	float groundHeight;

	MeshField* meshField = scene->GetGameObject<MeshField>();
	groundHeight = meshField->GetHeight(m_Position);

	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();

	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 position = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();
		D3DXVECTOR3 rifht = cylinder->GetRight();//X軸分離
		D3DXVECTOR3 forward = cylinder->GetForward();//Z軸分離
		D3DXVECTOR3 direction = m_Position - position;//円形からプレイヤーまでの方向ベクトル
		//obbxは箱の中心からプレイヤーまでのｘ距離

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
	//接地
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
	m_Matrix = world;

	Renderer::SetWorldMatrix(&world);
	// トゥーンテクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &m_ToonTexture);
	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);

	//m_Model->Update("Idle", m_Time, "Run", m_Time, m_BlendRate);
	m_Time++;
	m_BlendRate += 0.05f;

	if (m_BlendRate > 1.0f)
	{
		m_BlendRate = 1.0f;
	}
	////更新したパラメータをシェーダーへ渡す
	//PARAMETER param;
	//param.Parameter.X = g_TexAnimme;
	//Renderer::SetParameter(param);

	m_Model->Draw();
}

void Player::UpdateGround()
{
	bool move = false;

	//サードパーソンビュー

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


	//ジャンプ
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
