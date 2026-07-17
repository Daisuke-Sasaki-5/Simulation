#pragma once
#include "Crop.h"
#include "GameManager.h"
#include "DrawImageManager.h"
#include "MessageManager.h"
#include "SceneBase.h"

class PlayScene : public SceneBase
{
private:
	GameManager gameManager;
	DrawImageManager drawImageManager;
	MessageManager messageManager;

	// Image
	int CarrotHandle;

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
	bool prevLeftKey;
	bool prevRightKey;
	bool prevPlantKey;

	bool prevEscKey;

	bool prevSeed1Key;
	bool prevSeed2Key;
	bool prevSeed3Key;

	// 選択中
	int selectIndex = 0;

	CropType selectCropType = CropType::Cheap;

	bool IsKeyPressedOnce(int key, bool& prevFlag);

	// Update関数分け

	void UpdateSelectField();
	void UpdateSelectSeed();

	void UpdateInput();

	void UpdateNextDay();
	void UpdateWater();
	void UpdateHarvest();
	void UpdatePlant();
	int GetSeedPrice(CropType type);
	void UpdateRefill();

	// Draw関数分け
	void DrawCropInfo();   // 作物の表示
	void DrawCropState();  // 作物の状態の表示

public:
	PlayScene();
	~PlayScene();

	SceneType Update() override;
	void Draw() override;

	// 外部参照用
	int GetMoney() const;
	int GetPlayerWater() const;
	int GetMaxPlayerWater() const;
	int GetRunningCost() const;
	int GetSelectIndex() const;
	CropType GetSelectCropType()const;

	const Crop& GetCrop(int index)const;
};