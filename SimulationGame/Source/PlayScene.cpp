#include "PlayScene.h"
#include "DxLib.h"

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
	// スペースキーで次の日へ進める
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (prevNextDayKey == false)
		{
			crop.NextDay();

			// 水タンク補充
			playerWater = maxPlayerWater;
		}
		prevNextDayKey = true;
	}
	else
	{
		prevNextDayKey = false;
	}

	// Wキーで水を増やす
	if (CheckHitKey(KEY_INPUT_W))
	{
		if (prevAddWaterKey == false)
		{
			// Playerが水を１以上持っているとき
			if (playerWater >= 1 && crop.GetState() != CropState::Dead)
			{
				crop.AddWater(1);

				playerWater--;
			}
		}
		prevAddWaterKey = true;
	}
	else
	{
		prevAddWaterKey = false;
	}

	// 収穫状態の時
	if (crop.CanHarvest())
	{
		// Entnerキーで収穫する
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			if (prevHarvestKey == false)
			{
				money += 10;

				crop = Crop();
			}
			prevHarvestKey = true;
		}
		else
		{
			prevHarvestKey = false;
		}
	}
}

void PlayScene::Draw()
{
	DrawFormatString(100, 100, GetColor(255, 255, 255), "Water : %d", crop.GetWater());
	DrawFormatString(100, 150, GetColor(255, 255, 255), "Growth : %d", crop.GetGrowth());

	// 状態表示用文字列
	const char* stateText = " ";

	// 作物状態によって文字を変える
	switch (crop.GetState())
	{
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
	DrawFormatString(100, 200, GetColor(255, 255, 0), "State : %s", stateText);

	// 水タンク表示
	DrawFormatString(100, 250, GetColor(255, 255, 255), "Tank : %d / %d", playerWater, maxPlayerWater);

	// 所持金表示
	DrawFormatString(100, 300, GetColor(255, 255, 255), "Money : %d", money);
}
