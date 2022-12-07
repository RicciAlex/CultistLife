#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#pragma once
#include <Windows.h>
#include "d3dx9.h"
#include "xaudio2.h"

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

#define SCREEN_WIDTH		(1280)
#define SCREEN_HEIGHT		(720)
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//画面(モード)の種類
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME_FIRSTSTAGE_1,
	MODE_GAME_FIRSTSTAGE_2,
	MODE_GAME_FIRSTSTAGE_BOSS,
	MODE_GAME_BONUSSTAGE,
	MODE_GAME_SECONDSTAGE_1,
	MODE_GAME_SECONDSTAGE_BOSS,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX
}MODE;

//頂点情報[2]の構造体を設定
typedef struct
{
	D3DXVECTOR3 pos;		//頂点の座標
	float rhw;				//座標変換用係数(1.0ｆで固定)
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_2D;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawFPS(void);

#endif // !_MAIN_H_
