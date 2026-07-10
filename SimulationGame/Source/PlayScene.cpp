#include "PlayScene.h"
#include "DxLib.h"
#include <string>

PlayScene::PlayScene()
{
	playerWater = 10;
	maxPlayerWater = 10;

	// 初期所持金
	money = 100;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (gameManager.IsGameOver() || gameManager.IsGameClear()) { return; }

	UpdateInput();

	UpdateNextDay();
	UpdateWater();
	UpdateHarvest();
	UpdatePlant();
	UpdateRefill();

	gameManager.CheckGameOver(*this);
	gameManager.CheckGameClear(*this);
}

void PlayScene::Draw()
{
	drawImageManager.Draw(*this);

	//DrawCropInfo();
	//DrawCropState();

	// 選択中の種表示
	const char* seedName = "";

	switch (selectCropType)
	{
	case CropType::Cheap:
		seedName = "Cheap";
		break;
	case CropType::Normal:
		seedName = "Normal";
		break;
	case CropType::Rare:
		seedName = "Rare";
		break;
	}

	DrawFormatString(300, 650, GetColor(255, 255, 255), "Selected : %s", seedName);

	if (gameManager.IsGameOver())
	{
		DrawString(400, 300, "GAME OVER", GetColor(255, 0, 0));
	}

	if (gameManager.IsGameClear())
	{
		DrawString(400, 300, "GAME Clear", GetColor(0, 255, 0));
	}
}

/// <summary>
/// 外部参照用
/// </summary>
/// <returns></returns>

int PlayScene::GetMoney() const
{
	return money;
}

int PlayScene::GetPlayerWater() const
{
	return playerWater;
}

int PlayScene::GetMaxPlayerWater() const
{
	return maxPlayerWater;
}

int PlayScene::GetRunningCost() const
{
	return runningCost;
}

int PlayScene::GetSelectIndex() const
{
	return selectIndex;
}

const Crop& PlayScene::GetCrop(int index) const
{
	return crops[index];
}

// キー入力を共通化
bool PlayScene::IsKeyPressedOnce(int key, bool& prevFlag)
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

void PlayScene::UpdateSelectField()
{
	// ←
	if (IsKeyPressedOnce(KEY_INPUT_LEFT, prevLeftKey))
	{
		selectIndex--;

		if (selectIndex < 0)
		{
			selectIndex = 3;
		}
	}

	// →
	if (IsKeyPressedOnce(KEY_INPUT_RIGHT, prevRightKey))
	{
		selectIndex++;

		if (selectIndex >= 4)
		{
			selectIndex = 0;
		}
	}
}

void PlayScene::UpdateSelectSeed()
{
	if (IsKeyPressedOnce(KEY_INPUT_1, prevSeed1Key))
	{
		selectCropType = CropType::Cheap;
	}
	if (IsKeyPressedOnce(KEY_INPUT_2, prevSeed2Key))
	{
		selectCropType = CropType::Normal;
	}
	if (IsKeyPressedOnce(KEY_INPUT_3, prevSeed3Key))
	{
		selectCropType = CropType::Rare;
	}
}

/// <summary>
/// 入力関係
/// </summary>
void PlayScene::UpdateInput()
{
	UpdateSelectField();
	UpdateSelectSeed();
}

/// <summary>
/// 日数経過
/// </summary>
void PlayScene::UpdateNextDay()
{
	// スペースキーで次の日へ進める
	if (IsKeyPressedOnce(KEY_INPUT_SPACE, prevNextDayKey))
	{
		for (int i = 0; i < 4; i++)
		{
			crops[i].NextDay();
		}
		money -= runningCost;
	}
}

/// <summary>
/// 水やり
/// </summary>
void PlayScene::UpdateWater()
{
	// Wキーで水を増やす
	if (IsKeyPressedOnce(KEY_INPUT_W, prevAddWaterKey))
	{
		// Playerが水を１以上持っているとき
		if (playerWater >= 1)
		{
			crops[selectIndex].AddWater(1);

			playerWater--;
		}
		prevAddWaterKey = true;
	}
}

