#pragma once

/// <summary>
/// 作物成長状態
/// </summary>
enum class CropState
{
	Seed,    // 種
	Growing, // 成長
	Harvest, // 収穫
	Dead     // 枯れる 
};

class Crop
{
private:
	// 現在の水分量
	int water;

	// 最大の水分量
	int maxWater;

	// 成長度(0～100)
	int growth;

	// 成長に必要な日数
	int growDays;

	// 作物の1日ごとの水分消費量
	int waterDecay;

	// 作物ごとの成長スピード
	int growthSpeed;

	// 作物ごとの収穫可能日数
	int maxGrouth;

	// 売値
	int price;

	// 作物の状態
	CropState state;

public:
	Crop();
	~Crop();

	void Update();
	void Draw();

	// 1日進める
	void NextDay();

	// 水を与える
	void AddWater(int amont);

	// 収穫可能か?
	bool CanHarvest() const;

	// getter(表示確認用)
	int GetWater() const;
	int GetGrowth() const;

	CropState GetState() const;

};