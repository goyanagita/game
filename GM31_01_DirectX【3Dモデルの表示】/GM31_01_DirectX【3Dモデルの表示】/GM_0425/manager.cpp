#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "title.h"
#include "input.h"
#include "audio.h"
#include"camera.h"
#include"polygon2D.h"
#include"Player.h"
#include"field.h"
#include"Posteffect.h"
Scene* Manager::m_Scene{};   //静的メンバ変数は再宣言が必要
Scene* Manager::m_NextScene{};

Polygon2D* g_Polygon;
Field* g_Field;
Camera* g_Camera;
Player* g_Player;
Posteffect*g_Posteffect;

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();
	g_Posteffect = new Posteffect();
	g_Posteffect->Init();
	SetScene<Title>();
}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	g_Posteffect->Uninit();
	delete g_Posteffect;
	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();
	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
		
	}
	m_Scene->Update();

	g_Posteffect->Update();
}

void Manager::Draw()
{
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetLight(light);

	Renderer::BeginPP();
	

	m_Scene->Draw();
	
	////1パス目　レンダリング用テクスチャに描画 タイトルシーン
	/*Renderer::Begin();*/

	
	

	//2パス目	ポストエフェクト行いつつバックバッファに描画
	Renderer::Begin();
	
	light.Enable = false;
	Renderer::SetLight(light);
	
	g_Posteffect->Draw();
	
	Renderer::End();
}

