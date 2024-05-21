#pragma once
#include <d3d11.h>

//リンカ
#pragma comment(lib, "d3d11.lib")

namespace Direct3D
{
	//const int WINDOW_WIDTH = 800;  //ウィンドウの幅
 //   const int WINDOW_HEIGHT = 600; //ウィンドウの高さ


	//初期化
	void Initialize(int winW, int winH, HWND hWnd);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();
};
