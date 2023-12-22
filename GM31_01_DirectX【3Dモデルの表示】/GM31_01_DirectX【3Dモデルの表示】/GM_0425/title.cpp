#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "title.h"
#include "polygon2D.h"
#include "game.h"
#include "titleLogo.h"
#include "audio.h"
#include "fade.h"
#include "tutorial.h"
#include "gameObject.h"


void Title::Init()
{
	AddGameObject<TitleLogo>(2);
	m_Fade = AddGameObject<Fade>(2);

	//BGMçƒê∂
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\bgm\\title.wav");
	//bgm->Play(true);
}

void Title::Update()
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
