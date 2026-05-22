#pragma once
#include "Crop.h"
class PlayScene
{
private:
	Crop crop;

	// Player‚ÌŒ»İ‚Ì…‚Ì—Ê
	int playerWater;

	// Player‚ÌÅ‘å…—Ê
	int maxPlayerWater;

	// Player‚ÌŠ‹à
	int money;

	bool prevNextDayKey;
	bool prevAddWaterKey;
	bool prevHarvestKey;

public:
	PlayScene();
	~PlayScene();

	void Update();
	void Draw();
};