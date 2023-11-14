#include "main.h"
#include "manager.h"
#include "renderer.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "tutorial.h"
#include "game.h"
#include "field.h"
#include "camera.h"
#include "player.h"
#include "Enemy.h"
#include "bullet.h"
#include "input.h"
#include "audio.h"
#include "sky.h"
#include "fade.h"
#include "count.h"
#include "score.h"

void Tutorial::Init()
{
	m_Fade = AddGameObject<Fade>(2);
	srand(static_cast<unsigned int>(time(NULL)));

	Bullet::Load();

	AddGameObject<Camera>(0);
	AddGameObject<Sky>(1);
	AddGameObject<Field>(1);
	AddGameObject<Player>(1)->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, -78.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, -40.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, -20.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 0.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 20.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 40.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 60.0f));
	AddGameObject<Score>(2);

	//BGMçƒê∂
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\bgm\\tutorial.wav");
	bgm->Play(true);
}

void Tutorial::Uninit()
{
	Scene::Uninit();
	Bullet::Unload();
}

void Tutorial::Update()
{
	Scene::Update();
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Game>();
	}

}
