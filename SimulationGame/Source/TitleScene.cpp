#include "TitleScene.h"
#include "DxLib.h"

SceneType TitleScene::Update()
{
	if (IsPressedOnce(KEY_INPUT_RETURN, prevEnterKey))
	{
		return SceneType::Play;
	}

	if (IsPressedOnce(KEY_INPUT_ESCAPE,prevEscKey))
	{
		DxLib_End();
		exit(0);
	}

	return SceneType::Title;
}

bool TitleScene::IsPressedOnce(int key, bool& prevFlag)
{
	if (CheckHitKey(key))
	{
		if (!prevFlag)
		{
			prevFlag = true;
			return true;
		}
	}
	else
	{
		prevFlag = false;
	}

	return false;
}

void TitleScene::Draw()
{
	DrawString(500, 200, "TITLE", GetColor(255, 255, 255));
	DrawString(420, 350, "Press Enter", GetColor(255, 255, 255));
	DrawString(420, 400, "ESC : Exit", GetColor(255, 255, 255));
}