/// <summary>
/// 収穫
/// </summary>
void PlayScene::UpdateHarvest()
{
	// 収穫状態の時
	if (crops[selectIndex].CanHarvest())
	{
		// Entnerキーで収穫する
		if (IsKeyPressedOnce(KEY_INPUT_RETURN, prevHarvestKey))
		{
			CropType type = crops[selectIndex].GetType();

			int sellPrice = crops[selectIndex].GetPrice();

			float waterRate = (float)crops[selectIndex].GetWater() / crops[selectIndex].GetMaxWater();

			// 作物の残りの水の割合で売値に補正をかける
			if (waterRate >= 0.8f)
			{
				sellPrice *= 1.2f;
			}
			else if (waterRate >= 0.4f)
			{
			}
			else if (waterRate > 0)
			{
				sellPrice *= 0.5f;
			}

			money += sellPrice;

			crops[selectIndex].Clear();
		}
	}
}

/// <summary>
/// 植える
/// </summary>
void PlayScene::UpdatePlant()
{
	if (crops[selectIndex].GetState() != CropState::Empty) { return; }

	if (IsKeyPressedOnce(KEY_INPUT_P, prevPlantKey))
	{
		int cost = GetSeedPrice(selectCropType);

		if (money >= cost)
		{
			money -= cost;
			crops[selectIndex] = Crop(selectCropType);
		}
	}
}

/// <summary>
/// 価格取得
/// </summary>
int PlayScene::GetSeedPrice(CropType type)
{
	switch (type)
	{
	case CropType::Cheap:
		return 5;
		
	case CropType::Normal:
		return 20;

	case CropType::Rare:
		return 35;
	}

	return 0;
}

/// <summary>
/// 給水
/// </summary>
void PlayScene::UpdateRefill()
{
	// 水の補充
	if (IsKeyPressedOnce(KEY_INPUT_R, prevRefillKey))
	{
		int neadWater = maxPlayerWater - playerWater;

		int cost = neadWater * 2;

		if (money >= cost)
		{
			money -= cost;

			playerWater = maxPlayerWater;
		}
	}
}

/// <summary>
/// 作物の成長度合いの表示
/// </summary>
void PlayScene::DrawCropInfo()
{
	for (int i = 0; i < 4; i++)
	{
		if (crops[i].GetState() == CropState::Empty)
		{
			DrawString(100, 100 + i * 100, "Empty", GetColor(255, 255, 255));
			continue;
		}

		// 水割合を計算
		float waterRate = (float)crops[i].GetWater() / crops[i].GetMaxWater();

		int waterColor;

		if (waterRate <= 0.2f)
		{
			waterColor = GetColor(255, 0, 0);
		}
		else if (waterRate <= 0.5f)
		{
			waterColor = GetColor(255, 255, 0);
		}
		else
		{
			waterColor = GetColor(0, 255, 0);
		}

		DrawFormatString(100, 100 + i * 100, waterColor, TEXT("Water : %d"), crops[i].GetWater());
		DrawFormatString(100, 150 + i * 100, GetColor(255, 255, 255), TEXT("Growth : %d"), crops[i].GetGrowth());

		if (crops[i].GetState() == CropState::Empty)
		{
			DrawString(100, 130 + i * 100, "Empty", GetColor(200, 200, 200));
		}
	}
}

/// <summary>
/// 作物の状態表示
/// </summary>
void PlayScene::DrawCropState()
{
	// 作物状態によって文字を変える
	for (int i = 0; i < 4; i++)
	{
		const char* stateText = "Unknown";

		switch (crops[i].GetState())
		{
		case CropState::Empty:
			stateText = "Empty";
			break;

		case CropState::Seed:
			stateText = "Seed";
			break;

		case CropState::Growing:
			stateText = "Growing";
			break;

		case CropState::Harvest:
			stateText = "Harvest";
			break;

		case CropState::Dead:
			stateText = "Dead";
			break;
		}

		// 状態表示
		DrawFormatString(300, 300 + i * 30, GetColor(255, 255, 0), TEXT("State[%d] : %s"), i, stateText);
	}
}
