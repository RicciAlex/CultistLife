#include "main.h"
#include "score.h"

//グローバル変数を宣言する
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posScore;
int g_nScore;

//スコアの初期化処理
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCount;						//数をカウントする変数を宣言する

									//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureScore);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	//グローバル変数の初期化
	g_posScore = D3DXVECTOR3(900.0f, 35.0f, 0.0f);

	g_nScore = 1500;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//頂点の設定
		pVtx[0].pos = D3DXVECTOR3(900.0f + (25.0f * nCount), 35.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(925.0f + (25.0f * nCount), 35.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(900.0f + (25.0f * nCount), 75.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(925.0f + (25.0f * nCount), 75.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//スコアの終了処理
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//スコアの更新処理
void UpdateScore(void)
{
	Player*pPlayer;

	pPlayer = GetPlayer();

	//スコアの設定
	SetScore(g_nScore);

	if (g_nScore <= 0)
	{
		pPlayer->state = PLAYERSTATE_DEATH;
	}
}

//スコアの描画処理
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//四角形を描画する
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//スコアの設定処理
void SetScore(int nScore)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int aPosTexU[8];
	int nCount;						//数をカウントする変数を宣言する

									//デバイスの取得
	pDevice = GetDevice();
	g_nScore = nScore;

	//スコアの各桁を計算する
	aPosTexU[0] = (g_nScore % 100000000) / 10000000;
	aPosTexU[1] = (g_nScore % 10000000) / 1000000;
	aPosTexU[2] = (g_nScore % 1000000) / 100000;
	aPosTexU[3] = (g_nScore % 100000) / 10000;
	aPosTexU[4] = (g_nScore % 10000) / 1000;
	aPosTexU[5] = (g_nScore % 1000) / 100;
	aPosTexU[6] = (g_nScore % 100) / 10;
	aPosTexU[7] = (g_nScore % 10);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

	//スコアの取得
	GetRank(g_nScore);
}

void AddScore(int nValue)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int aPosTexU[8];
	int nCount;

	//デバイスの取得
	pDevice = GetDevice();

	//スコアに加算する
	g_nScore += nValue;

	//スコアの各桁を計算する
	aPosTexU[0] = (g_nScore % 100000000) / 10000000;
	aPosTexU[1] = (g_nScore % 10000000) / 1000000;
	aPosTexU[2] = (g_nScore % 1000000) / 100000;
	aPosTexU[3] = (g_nScore % 100000) / 10000;
	aPosTexU[4] = (g_nScore % 10000) / 1000;
	aPosTexU[5] = (g_nScore % 1000) / 100;
	aPosTexU[6] = (g_nScore % 100) / 10;
	aPosTexU[7] = (g_nScore % 10);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < 8; nCount++)
	{
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount] * 0.1f), 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}