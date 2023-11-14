#include "main.h"
#include "manager.h"
#include "renderer.h"
#include <cstdlib>
#include <ctime>   
#include "game.h"
#include "polygon2D.h"
#include "field.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "cylinder.h"
#include "box.h"
#include "input.h"
#include "score.h"
#include "result.h"
#include "audio.h"
#include "sky.h"
#include "fade.h"
#include "count.h"
#include "resultLose.h"
#include "resultPerfect.h"
#include "child.h"
#include "meshField.h"
#include "rock.h"
#include "tree.h"
#include "office.h"
void Game::Init()
{
	srand(static_cast<unsigned int>(time(NULL)));

	Bullet::Load();

	AddGameObject<Camera>(0);
	AddGameObject<Sky>(1);

	MeshField* meshField = AddGameObject<MeshField>(1);

	Player* player = AddGameObject<Player>(1);
	player->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -7.0f));
	Office* office = AddGameObject<Office>(1);
	Office* office1 = AddGameObject<Office>(1);
	office1->SetPosition(D3DXVECTOR3(2.5f, 0.0f, 5.5f));
	office1->SetRotation(D3DXVECTOR3(0.0f, 4.7f, 0.0f));
	Office* office2 = AddGameObject<Office>(1);
	office2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 5.0f));
	office2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < 20; i++)
	{
		Rock* rock = AddGameObject<Rock>(1);

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.y = meshField->GetHeight(pos);

		rock->SetPosition(pos);

	}

	//AddGameObject<Child>(1)->SetParent(player);
	//AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(4.0f, 0.0f, 5.0f));
	//AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-4.0f, 0.0f, 5.0f));
	
	AddGameObject<Tree>(1);
	for (int i = 0; i < 20; i++)
	{
		Tree* tree = AddGameObject<Tree>(1);

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.y = meshField->GetHeight(pos);

		tree->SetPosition(pos);
	}

	/*{
		Cylinder* cylinder = AddGameObject<Cylinder>(1);
		cylinder->SetPosition(D3DXVECTOR3(-8.0f, 0.0f, 5.0f));
		cylinder->SetScale(D3DXVECTOR3(4.0f, 2.0f, 4.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-45.0f, 0.0f, 0.0f));
		box->SetScale(D3DXVECTOR3(40.0f, 1.0f, 40.0f));
	}*/

	/*{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-15.0f, 0.0f, 80.0f));
		box->SetScale(D3DXVECTOR3(60.0f, 1.0f, 40.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
		box->SetScale(D3DXVECTOR3(6.0f, 1.0f, 2.0f));
	}
	
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(8.0f, 0.0f, 0.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 2.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(14.0f, 0.0f, 0.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 3.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(46.0f, 0.0f, 0.0f));
		box->SetScale(D3DXVECTOR3(30.0f, 3.0f, 30.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(46.0f, 0.0f, -32.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 3.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(46.0f, 0.0f, -36.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 2.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(46.0f, 0.0f, -42.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 1.0f, 6.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(46.0f, 0.0f, -65.0f));
		box->SetScale(D3DXVECTOR3(30.0f, 1.0f, 20.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-90.0f, 0.0f, -78.0f));
		box->SetScale(D3DXVECTOR3(30.0f, 1.0f, 20.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-90.0f, 2.0f, -100.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 1.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-90.0f, 3.0f, -106.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 1.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-90.0f, 4.0f, -112.0f));
		box->SetScale(D3DXVECTOR3(3.0f, 1.0f, 2.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-90.0f, 4.0f, -138.0f));
		box->SetScale(D3DXVECTOR3(30.0f, 1.0f, 20.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(90.0f, 1.0f, 38.0f));
		box->SetScale(D3DXVECTOR3(40.0f, 1.0f, 50.0f));
	}*/

	//const int numBox = 20;
	//for (int i = 0; i < numBox; i++)
	//{
	//	Box* box = AddGameObject<Box>(1);

	//	// ランダムな位置を生成（適切な範囲で調整する）
	//	float x = static_cast<float>(rand() % 300 - 100); // -100から100の範囲
	//	float y = static_cast<float>(rand() % 2 - 1); // -100から100の範囲
	//	float z = static_cast<float>(rand() % 300 - 100); // -100から100の範囲
	//	box->SetPosition(D3DXVECTOR3(x, y, z));

	//	float scaleX = static_cast<float>(rand() % 100 - 20); // -100から100の範囲
	//	float scaleZ = static_cast<float>(rand() % 100 - 20); // -100から100の範囲
	//	box->SetScale(D3DXVECTOR3(scaleX, 1.0f, scaleZ));
	//}

	//const int numTrees = 60;
	//for (int i = 0; i < numTrees; i++)
	//{
	//	Tree* tree = AddGameObject<Tree>(1);

	//	// ランダムな位置を生成（適切な範囲で調整する）
	//	float x = static_cast<float>(rand() % 300 - 100); // -100から100の範囲
	//	float z = static_cast<float>(rand() % 300 - 100); // -100から100の範囲
	//	tree->SetPosition(D3DXVECTOR3(x, 0.0f, z));

	//	tree->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	//}

	//const int numEnemies = 60;
	//for (int i = 0; i < numEnemies; i++)
	//{
	//	Enemy* enemy = AddGameObject<Enemy>(1);

	//	// ランダムな位置を生成（適切な範囲で調整する）
	//	float x = static_cast<float>(rand() % 300 - 100); // -100から100の範囲
	//	float z = static_cast<float>(rand() % 300 - 100); // -100から100の範囲
	//	enemy->SetPosition(D3DXVECTOR3(x, 0.0f, z));
	//}

	AddGameObject<Score>(2);
	AddGameObject<Fade>(2);
	AddGameObject<Count>(2);

	//BGM再生
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\bgm\\game.wav");
	//bgm->Play(true);
}

void Game::Uninit()
{
	Scene::Uninit();

	Bullet::Unload();
}

void Game::Update()
{
	Scene::Update();

	Scene* scene = Manager::GetScene();
	Count* count = scene->GetGameObject<Count>();

	for (int i = 0; i < 1; i++)
	{
		count->AddTime(1);
	}

	Score* score = scene->GetGameObject<Score>();
	

	//画面遷移コードをここに書く
	if (Input::GetKeyTrigger(VK_RETURN))//(count->GetTime() == 3000 && score->GetScore() >= 20)
	{
		
		Manager::SetScene<Result>();
	}
	/*if (count->GetTime() == 3000 && score->GetScore() <= 20)
	{

		Manager::SetScene<ResultLose>();
	}
	if (score->GetScore() >= 60)
	{

		Manager::SetScene<ResultPerfect>();
	}*/
	
}
