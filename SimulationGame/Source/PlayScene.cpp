#include "PlayScene.h"
#include "DxLib.h"

PlayScene::PlayScene()
{
	playerWater = 10;
	maxPlayerWater = 10;

	// 初期所持金
	money = 100;

	crops[0] = Crop(CropType::Cheap);
	crops[1] = Crop(CropType::Cheap);
	crops[2] = Crop(CropType::Normal);
	crops[3] = Crop(CropType::Rare);

	isGameOver = false;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	// 作物の選択
	if (CheckHitKey(KEY_INPUT_1))selectIndex = 0;
	if (CheckHitKey(KEY_INPUT_2))selectIndex = 1;
	if (CheckHitKey(KEY_INPUT_3))selectIndex = 2;
	if (CheckHitKey(KEY_INPUT_4))selectIndex = 3;

	// スペースキーで次の日へ進める
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (prevNextDayKey == false)
		{
			for (int i = 0; i < 4; i++)
			{
				crops[i].NextDay();
			}
			money -= 10;

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
		if (!prevAddWaterKey)
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
	else
	{
		prevAddWaterKey = false;
	}
	
		// 収穫状態の時
	if (crops[selectIndex].CanHarvest())
	{
		// Entnerキーで収穫する
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			if (prevHarvestKey == false)
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

				crops[selectIndex] = Crop(type);
			}
			prevHarvestKey = true;
		}
		else
		{
			prevHarvestKey = false;
		}
	}

	// お金が0以下になら
	if (money <= 0)
	{
		isGameOver = true;
	}
}

void PlayScene::Draw()
{
	for (int i = 0; i < 4; i++)
	{
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

		// 成長割合計算
		float growtRate = (float)crops[i].GetGrowth() / crops[i].GetMaxGrowth();

		int barLength = 10;
		int fillLength = growtRate * barLength;

		DrawFormatString(100, 100 + i * 100, waterColor, TEXT("Water : %d"), crops[i].GetWater());
		DrawFormatString(100, 150 + i * 100, GetColor(255, 255, 255), TEXT("Growth : %d"), crops[i].GetGrowth());
	}

	DrawFormatString(50, 100 + selectIndex * 100, GetColor(255, 255, 0), ">");

	// 作物状態によって文字を変える
	for (int i = 0; i < 4; i++)
	{
		const char* stateText = "Unknown";

		switch (crops[i].GetState())
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
		DrawFormatString(300, 300 + i * 30, GetColor(255, 255, 0), TEXT("State[%d] : %s"), i, stateText);
	}

	// 水タンク表示
	DrawFormatString(300, 550, GetColor(255, 255, 255), TEXT("Tank : %d / %d"), playerWater, maxPlayerWater);

	// 所持金表示
	DrawFormatString(300, 600, GetColor(255, 255, 255), TEXT("Money : %d"), money);

	if (isGameOver)
	{
		DrawString(400, 300, "GAME OVER", GetColor(255, 0, 0));
	}
}
