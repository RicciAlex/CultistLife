#include "Ranking.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include <stdio.h>

//マクロ定義
#define FILENAME_RANKING	"RankingSave"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankingLogo = NULL;			//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankingBg = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		//頂点バッファへのポインタ
int g_nRankPlayer;
int g_aSavedRank[5];
int g_nRankMemory;
int g_nCountAnimRank, g_nAnimPatternRank;
int g_nPatternRankLogo, g_nAnimRankLogo;
int g_nDelayReturn;

//ランキングの初期化処理
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCount, nCount2;			//数をカウントする変数を宣言
	g_nRankMemory = 5;				//プレイヤーのランキングを保存する変数を宣言

	//デバイスの取得
	pDevice = GetDevice();

	//グローバル変数を初期化する
	g_nCountAnimRank = 0;
	g_nAnimPatternRank = -100;
	g_nAnimRankLogo = 0.0f;
	g_nPatternRankLogo = 3;
	g_nDelayReturn = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_rank.png",
		&g_pTextureRanking);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTextureRankingScore);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking_logo.png",
		&g_pTextureRankingLogo);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ranking.png",
		&g_pTextureRankingBg);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 47,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[4].pos = D3DXVECTOR3(340.0f, 100.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(940.0f, 100.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(340.0f, 200.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(940.0f, 200.0f, 0.0f);

	for (nCount = 2; nCount < 7; nCount++)
	{
		pVtx[nCount * 4].pos = D3DXVECTOR3(400.0f, 275.0f + (75.0f * (nCount - 2)), 0.0f);
		pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(450.0f, 275.0f + (75.0f * (nCount - 2)), 0.0f);
		pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(400.0f, 325.0f + (75.0f * (nCount - 2)), 0.0f);
		pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(450.0f, 325.0f + (75.0f * (nCount - 2)), 0.0f);
	}

	for (nCount = 0; nCount < 5; nCount++)
	{
		for (nCount2 = 0; nCount2 < 8; nCount2++)
		{
			pVtx[(nCount * 32) + 28 + (nCount2 * 4)].pos = D3DXVECTOR3(500.0f + (50.0f * (nCount2)), 275.0f + ((75.0f * (nCount))), 0.0f);
			pVtx[(nCount * 32) + 29 + (nCount2 * 4)].pos = D3DXVECTOR3(550.0f + (50.0f * (nCount2)), 275.0f + ((75.0f * (nCount))), 0.0f);
			pVtx[(nCount * 32) + 30 + (nCount2 * 4)].pos = D3DXVECTOR3(500.0f + (50.0f * (nCount2)), 325.0f + ((75.0f * (nCount))), 0.0f);
			pVtx[(nCount * 32) + 31 + (nCount2 * 4)].pos = D3DXVECTOR3(550.0f + (50.0f * (nCount2)), 325.0f + ((75.0f * (nCount))), 0.0f);
		}
	}

	for (nCount = 0; nCount < 7; nCount++)
	{
		//rhwの設定
		pVtx[(nCount * 4) + 0].rhw = 1.0f;
		pVtx[(nCount * 4) + 1].rhw = 1.0f;
		pVtx[(nCount * 4) + 2].rhw = 1.0f;
		pVtx[(nCount * 4) + 3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	for (nCount = 7; nCount < 47; nCount++)
	{
		//rhwの設定
		pVtx[(nCount * 4) + 0].rhw = 1.0f;
		pVtx[(nCount * 4) + 1].rhw = 1.0f;
		pVtx[(nCount * 4) + 2].rhw = 1.0f;
		pVtx[(nCount * 4) + 3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[(nCount * 4) + 0].col = D3DCOLOR_RGBA(25, 25, 25, 255);
		pVtx[(nCount * 4) + 1].col = D3DCOLOR_RGBA(25, 25, 25, 255);
		pVtx[(nCount * 4) + 2].col = D3DCOLOR_RGBA(25, 25, 25, 255);
		pVtx[(nCount * 4) + 3].col = D3DCOLOR_RGBA(25, 25, 25, 255);
	}

	//テクスチャ座標の設定
	for (nCount = 0; nCount < 2; nCount++)
	{
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	for (nCount = 2; nCount < 7; nCount++)
	{
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f + ((nCount - 2) * 0.2f));
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f + ((nCount - 2) * 0.2f));
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.2f + ((nCount - 2) * 0.2f));
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 0.2f + ((nCount - 2) * 0.2f));
	}
	for (nCount = 7; nCount < 47; nCount++)
	{
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();

	//ランキング情報のロード処理
	LoadRanking();
}

//ランキングの終了処理
void UninitRanking(void)
{
	//テクスチャの破棄
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}
	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();
		g_pTextureRankingLogo = NULL;
	}
	if (g_pTextureRankingBg != NULL)
	{
		g_pTextureRankingBg->Release();
		g_pTextureRankingBg = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//ランキングの更新処理
void UpdateRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCount;						//数をカウントする変数を宣言

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//ランキングロゴのアニメーション処理
	g_nCountAnimRank++;
	g_nDelayReturn++;

	g_nAnimRankLogo += g_nPatternRankLogo;

	if (g_nCountAnimRank % 35 == 34)
	{
		g_nPatternRankLogo *= -1;
	}

	pVtx[4].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);
	pVtx[5].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);
	pVtx[6].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);
	pVtx[7].col = D3DCOLOR_RGBA(150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 150 + g_nAnimRankLogo, 255);

	//プレイヤーのランキングアニメーション処理

	if (g_nRankMemory <= 4)
	{
		if (g_nCountAnimRank % 5 == 4)
		{
			g_nAnimPatternRank *= -1;
		}

		for (nCount = 0; nCount < 8; nCount++)
		{
			//頂点カラーの設定
			pVtx[28 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
			pVtx[29 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
			pVtx[30 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
			pVtx[31 + (g_nRankMemory * 32) + (nCount * 4)].col = D3DCOLOR_RGBA(155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 155 + g_nAnimPatternRank, 255);
		}
	}
	
	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{//エンターキーを押す場合
		//ランキングのセーブ処理
		SaveRanking();

		PlaySound(SOUND_LABEL_SE_CLICK);

		//フェードの設定
		SetFade(MODE_TITLE);
	}
	if (g_nDelayReturn >= 800)
	{
		g_nDelayReturn = 0;
		SetFade(MODE_TITLE);
	}
}

//ランキングの描画処理
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;							//数をカウントする変数を宣言

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankingBg);

	//ランキングの背景を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, g_pTextureRankingLogo);

	//ランキングのロゴを描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	pDevice->SetTexture(0, g_pTextureRanking);

	for (nCount = 2; nCount < 7; nCount++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}

	pDevice->SetTexture(0, g_pTextureRankingScore);

	for (nCount = 7; nCount < 47; nCount++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//プレイヤーのスコアを取得
void GetRank(int nRank)
{
	g_nRankPlayer = nRank;
}

//ランキングのセーブ処理
void SaveRanking(void)
{
	FILE*pFile;				//ファイルポインタを宣言する

	//ファイルを開く
	pFile = fopen("data/RankingSave/FILENAME_RANKING", "wb");

	if (pFile != NULL)
	{//ファイルが開けた場合
		//ファイルにランキング情報を書き出す
		fwrite(&g_aSavedRank[0], sizeof(int), 5, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("XXXXX セーブファイルが開けませんでした XXXXX");
	}
}

//ランキングのロード処理
void LoadRanking(void)
{
	FILE*pFile;				//ファイルポインタを宣言する

	//ファイルを開く
	pFile = fopen("data/RankingSave/FILENAME_RANKING", "rb");

	if (pFile != NULL)
	{//ファイルが開けた場合
		//ファイルからランキング情報を読み込む
		fread(&g_aSavedRank[0], sizeof(int), 5, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("XXXXX セーブファイルが開けませんでした XXXXX");
	}
}

//ランキングの設定処理
void SetRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCount, nCount2;			//数をカウントする変数を宣言
	int nMemory;					//ランキング情報を格納する変数を宣言する
	int aPosTexU[5][8];

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーのスコアは保存されたランキングより大きいかどうか確認する
	for (nCount = 4; nCount >= 0; nCount--)
	{
		if (g_nRankPlayer > g_aSavedRank[nCount])
		{
			g_nRankMemory = nCount;
		}
	}

	//バブルソートアルゴリズム
	if (g_nRankPlayer > g_aSavedRank[4])
	{
		g_aSavedRank[4] = g_nRankPlayer;

		for (nCount = 0; nCount < 4; nCount++)
		{
			for (nCount2 = nCount + 1; nCount2 < 5; nCount2++)
			{
				if (g_aSavedRank[nCount] < g_aSavedRank[nCount2])
				{
					nMemory = g_aSavedRank[nCount2];
					g_aSavedRank[nCount2] = g_aSavedRank[nCount];
					g_aSavedRank[nCount] = nMemory;
				}
			}
		}
	}

	for (nCount = 0; nCount < 5; nCount++)
	{
		//スコアの各桁を計算する
		aPosTexU[nCount][0] = (g_aSavedRank[nCount] % 100000000) / 10000000;
		aPosTexU[nCount][1] = (g_aSavedRank[nCount] % 10000000) / 1000000;
		aPosTexU[nCount][2] = (g_aSavedRank[nCount] % 1000000) / 100000;
		aPosTexU[nCount][3] = (g_aSavedRank[nCount] % 100000) / 10000;
		aPosTexU[nCount][4] = (g_aSavedRank[nCount] % 10000) / 1000;
		aPosTexU[nCount][5] = (g_aSavedRank[nCount] % 1000) / 100;
		aPosTexU[nCount][6] = (g_aSavedRank[nCount] % 100) / 10;
		aPosTexU[nCount][7] = (g_aSavedRank[nCount] % 10);
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//各桁のテクスチャ座標の設定
	for (nCount = 0; nCount < 5; nCount++)
	{
		for (nCount2 = 0; nCount2 < 8; nCount2++)
		{
			pVtx[(nCount * 32) + 28 + (nCount2 * 4)].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount][nCount2] * 0.1f), 0.0f);
			pVtx[(nCount * 32) + 29 + (nCount2 * 4)].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount][nCount2] * 0.1f), 0.0f);
			pVtx[(nCount * 32) + 30 + (nCount2 * 4)].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCount][nCount2] * 0.1f), 1.0f);
			pVtx[(nCount * 32) + 31 + (nCount2 * 4)].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCount][nCount2] * 0.1f), 1.0f);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();
}