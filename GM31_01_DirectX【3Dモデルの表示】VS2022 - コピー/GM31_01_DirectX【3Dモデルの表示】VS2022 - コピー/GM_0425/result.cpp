#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "polygon2D.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "resultLogo.h"
#include "fade.h"
#include "audio.h"


void Result::Init()
{
	AddGameObject<ResultLogo>(2);
	AddGameObject<Fade>(2);

	//BGMçƒê∂
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\bgm\\Normal.wav");
	//bgm->Play(true);

}

void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
}
