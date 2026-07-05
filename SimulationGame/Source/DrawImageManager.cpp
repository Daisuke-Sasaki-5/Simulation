#include "DrawImageManager.h"
#include "PlayScene.h"
#include "DxLib.h"

DrawImageManager::DrawImageManager()
{
	carrotHandle = LoadGraph("Data/Image/Carrot.png");
	PumpkinHandle = LoadGraph("Data/Image/Pumpkin.png");
	tomatoHandle = LoadGraph("Data/Image/Tomato.png");

	carrotgrawHandle = LoadGraph("Data/Image/CarrotGraw.png");
	PumpkingrawHandle = LoadGraph("Data/Image/PumpkinGraw.png");
	tomatograwHandle = LoadGraph("Data/Image/TomatoGraw.png");

	emptyHandle = LoadGraph("Data/Image/Empty.png");
	deadHandle = LoadGraph("Data/Image/Dead.png");
	seedHandle = LoadGraph("Data/Image/Seed.png");

	slotHandle = LoadGraph("Data/Image/Slot.png");
}

DrawImageManager::~DrawImageManager()
{
}

void DrawImageManager::Draw(const PlayScene& scene)
{
	DrawSlot();
	DrawCrop(scene);
	DrawCropBar(scene);
}

void DrawImageManager::DrawSlot()
{
	// スロット表示
	for (int i = 0; i < 4; i++)
	{
		DrawGraph(300, 53 + i * 150, slotHandle, TRUE);
	}
}

void DrawImageManager::DrawCrop(const PlayScene& scene)
{
	// 作物表示
	for (int i = 0; i < 4; i++)
	{
		const Crop& crop = scene.GetCrop(i);

		switch (scene.GetCrop(i).GetState())
		{
			// 土表示
		case CropState::Empty:
			handle = emptyHandle;
			break;

			// 種表示
		case CropState::Seed:
			handle = seedHandle;
			break;

			// 枯れた状態表示
		case CropState::Dead:
			handle = deadHandle;
			break;

			// 成長途中表示
		case CropState::Growing:
			switch (crop.GetType())
			{
			case CropType::Cheap:
				handle = carrotgrawHandle;
				break;
			case CropType::Normal:
				handle = tomatograwHandle;
				break;
			case CropType::Rare:
				handle = PumpkingrawHandle;
				break;
			}
			break;

			// 収穫可能状態表示
		case CropState::Harvest:
			switch (crop.GetType())
			{
			case CropType::Cheap:
				handle = carrotHandle;
				break;
			case CropType::Normal:
				handle = tomatoHandle;
				break;
			case CropType::Rare:
				handle = PumpkinHandle;
				break;
			}
			break;
		}
		DrawExtendGraph(300, 70 + i * 150, 500, 200 + i * 150, handle, TRUE);
	}
}

void DrawImageManager::DrawCropBar(const PlayScene& scene)
{
	for (int i = 0; i < 4; i++)
	{
		const Crop& crop = scene.GetCrop(i);

		float growRate = (float)crop.GetGrowth() / crop.GetMaxGrowth();
		float waterRate = (float)crop.GetWater() / crop.GetMaxWater();
		
		DrawBar(520, 100 + i * 150, 120, 35, growRate, GetColor(255, 255, 0));
		DrawBar(520, 140 + i * 150, 120, 35, waterRate, GetColor(0, 255, 255));
	
		// % 表示
		DrawFormatString(650, 110 + i * 150, GetColor(255, 255, 255), "%d%%", (int)(growRate * 100));
		DrawFormatString(650, 150 + i * 150, GetColor(255, 255, 255), "%d%%", (int)(waterRate * 100));
	}
}

void DrawImageManager::DrawBar(int x, int y, int width, int height, float rate, int color)
{
	// 枠
	DrawBox(x, y, x + width, y + height, GetColor(255, 255, 255), FALSE);

	// rateを0～1に制限
	if (rate < 0.0f)rate = 0.0f;
	if (rate > 1.0f)rate = 1.0f;

	DrawBox(x, y, x + width * rate, y + height, color, TRUE);
}

