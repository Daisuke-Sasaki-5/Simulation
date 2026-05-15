#include "PlayScene.h"
#include "DxLib.h"

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		crop.NextDay();
	}
}

void PlayScene::Draw()
{

}
