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
	SoundManager soundManager;
	FadeManager fadeManager;

	// ===== ゲーム開始演出 =====
	bool isShowingStartInfo;
	int startInfoTimer;

	static constexpr int StartInfoDisplayFrame = 120;
};