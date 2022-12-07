//===================================================//
//                                                   //
//    　  アクションゲームリザルト画面ファイル   　  //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "Result.h"
#include "fade.h"

LPDIRECT3DTEXTURE9 g_apTextureResult = NULL;	    //テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureResultFlame = NULL;
LPDIRECT3DTEXTURE9 g_apTextureResultTarotMaster = NULL;
LPDIRECT3DTEXTURE9 g_apTextureResultSun = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;		//頂点バッファへのポインタ
bool g_bWin;
int g_nAnimResult;
int g_nCntResultAnim, g_nResultPattern1, g_nResultPattern2;

//リザルト画面の初期化処理
void InitResult(bool bWin)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	g_bWin = bWin;
	g_nCntResultAnim = 0;
	g_nResultPattern1 = 0;
	g_nResultPattern2 = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Results.png",
		&g_apTextureResult);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Fire_Sprite.png",
		&g_apTextureResultFlame);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TarotMaster_Sprite.png",
		&g_apTextureResultTarotMaster);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\XIX TheSun.png",
		&g_apTextureResultSun);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	if (g_bWin == false)
	{
		pVtx[4].pos = D3DXVECTOR3(110.0f, 580.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(310.0f, 580.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(110.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(310.0f, SCREEN_HEIGHT, 0.0f);

		pVtx[8].pos = D3DXVECTOR3(970.0f, 580.0f, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(1170.0f, 580.0f, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(970.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(1170.0f, SCREEN_HEIGHT, 0.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[7].tex = D3DXVECTOR2(0.5f, 0.5f);

		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[11].tex = D3DXVECTOR2(0.5f, 0.5f);
	}
	else
	{
		pVtx[4].pos = D3DXVECTOR3(700.0f, 400.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(1000.0f, 400.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(700.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(1000.0f, SCREEN_HEIGHT, 0.0f);

		pVtx[8].pos = D3DXVECTOR3(200.0f, 1.0f, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(400.0f, 1.0f, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(200.0f, 201.0f, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(400.0f, 201.0f, 0.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.750f);
		pVtx[5].tex = D3DXVECTOR2(0.125f, 0.750f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 0.875f);
		pVtx[7].tex = D3DXVECTOR2(0.125f, 0.875f);

		pVtx[8].tex = D3DXVECTOR2(0.125f, 0.250f);
		pVtx[9].tex = D3DXVECTOR2(0.25f, 0.250f);
		pVtx[10].tex = D3DXVECTOR2(0.125f, 0.375f);
		pVtx[11].tex = D3DXVECTOR2(0.25f, 0.375f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	if (bWin == true)
	{
		PlaySound(SOUND_LABEL_BGMWIN);
	}
	else
	{
		PlaySound(SOUND_LABEL_BGMGAMEOVER);
	}
}

//リザルト画面の終了処理
void UninitResult(void)
{
	//テクスチャの破棄
	if (g_apTextureResult != NULL)
	{
		g_apTextureResult->Release();
		g_apTextureResult = NULL;
	}
	if (g_apTextureResultFlame != NULL)
	{					 
		g_apTextureResultFlame->Release();
		g_apTextureResultFlame = NULL;
	}
	if (g_apTextureResultTarotMaster != NULL)
	{			   
		g_apTextureResultTarotMaster->Release();
		g_apTextureResultTarotMaster = NULL;
	}
	if (g_apTextureResultSun != NULL)
	{					 
		g_apTextureResultSun->Release();
		g_apTextureResultSun = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//リザルト画面の更新処理
void UpdateResult(void)
{
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	g_nCntResultAnim++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
	if (g_bWin == false)
	{
		if (g_nCntResultAnim % 7 == 6)
		{
			g_nResultPattern1++;
			g_nResultPattern2++;

			if (g_nResultPattern1 >= 4)
			{
				g_nResultPattern1 = 0;
			}
			if (g_nResultPattern2 >= 4)
			{
				g_nResultPattern2 = 0;
			}
		}


		pVtx[4].tex = D3DXVECTOR2(0.0f + (0.5f * g_nResultPattern1), 0.0f + (0.5f * g_nResultPattern1) + 0.011f);
		pVtx[5].tex = D3DXVECTOR2(0.5f + (0.5f * g_nResultPattern1), 0.0f + (0.5f * g_nResultPattern1) + 0.011f);
		pVtx[6].tex = D3DXVECTOR2(0.0f + (0.5f * g_nResultPattern1), 0.5f + (0.5f * g_nResultPattern1));
		pVtx[7].tex = D3DXVECTOR2(0.5f + (0.5f * g_nResultPattern1), 0.5f + (0.5f * g_nResultPattern1));

		pVtx[8].tex = D3DXVECTOR2(0.0f + (0.5f * g_nResultPattern2), 0.0f + (0.5f * g_nResultPattern2) + 0.011f);
		pVtx[9].tex = D3DXVECTOR2(0.5f + (0.5f * g_nResultPattern2), 0.0f + (0.5f * g_nResultPattern2) + 0.011f);
		pVtx[10].tex = D3DXVECTOR2(0.0f + (0.5f * g_nResultPattern2), 0.5f + (0.5f * g_nResultPattern2));
		pVtx[11].tex = D3DXVECTOR2(0.5f + (0.5f * g_nResultPattern2), 0.5f + (0.5f * g_nResultPattern2));
	}
	else
	{
		if (g_nCntResultAnim % 15 == 14)
		{
			g_nResultPattern1++;

			if (g_nResultPattern1 >= 4)
			{
				g_nResultPattern1 = 0;
			}
		}
		if (g_nCntResultAnim % 10 == 9)
		{
			g_nResultPattern2++;

			if (g_nResultPattern2 >= 4)
			{
				g_nResultPattern2 = 0;
			}
		}

		pVtx[4].tex = D3DXVECTOR2(0.0f + (0.125f * g_nResultPattern1), 0.750f);
		pVtx[5].tex = D3DXVECTOR2(0.125f + (0.125f * g_nResultPattern1), 0.750f);
		pVtx[6].tex = D3DXVECTOR2(0.0f + (0.125f * g_nResultPattern1), 0.875f);
		pVtx[7].tex = D3DXVECTOR2(0.125f + (0.125f * g_nResultPattern1), 0.875f);

		pVtx[8].tex = D3DXVECTOR2(0.125f + (0.125f * g_nResultPattern2), 0.250f);
		pVtx[9].tex = D3DXVECTOR2(0.25f + (0.125f * g_nResultPattern2), 0.250f);
		pVtx[10].tex = D3DXVECTOR2(0.125f + (0.125f * g_nResultPattern2), 0.375f);
		pVtx[11].tex = D3DXVECTOR2(0.25f + (0.125f * g_nResultPattern2), 0.375f);
	}
	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);



	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//エンターキーを押したら

		PlaySound(SOUND_LABEL_SE_CLICK);

		SetFade(MODE_RANKING);
	}
}

//リザルト画面の描画処理
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureResult);

	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (g_bWin == false)
	{
		pDevice->SetTexture(0, g_apTextureResultFlame);

		//四角形を描画する
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);
	}
	else
	{
		pDevice->SetTexture(0, g_apTextureResultTarotMaster);

		//四角形を描画する
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

		pDevice->SetTexture(0, g_apTextureResultSun);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);
	}
	
}