#pragma once
#include "SceneBase.h"

class TitleScene : public SceneBase
{
public:
	SceneType Update() override;
	void Draw() override;

private :
	int escExitImageHandle = -1;

	bool prevEnterKey = false;
	bool prevEscKey = false;

	bool IsPressedOnce(int key, bool& prevFlag);
};