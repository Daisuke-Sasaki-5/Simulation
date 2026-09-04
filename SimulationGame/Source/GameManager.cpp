#include "GameManager.h"
#include "PlayScene.h"

void GameManager::CheckGameOver(const PlayScene& scene)
{
	/// <summary>
	/// ゲームオーバー判定
	/// </summary>
	
	// ==== ゲームオーバー条件を明確に ====

	// 収穫できる作物が1つでもあるか?
		auto canHarvest = [&]()
			{
				for (int i = 0; i < 4; i++)
				{
					if (scene.GetCrop(i).CanHarvest())return true;
				}
				return false;
			}();

		// 次の日へ進めるか?
		auto canNextDay = (scene.GetMoney() >= scene.GetRunningCost());

		// 水を補充できるか
		auto canRefill = [&]()
			{
				int needWater = scene.GetMaxPlayerWater() - scene.GetPlayerWater();
				int refillCost = needWater * 2;
				return scene.GetMoney() >= refillCost;
			}();

		// 水を補充するお金もなく、作物も収穫できないなら
		if (!canHarvest && !canNextDay && !canRefill)
		{
			isGameOver = true;
		}
}

void GameManager::CheckGameClear(const PlayScene& scene)
{
	if (scene.GetMoney() >= 300)
	{
		isGameClear = true;
	}
}

bool GameManager::IsGameOver() const
{
	return isGameOver;
}

bool GameManager::IsGameClear() const
{
	return isGameClear;
}

void GameManager::Reset()
{
	isGameOver = false;
	isGameClear = false;
}
