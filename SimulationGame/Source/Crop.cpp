#include "Crop.h"
#include "PlayScene.h"

Crop::Crop()
{
	// 作物・水初期化

	water = 20;
	maxWater = 20;

	growth = 0;

	growDays = 0;

	waterDecay = 1;

	price = 10;

	state = CropState::Seed;
}

Crop::~Crop()
{
}

void Crop::Update()
{
}

void Crop::Draw()
{
}

void Crop::NextDay()
{
	// 水を減らす;
	water -= waterDecay;

	if (water < 0)
	{
		water = 0;
	}

	// 水がある場合
	if (water > 0)
	{
		// 成長を進める
		growth += growthSpeed;

		if (growth >= maxGrouth)
		{
			// 収穫可能
			state = CropState::Harvest;
		}
		else
		{
			// 成長状態にする
			state = CropState::Growing;
		}
	}
	else
	{
		// 枯れ状態
		state = CropState::Dead;
	}
}

void Crop::AddWater(int amont)
{
	// 水を増やす
	water += amont;

	// 最大値を超えない
	if (maxWater <= water)
	{
		water = maxWater;
	}
}

bool Crop::CanHarvest() const
{
	// Harvestならtrue
	return state == CropState::Harvest;
}

int Crop::GetWater() const
{
	return water;
}

int Crop::GetGrowth() const
{
	return growth;
}

CropState Crop::GetState() const
{
	return state;
}
