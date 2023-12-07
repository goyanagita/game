#pragma once
#include "scene.h"

class Tutorial : public Scene
{
private:
	class Fade* m_Fade{};


public:
	void Init() override;
	void Uninit() override;
	void Update()override;
};