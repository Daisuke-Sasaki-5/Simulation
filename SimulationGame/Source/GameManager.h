#pragma once

class PlayScene;

class GameManager
{
private:
	bool isGameOver = false;
	bool isGameClear = false;

public:
	void CheckGameOver(const PlayScene& scene);
	void CheckGameClear(const PlayScene& scene);

	bool IsGameOver()const;
	bool IsGameClear()const;

	void Reset();
};