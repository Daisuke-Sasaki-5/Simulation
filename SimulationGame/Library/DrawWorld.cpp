#include <DxLib.h>
#include "../Source/Screen.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);
	SetMainWindowText(Screen::WINDOW_NAME);
	SetWindowSizeExtendRate(Screen::WINDOW_EXTEND);
	ChangeWindowMode(Screen::WINDOW_MODE); // Windowモードの場合

	// ImGui
	//ImGui::CreateContext();
	//ImGui_ImplDXlib_Init();

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();

		ScreenFlip();

		//ImGui_ImplDXlib_NewFrame();
		//ImGui::NewFrame();

		//ImGui::Begin("Debug");
		//ImGui::Text("Hello ImGui");
		//ImGui::End;

		//ImGui::Render();
		//ImGui_ImplDXlib_RenderDrawData();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}