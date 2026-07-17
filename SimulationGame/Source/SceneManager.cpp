#include "SceneManager.h"
#include "DxLib.h"

SceneManager::SceneManager()
{
	currentScene = SceneType::Title;
}

void SceneManager::Update()
{
	switch (currentScene)
	{
	case SceneType::Title:
		if (titleScene.Update() == SceneType::Play)
		{
			ChangeScene(SceneType::Play);
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
		titleScene.Draw();
		break;
	case SceneType::Play:
		playScene.Draw();
		break;
	}
}

void SceneManager::ChangeScene(SceneType scene)
{
	currentScene = scene;
}
