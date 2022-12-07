//===================================================//
//                                                   //
//     アクションゲームタイトル画面の ファイル   　  //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "title.h"
#include "fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureTitle = NULL;	    //テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureStart = NULL;	    //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
int g_AnimStart, g_PatternStart;
float  g_ShrinkStart;

//タイトルの初期化処理
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	pDevice = GetDevice();			//デバイスの取得
	g_AnimStart = 0;
	g_PatternStart = 1;
	g_ShrinkStart = 0.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Title.png",
		&g_apTextureTitle);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PressStart.png",
		&g_apTextureStart);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 6,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGMTITLE);
}

//タイトルの終了処理
void UninitTitle(void)
{
	//テクスチャの破棄
	if (g_apTextureTitle != NULL)
	{
		g_apTextureTitle->Release();
		g_apTextureTitle = NULL;
	}
	if (g_apTextureStart != NULL)
	{			   
		g_apTextureStart->Release();
		g_apTextureStart = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//タイトルの更新処理
void UpdateTitle(void)
{
	if (g_PatternStart > 0)
	{
		g_ShrinkStart += 1.0f;
	}
	else
	{
		g_ShrinkStart -= 1.0f;
	}

	if (g_ShrinkStart > 100.0f || g_ShrinkStart < 0.0f)
	{
		g_PatternStart *= -1;
	}

	VERTEX_2D*pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[4].pos = D3DXVECTOR3(0.0f - g_ShrinkStart, 0.0f - (g_ShrinkStart * 0.4f), 0.0f);
	pVtx[5].pos = D3DXVECTOR3(SCREEN_WIDTH + g_ShrinkStart, 0.0f - (g_ShrinkStart * 0.4f), 0.0f);
	pVtx[6].pos = D3DXVECTOR3(0.0f - g_ShrinkStart, SCREEN_HEIGHT + (g_ShrinkStart * 0.4f), 0.0f);
	pVtx[7].pos = D3DXVECTOR3(SCREEN_WIDTH + g_ShrinkStart, SCREEN_HEIGHT + (g_ShrinkStart * 0.4f), 0.0f);

	pVtx[4].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);
	pVtx[5].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);
	pVtx[6].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);
	pVtx[7].col = D3DXCOLOR(0.7f +  (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 0.7f + (g_ShrinkStart * 0.003), 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//次の画面に進む

		PlaySound(SOUND_LABEL_SE_CLICK);

		SetFade(MODE_GAME_FIRSTSTAGE_1);
	}
}

//タイトルの描画処理
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureTitle);

	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, g_apTextureStart);

	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);
}