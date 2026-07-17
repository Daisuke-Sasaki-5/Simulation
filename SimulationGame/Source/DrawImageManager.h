#pragma once

#include "MessageManager.h"
class PlayScene;

class  DrawImageManager
{
public:
	 DrawImageManager();
	~ DrawImageManager();

	void Draw(const PlayScene& scene, const MessageManager& message);

private:
	int BackGround;

	int bigFont;

	int handle;

	int slotHandle;

	int playerInfoHandle;
	int controlIHandle;

	int MessageHandle;
	int selectImage;

	int carrotHandle;
	int PumpkinHandle;
	int tomatoHandle;

	int carrotgrawHandle;
	int PumpkingrawHandle;
	int tomatograwHandle;

	int emptyHandle;
	int deadHandle;
	int seedHandle;

	void DrawSlot();
	void DrawCrop(const PlayScene& scene);
	void DrawCropBar(const PlayScene& scene);
	void DrawBar(int x, int y, int width, int height, float rate, int color);
	void DrawPlayerInfo(const PlayScene& scene);
	void DrawSelectField(const PlayScene& scene);
	void DrawSelectSeed(const PlayScene& scene);
};
