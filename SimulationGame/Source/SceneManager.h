#pragma once
#include "TitleScene.h"
#include "PlayScene.h"
#include "DrawImageManager.h"
#include "SoundManager.h"
#include "FadeManager.h"

class SceneManager
{
public:
	SceneManager();

	void Update();
	void Draw();

	void ChangeScene(SceneType scene);

private:
	SceneType currentScene;
	SceneType nextScene;

	TitleScene titleScene;
	PlayScene playScene;
	DrawImageManager drawImageManager;
	//SoundManager soundManager;
	FadeManager fadeManager;
};