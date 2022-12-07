//==========================================//
//                                          //
//         �@ 2D �A�N�V�����Q�[��    �@     //
//            Author: Ricci Alex            //
//                                          //
//==========================================//

////�C���N���[�h�t�@�C��
#include "main.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "Result.h"
#include "sound.h"
#include "fade.h"
#include "Ranking.h"

//�}�N����`
#define CLASS_NAME		"WindowClass"			//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"Cultist Life"			//�E�C���h�E�̖��O

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_Mode = MODE_TITLE;
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;

//���C���֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),							//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,									//�E�C���h�E�̃X�^�C��
		WindowProc,									//�E�C���h�E�v���V�[�W��
		0,											//0�ɂ���
		0,											//0�ɂ���
		hInstance,									//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),				//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),					//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),					//�N���C�A���g�̏�̔w�i�F
		NULL,										//���j���[�o�[
		CLASS_NAME,									//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)				//�t�@�C���̃A�C�R��
	};

	HWND hWnd;										//�E�C���h�E�n���h��
	MSG msg;										//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(0,						//�g���E�C���h�E�X�^�C��
		CLASS_NAME,									//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,								//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,						//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,								//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,								//�E�C���h�E�̉E��Y���W
		(rect.right - rect.left),								//�E�C���h�E�̕�
		(rect.bottom - rect.top),								//�E�C���h�E�̍���
		NULL,										//�e�E�C���h�E�̃n���h��
		NULL,										//���j���[�n���h�����͎q�E�C���h�EID
		hInstance,									//�C���X�^���X�n���h��
		NULL);										//�E�C���h�E�����f�[�^


	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);						//�E�C���h�E�̕\����Ԃ�ݒ�

	UpdateWindow(hWnd);								//�N���C�G���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);						//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�

				DispatchMessage(&msg);						//�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//�X�V����
				Update();
				//�`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�C���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:							//�E�C���h�E�j���̃��b�Z�[�W
												//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:							//�L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);				//����̏�����Ԃ�

}

//����������
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;					//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;			//�v���[���e�[�V�����p�����[�^	

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�B�X�v���C�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16�o�C�g���g��
	d3dpp.Windowed = bWindow;										//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A�ŁA���_������CPU�ōs��)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_������CPU�ōs��)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	InitSound(hWnd);

	InitFade(MODE_TITLE);
	//InitGame();
	//SetMode(MODE_TITLE);

	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	return S_OK;
}

//�I������
void Uninit(void)
{
	UninitGame();

	UninitTitle();

	UninitResult();

	UninitScore();

	UninitSound();

	UninitFade();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//�X�V����
void Update(void)
{
	FADE fade;

	fade = GetFade();

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	UpdateFade();


	switch (g_Mode)
	{
	default:
		break;
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_GAME_FIRSTSTAGE_1:
		if (fade != FADE_OUT)
		{
			UpdateGame();
		}
		break;
	case MODE_GAME_FIRSTSTAGE_2:
		if (fade != FADE_OUT)
		{
			UpdateGame();
		}
		break;
	case MODE_GAME_FIRSTSTAGE_BOSS:
		if (fade != FADE_OUT)
		{
			UpdateGame();
		}
		break;
	case MODE_GAME_BONUSSTAGE:
		if (fade != FADE_OUT)
		{
			UpdateGame();
		}
		break;
	case MODE_GAME_SECONDSTAGE_1:
		if (fade != FADE_OUT)
		{
			UpdateGame();
		}
		break;
	case MODE_GAME_SECONDSTAGE_BOSS:
		if (fade != FADE_OUT)
		{
			UpdateGame();
		}
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_RANKING:
		UpdateRanking();
		break;

	}
}

//�`�揈��
void Draw(void)
{

	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		switch (g_Mode)
		{
		default:
			break;
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_GAME_FIRSTSTAGE_1:
			DrawGame();
			break;
		case MODE_GAME_FIRSTSTAGE_2:
			DrawGame();
			break;
		case MODE_GAME_FIRSTSTAGE_BOSS:
			DrawGame();
			break;
		case MODE_GAME_BONUSSTAGE:
			DrawGame();
			break;
		case MODE_GAME_SECONDSTAGE_1:
			DrawGame();
			break;
		case MODE_GAME_SECONDSTAGE_BOSS:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		case MODE_RANKING:
			DrawRanking();
			break;
		}

		DrawFade();

#ifdef _DEBUG
		//FPS�̕`�揈��
		DrawFPS();

#endif // _DEBUG

		

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//���[�h�̐ݒ�
void SetMode(MODE mode)
{
	bool bWin;

	bWin = GetWin();

	switch (g_Mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME_FIRSTSTAGE_1:
		UninitGame();
		break;
	case MODE_GAME_FIRSTSTAGE_2:
		UninitGame();
		break;
	case MODE_GAME_FIRSTSTAGE_BOSS:
		UninitGame();
		break;
	case MODE_GAME_BONUSSTAGE:
		UninitGame();
		break;
	case MODE_GAME_SECONDSTAGE_1:
		UninitGame();
		break;
	case MODE_GAME_SECONDSTAGE_BOSS:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_RANKING:
		UninitRanking();
		break;
	}

	g_Mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_GAME_FIRSTSTAGE_1:
		InitTutorial();
		InitScore();
		InitGame();
		break;
	case MODE_GAME_FIRSTSTAGE_2:
		PlaySound(SOUND_LABEL_SE_LEVELCHANGE);
		InitGame();
		break;
	case MODE_GAME_FIRSTSTAGE_BOSS:
		PlaySound(SOUND_LABEL_SE_LEVELCHANGE);
		InitGame();
		break;

	case MODE_GAME_BONUSSTAGE:
		InitGame();
		break;

	case MODE_GAME_SECONDSTAGE_1:
		PlaySound(SOUND_LABEL_SE_LEVELCHANGE);
		InitGame();
		break;

	case MODE_GAME_SECONDSTAGE_BOSS:
		PlaySound(SOUND_LABEL_SE_LEVELCHANGE);
		InitGame();
		break;

	case MODE_RESULT:
		InitResult(bWin);
		break;

	case MODE_RANKING:
		InitRanking();
		SetRanking();
		break;
	}
}

//���[�h�̎擾
MODE GetMode(void)
{
	return g_Mode;
}

//FPS�̕`�揈��
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0], "FPS: %d\n", g_nCountFPS);

	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}