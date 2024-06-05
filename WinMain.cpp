#include <Windows.h>
#include<tchar.h>
#include "Direct3D.h"
#include "Quad.h"
#include "Camera.h"

using namespace Direct3D;

const wchar_t * WIN_CLASS_NAME = L"SampleGame";
const wchar_t* APP_NAME = L"Error";
const int WINDOW_WIDTH = 800;  //�E�B���h�E�̕�
const int WINDOW_HEIGHT = 600; //�E�B���h�E�̍���

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
    wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
    wc.lpszClassName = WIN_CLASS_NAME;          //�E�B���h�E�N���X��
    wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
    wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);       //�A�C�R��
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
    wc.hCursor = LoadCursor(NULL, IDC_WAIT);    //�}�E�X�J�[�\��
    wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
    RegisterClassEx(&wc); //�N���X��o�^

    //�E�B���h�E�T�C�Y�̌v�Z(�\���̈��WINDOW_WIDTH x WINDOW_HEIGHT�Ɏw�肷�邽�߂̌v�Z)
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //�E�B���h�E��
    int winH = winRect.bottom - winRect.top;     //�E�B���h�E����


    HWND hWnd = CreateWindow(
        WIN_CLASS_NAME,         //�E�B���h�E�N���X��
        APP_NAME,     //�^�C�g���o�[�ɕ\��������e
        WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
        CW_USEDEFAULT,       //�\���ʒu���i���܂����j
        CW_USEDEFAULT,       //�\���ʒu��i���܂����j
        winW,        //�E�B���h�E��
        winH,       //�E�B���h�E����
        NULL,                //�e�E�C���h�E�i�Ȃ��j
        NULL,                //���j���[�i�Ȃ��j
        hInstance,           //�C���X�^���X
        NULL                 //�p�����[�^�i�Ȃ��j
    );

    ShowWindow(hWnd, nCmdShow);


    //Direct3D������
   HRESULT hr =  Direct3D::Initialize(winW, winH, hWnd);
   Camera::Initialize();

    Quad* q = new Quad;
    q->Initialize();

    if (FAILED(hr))
    {
        MessageBox(NULL, L"Direct3D�̏������Ɏ��s���܂���", L"Error", NULL);
        return hr;
    }

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //���b�Z�[�W����
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //���b�Z�[�W�Ȃ�
        else
        {
            //�J�������X�V
            Camera::Update();
            //�Q�[���̏���
            Direct3D::BeginDraw();

            static float rot = 0;
            rot+= 0.25;
            //�`�揈��
            XMMATRIX rmat = XMMatrixRotationY(XMConvertToRadians((float)rot));

            static float factor = 0.0f;
            factor += 0.01;
            //float scale = 1.5 + sin(factor);
            //XMMATRIX smat = XMMatrixScaling(scale, scale, scale);

            //XMMATRIX mat = smat * rmat;

            //�P�ʍs��́A�����̂P�Ɠ���
            XMMATRIX mat = XMMatrixIdentity();

            XMMATRIX tmat = XMMatrixTranslation(2.0*cos(factor),sin(factor), 0);
            
            mat = rmat * tmat;
            //�����Ɏ��O�̕`�揈����ǉ����Ă���
            //�`�揈��
            q -> Draw(mat);
            
            
            Direct3D::EndDraw();
        }
    }

    SAFE_DELETE(q);
    Direct3D::Release();

	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:

        PostQuitMessage(0);  //�v���O�����I��
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}