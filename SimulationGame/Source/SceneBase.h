#pragma once
#include "SceneType.h"

class SceneBase
{
public:
	virtual ~SceneBase() = default;

	virtual SceneType Update() = 0;
	virtual void Draw() = 0;
};