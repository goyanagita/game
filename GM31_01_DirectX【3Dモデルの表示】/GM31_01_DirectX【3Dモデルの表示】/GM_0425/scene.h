#pragma once
#include "gameObject.h"
#include <list>
#include <typeinfo>
#include <vector>


class Scene
{
protected:
	std::list<GameObject*> m_GameObject[3];   //STL�̃��X�g�\��

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

			m_GameObject[i].clear();  //���X�g�\���̍폜

		}
	}
	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{

			for (GameObject* gameObject : m_GameObject[i]) //�͈�for���[�v
			{
				gameObject->Update();

			}

			//�����_��
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
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�iRTTI���I�^���j
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
				if (typeid(*object) == typeid(T))//�^�𒲂ׂ�iRTTI���I�^���j
				{
					objects.push_back((T*)object);
				}
			}
		}

		return objects;

	}

};
