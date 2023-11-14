#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "polygon2D.h"
#include "game.h"
#include "resultPerfect.h"
#include "title.h"
#include "resultLogoPerfect.h"
#include "fade.h"
#include "audio.h"


void ResultPerfect::Init()
{
	AddGameObject<ResultLogoPerfect>(2);
	AddGameObject<Fade>(2);

	//BGMçƒê∂
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\bgm\\Perfect.wav");
	bgm->Play(true);

}

void ResultPerfect::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
}
