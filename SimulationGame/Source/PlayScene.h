#pragma once
#include "Crop.h"
class PlayScene
{
private:
	Crop crops[4];

	// Playerの現在の水の量
	int playerWater;

	// Playerの最大水量
	int maxPlayerWater;

	// Playerの所持金
	int money;

	// 畑の維持費
	int runningCost = 3;

	bool prevNextDayKey;
	bool prevAddWaterKey;
	bool prevHarvestKey;
	bool prevRefillKey;

	// 選択中
	int selectIndex = 0;

	// ゲームオーバーか
	bool isGameOver;

public:
	PlayScene();
	~PlayScene();

	void Update();
	void Draw();
};