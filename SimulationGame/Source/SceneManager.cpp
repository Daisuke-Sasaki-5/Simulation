#include "SceneManager.h"
#include "DxLib.h"

SceneManager::SceneManager()
{
	currentScene = SceneType::Title;
	nextScene = SceneType::Title;

	isShowingStartInfo = false;
	startInfoTimer = 0;
}

void SceneManager::Update()
{
	// フェード中ならフェードだけ更新
	if (!fadeManager.IsFinished())
	{
		fadeManager.Update();

		// フェードアウトが完了したらシーン変更
		if (fadeManager.IsFadeOutFinished())
		{
			ChangeScene(nextScene);
		}
		return;
	}

	// ゲーム開始説明表示中
	if (isShowingStartInfo)
	{
		startInfoTimer++;

		if (startInfoTimer >= StartInfoDisplayFrame)
		{
			isShowingStartInfo = false;
			startInfoTimer = 0;
		}
		return;
	}

	switch (currentScene)
	{
	case SceneType::Title:
		if (titleScene.Update() == SceneType::Play)
		{
			nextScene = SceneType::Play;
			fadeManager.Start();
		}
		break;

	case SceneType::Play:
		if (playScene.Update() == SceneType::Title)
		{
			ChangeScene(SceneType::Title);
		}
		break;
	}
}

void SceneManager::Draw()
{
	switch (currentScene)
	{
	case SceneType::Title:
		drawImageManager.DrawTitle();
		break;
	case SceneType::Play:
		playScene.Draw();
		break;
	}

	// 開始説明画像
	if (isShowingStartInfo)
	{
		drawImageManager.DrawStartInfo();
	}

	// 最後にフェードを描画
	fadeManager.Draw();
}

void SceneManager::ChangeScene(SceneType scene)
{
	if (scene == SceneType::Play)
	{
		playScene.Reset();

		isShowingStartInfo = true;
		startInfoTimer = 0;
	}

	currentScene = scene;
}
