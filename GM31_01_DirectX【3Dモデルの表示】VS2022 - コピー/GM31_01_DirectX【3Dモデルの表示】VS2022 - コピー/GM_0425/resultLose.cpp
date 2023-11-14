#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "polygon2D.h"
#include "game.h"
#include "resultLose.h"
#include "title.h"
#include "resultLogoLose.h"
#include "fade.h"
#include "audio.h"


void ResultLose::Init()
{
	AddGameObject<ResultLogoLose>(2);
	AddGameObject<Fade>(2);

	//BGMçƒê∂
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\bgm\\Lose.wav");
	bgm->Play(true);

}

void ResultLose::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
}
