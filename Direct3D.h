#pragma once
#include <d3d11.h>

//�����J
#pragma comment(lib, "d3d11.lib")

namespace Direct3D
{
	//const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
 //   const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���


	//������
	void Initialize(int winW, int winH, HWND hWnd);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
};
