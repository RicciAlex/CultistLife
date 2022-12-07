//===================================//
//                                   //
//	     背景を表示するファイル		 //
//         Author: Ricci Alex	     //
//                                   //
//===================================//

//インクルードファイル
#include "bg.h"

//マクロ定義
#define NUM_BG		(3)								//背景の数

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBg[NUM_BG] = {};	    //テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureBlack = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;		//頂点バッファへのポインタ
float g_aPosTexV[NUM_BG];							//テクスチャ座標の開始位置					

//背景の初期化処理
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	g_aPosTexV[0] = 0.0f;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BgStoneWall.png",
		&g_apTextureBg[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg102.png",
		&g_apTextureBg[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bg101.png",
		&g_apTextureBg[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BlackBG.png",
		&g_apTextureBlack);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	//背景の位置の初期化
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, SCREEN_HEIGHT, 0.0f);

	pVtx[8].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, 0.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.0f, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 180);

	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 180);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 180);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(g_aPosTexV[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_aPosTexV[0] + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_aPosTexV[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aPosTexV[0] + 1.0f, 1.0f);

	pVtx[4].tex = D3DXVECTOR2(0.0f, g_aPosTexV[0]);
	pVtx[5].tex = D3DXVECTOR2(1.0f, g_aPosTexV[0]);
	pVtx[6].tex = D3DXVECTOR2(0.0f, g_aPosTexV[0] + 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, g_aPosTexV[0] +1.0f);

	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}

//背景の終了処理
void UninitBg(void)
{

	//テクスチャの破棄
	if (g_apTextureBg[0] != NULL)
	{
		g_apTextureBg[0]->Release();
		g_apTextureBg[0] = NULL;
	}
	if (g_apTextureBg[1] != NULL)
	{
		g_apTextureBg[1]->Release();
		g_apTextureBg[1] = NULL;
	}
	if (g_apTextureBg[2] != NULL)
	{				  
		g_apTextureBg[2]->Release();
		g_apTextureBg[2] = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//背景の更新処理
void UpdateBg(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	g_aPosTexV[0] += 0.001f;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + 1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f + 1.0f, 1.0f);

	pVtx[4].tex = D3DXVECTOR2(0.0f, -0.7f * g_aPosTexV[0]);
	pVtx[5].tex = D3DXVECTOR2(1.0f, -0.7f * g_aPosTexV[0]);
	pVtx[6].tex = D3DXVECTOR2(0.0f, -0.7f * g_aPosTexV[0] + 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, -0.7f * g_aPosTexV[0] + 1.0f);

	pVtx[8].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0], -0.4f * g_aPosTexV[0]);
	pVtx[9].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0] + 1.0f, -0.4f * g_aPosTexV[0]);
	pVtx[10].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0], -0.4f * g_aPosTexV[0] + 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.5f * g_aPosTexV[0] + 1.0f, -0.4f * g_aPosTexV[0] + 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}

//背景の描画処理
void DrawBg(void)
{
	MODE mode;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	//モードの取得
	mode = GetMode();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (mode == MODE_GAME_BONUSSTAGE)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBlack);
	}
	else
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBg[0]);
	}
	
	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, g_apTextureBg[1]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	pDevice->SetTexture(0, g_apTextureBg[2]);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);
}