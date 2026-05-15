#pragma once
#include "Crop.h"
class PlayScene
{
private:
	Crop crop;

public:
	PlayScene();
	~PlayScene();

	void Update();
	void Draw();
};