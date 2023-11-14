#pragma once
#include "gameObject.h"
#include <list>
#include <typeinfo>
#include <vector>


class Scene
{
protected:
	std::list<GameObject*> m_GameObject[3];   //STLのリスト構造

public:
	virtual void Init(){}

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{

			for (GameObject* gameObject : m_GameObject[i])
			{
				gameObject->Uninit();
				delete gameObject;
			}

			m_GameObject[i].clear();  //リスト構造の削除

		}
	}
	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{

			for (GameObject* gameObject : m_GameObject[i]) //範囲forループ
			{
				gameObject->Update();

			}

			//ラムダ式
			m_GameObject[i].remove_if([](GameObject* object) 
			                         {return object->Destroy(); });
		}
	}
	void Draw()
	{
		for (int i = 0; i < 3; i++)
		{

			for (GameObject* gameObject : m_GameObject[i])
			{
				gameObject->Draw();

			}
		}
	}

	template <typename T>
	T*  AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <typename T>
	T* GetGameObject()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//型を調べる（RTTI動的型情報）
				{
					return (T*)object;
				}
			}
		}

		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;

		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//型を調べる（RTTI動的型情報）
				{
					objects.push_back((T*)object);
				}
			}
		}

		return objects;

	}

};
