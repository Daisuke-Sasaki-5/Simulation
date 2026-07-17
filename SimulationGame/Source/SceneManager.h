#pragma once
#include "TitleScene.h"
#include "PlayScene.h"

class SceneManager
{
public:
	SceneManager();

	void Update();
	void Draw();

	void ChangeScene(SceneType scene);

private:
	SceneType currentScene;

	TitleScene titleScene;
	PlayScene playScene;
};