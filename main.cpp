//==========================================//
//                                          //
//         　 2D アクションゲーム    　     //
//            Author: Ricci Alex            //
//                                          //
//==========================================//

////インクルードファイル
#include "main.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "Result.h"
#include "sound.h"
#include "fade.h"
#include "Ranking.h"

//マクロ定義
#define CLASS_NAME		"WindowClass"			//ウインドウクラスの名前
#define WINDOW_NAME		"Cultist Life"			//ウインドウの名前

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
MODE g_Mode = MODE_TITLE;
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;

//メイン関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),							//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,									//ウインドウのスタイル
		WindowProc,									//ウインドウプロシージャ
		0,											//0にする
		0,											//0にする
		hInstance,									//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),				//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),					//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),					//クライアント領城の背景色
		NULL,										//メニューバー
		CLASS_NAME,									//ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)				//ファイルのアイコン
	};

	HWND hWnd;										//ウインドウハンドル
	MSG msg;										//メッセージを格納する変数

	RECT rect = { 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(0,						//拡張ウインドウスタイル
		CLASS_NAME,									//ウインドウクラスの名前
		WINDOW_NAME,								//ウインドウの名前
		WS_OVERLAPPEDWINDOW,						//ウインドウスタイル
		CW_USEDEFAULT,								//ウインドウの左上X座標
		CW_USEDEFAULT,								//ウインドウの右上Y座標
		(rect.right - rect.left),								//ウインドウの幅
		(rect.bottom - rect.top),								//ウインドウの高さ
		NULL,										//親ウインドウのハンドル
		NULL,										//メニューハンドル又は子ウインドウID
		hInstance,									//インスタンスハンドル
		NULL);										//ウインドウ生成データ


	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);						//ウインドウの表示状態を設定

	UpdateWindow(hWnd);								//クライエント領域を更新

	//メッセージループ
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
				//メッセージの設定
				TranslateMessage(&msg);						//仮想キーメッセージを文字メッセージに変換

				DispatchMessage(&msg);						//ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
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

				//更新処理
				Update();
				//描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:							//ウインドウ破棄のメッセージ
												//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:							//キー押下のメッセージ

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);				//既定の処理を返す

}

//初期化処理
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;					//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;			//プレゼンテーションパラメータ	

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//ディスプレイのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							//バックバッファの形式
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;							//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして16バイトを使う
	d3dpp.Windowed = bWindow;										//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスの生成(描画処理と頂点処理をハードウェアで行う)
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成(描画処理はハードウェアで、頂点処理はCPUで行う)
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化処理
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

//終了処理
void Uninit(void)
{
	UninitGame();

	UninitTitle();

	UninitResult();

	UninitScore();

	UninitSound();

	UninitFade();

	//キーボードの終了処理
	UninitKeyboard();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3オブジェクトの破棄
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

//更新処理
void Update(void)
{
	FADE fade;

	fade = GetFade();

	//キーボードの更新処理
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

//描画処理
void Draw(void)
{

	//画面クリア(バックバッファ＆Zバッファのクリア)
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

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
		//FPSの描画処理
		DrawFPS();

#endif // _DEBUG

		

		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//デバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//モードの設定
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

//モードの取得
MODE GetMode(void)
{
	return g_Mode;
}

//FPSの描画処理
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0], "FPS: %d\n", g_nCountFPS);

	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}