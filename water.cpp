//===================================================//
//                                                   //
//            アクションゲーム水ファイル             //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "water.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureWater = NULL;				//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWaterVertical = NULL;		//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureFire = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWater = NULL;			//頂点バッファへのポインタ
WATER g_aWater[MAX_WATER];								//水型の配列を宣言する
int g_nAnimWater;										//水のアニメーションカウンター
int g_nAnimPattern;										//水のアニメーションパターン
int g_nAnimPatternFire;										//水のアニメーションパターン
float g_fMoveWater;										//滝を動かすカウンター

//水の初期化処理
void InitWater(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの情報へのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCount;						//数をカウントする変数を宣言

	//グローバル変数の初期化
	g_nAnimWater = 0;
	g_nAnimPattern = 0;
	g_fMoveWater = 0.0f;
	g_nAnimPatternFire = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Acqua.png",
		&g_pTextureWater);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\AcquaVerticale.png",
		&g_pTextureWaterVertical);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Fire.png",
		&g_pTextureFire);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_WATER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWater,
		NULL);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWater->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		//水型の変数の各パラメータの初期化
		g_aWater[nCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_aWater[nCount].fHeight = 0.0f;						//高さ
		g_aWater[nCount].fWidth = 0.0f;							//幅
		g_aWater[nCount].nType = 0;								//種類
		g_aWater[nCount].nNumSwitch = 0;						//スイッチの番号
		g_aWater[nCount].wState = WATERSTATE_READY;				//水の状態
		g_aWater[nCount].bUse = false;							//使用されているかどうか

		//頂点設定
		pVtx[1].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);

		//rhw設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);

		//テクスチャ座標の設定
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWater->Unlock();
}

//水の終了処理
void UninitWater(void)
{
	//テクスチャポインタの破棄
	if (g_pTextureWater != NULL)
	{			   
		g_pTextureWater->Release();
		g_pTextureWater = NULL;
	}			   
	if (g_pTextureWaterVertical != NULL)
	{			  
		g_pTextureWaterVertical->Release();
		g_pTextureWaterVertical = NULL;
	}
	if (g_pTextureFire != NULL)
	{			  
		g_pTextureFire->Release();
		g_pTextureFire = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWater != NULL)
	{
		g_pVtxBuffWater->Release();
		g_pVtxBuffWater = NULL;
	}
}

//水の更新
void UpdateWater(void)
{
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCount;						//数をカウントする変数を宣言

	MODE mode;						//モード

	mode = GetMode();				//モードの取得

	g_fMoveWater -= 0.01f;			

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWater->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		//アニメーション処理
		if (g_aWater[nCount].bUse == true)
		{
			g_nAnimWater++;

			if (g_aWater[nCount].nType == 0)
			{//普通水の場合

				if (g_nAnimWater % 30 == 29)
				{
					g_nAnimPattern ^= 1;
				}

				if (g_nAnimPattern == 0)
				{

					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.01f - (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) - (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.01f - (g_fMoveWater * 3), 1.0f);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) - (g_fMoveWater * 3), 1.0f);
				}
				else
				{
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.01f + (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) + (g_fMoveWater * 3), 0.1f);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.01f + (g_fMoveWater * 3), 1.0f);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f) + (g_fMoveWater * 3), 1.0f);
				}

				if (mode == MODE_GAME_FIRSTSTAGE_BOSS)
				{
					//頂点カラーの設定
					pVtx[(nCount * 4) + 1].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
					pVtx[(nCount * 4) + 0].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
					pVtx[(nCount * 4) + 3].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
					pVtx[(nCount * 4) + 2].col = D3DXCOLOR(0.1f, 0.4f, 0.1f, 1.0f);
				}

			}
			else if (g_aWater[nCount].nType == 1)
			{//滝の場合

				if (g_nAnimWater % 30 == 29)
				{
					g_nAnimPattern ^= 1;
				}

				if (g_nAnimPattern == 0)
				{
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.01f, g_fMoveWater);
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater);
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.01f, g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
				}
				else
				{
					pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.01f, g_fMoveWater);
					pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater);
					pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.01f, g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
					pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), g_fMoveWater + 1.0f * (g_aWater[nCount].fHeight / 130.0f));
				}

				//水を止める処理
				if (g_aWater[nCount].wState == WATERSTATE_CLOSING)
				{
					g_aWater[nCount].pos.y += 5.0f;
					g_aWater[nCount].fHeight -= 5.0f;
				}
				if (g_aWater[nCount].pos.y >= SCREEN_HEIGHT && g_aWater[nCount].fHeight <= 0.0f)
				{
					g_aWater[nCount].pos.y = 0.0f;
					g_aWater[nCount].fHeight = 0.0f;
					g_aWater[nCount].wState = WATERSTATE_READY;
				}
				//水を開ける処理
				if (g_aWater[nCount].wState == WATERSTATE_OPEN)
				{
					if (g_aWater[nCount].fHeight < 650.0f)
					{
						g_aWater[nCount].fHeight += 5.0f;
					}
				}
			}
			else if (g_aWater[nCount].nType == 2)
			{
				if (g_nAnimWater % 25 == 24)
				{
					g_nAnimPatternFire++;
				}

				if (g_nAnimPatternFire >= 4)
				{
					g_nAnimPatternFire = 0;
				}

				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f + (0.25f * g_nAnimPatternFire));
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.f + (0.25f * g_nAnimPatternFire));
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.25f + (0.25f * g_nAnimPatternFire));
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.25f + (0.25f * g_nAnimPatternFire));
			}

			//頂点設定
			pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
			pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
			pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y + g_aWater[nCount].fHeight, 0.0f);
			pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y + g_aWater[nCount].fHeight, 0.0f);
			
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWater->Unlock();
}

//水の描画処理
void DrawWater(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;							//数をカウントする変数を宣言

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffWater, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		if (g_aWater[nCount].bUse == true)
		{
			if (g_aWater[nCount].nType == 0)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureWater);
			}
			else if (g_aWater[nCount].nType == 1)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureWaterVertical);
			}
			else if (g_aWater[nCount].nType == 2)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureFire);
			}
			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}

//水の設定
void SetWater(D3DXVECTOR3 pos, int type, float width, float height, int nSwitch, WATERSTATE state)
{
	int nCount;						//数をカウントする変数を宣言
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffWater->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		if (g_aWater[nSwitch].bUse == false)
		{
			g_aWater[nSwitch].pos = pos;				//位置の設定
			g_aWater[nSwitch].fHeight = height;			//高さの設定
			g_aWater[nSwitch].fWidth = width;			//幅の設定
			g_aWater[nSwitch].nType = type;				//種類の設定
			g_aWater[nSwitch].nNumSwitch = nSwitch;		//スイッチの番号
			g_aWater[nSwitch].wState = state;			//水の状態
			g_aWater[nSwitch].bUse = true;				//使用されている状態にする

			//頂点座標の設定
			pVtx[(nSwitch * 4) + 0].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x - g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y, 0.0f);
			pVtx[(nSwitch * 4) + 1].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x + g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y, 0.0f);
			pVtx[(nSwitch * 4) + 2].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x - g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y + g_aWater[nSwitch].fHeight, 0.0f);
			pVtx[(nSwitch * 4) + 3].pos = D3DXVECTOR3(g_aWater[nSwitch].pos.x + g_aWater[nSwitch].fWidth, g_aWater[nSwitch].pos.y + g_aWater[nSwitch].fHeight, 0.0f);

			//テクスチャ座標の設定
			if (type == 0)
			{
				pVtx[(nSwitch * 4) + 0].tex = D3DXVECTOR2(0.01f, 0.1f);
				pVtx[(nSwitch * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), 0.1f);
				pVtx[(nSwitch * 4) + 2].tex = D3DXVECTOR2(0.01f, 1.0f);
				pVtx[(nSwitch * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), 1.0f);


				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 1.0f);


			}
			else if (type == 1)
			{
				pVtx[(nSwitch * 4) + 0].tex = D3DXVECTOR2(0.01f, g_fMoveWater);
				pVtx[(nSwitch * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), g_fMoveWater);
				pVtx[(nSwitch * 4) + 2].tex = D3DXVECTOR2(0.01f, g_fMoveWater + 1.0f * (g_aWater[nSwitch].fHeight / 130.0f));
				pVtx[(nSwitch * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nSwitch].fWidth / 50.0f), g_fMoveWater + 1.0f * (g_aWater[nSwitch].fHeight / 130.0f));

				//頂点カラーの設定
				pVtx[(nSwitch * 4) + 0].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
				pVtx[(nSwitch * 4) + 1].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
				pVtx[(nSwitch * 4) + 2].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
				pVtx[(nSwitch * 4) + 3].col = D3DXCOLOR(0.8f, 0.73f, 0.5f, 0.6f);
			}
			if (type == 2)
			{
				//頂点座標の設定
				pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
				pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y - g_aWater[nCount].fHeight, 0.0f);
				pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aWater[nCount].pos.x - g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
				pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aWater[nCount].pos.x + g_aWater[nCount].fWidth, g_aWater[nCount].pos.y, 0.0f);
					   
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f * (g_aWater[nCount].fWidth / 50.0f), 0.5f);


				//頂点カラーの設定
				pVtx[(nCount * 4) + 0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);
				pVtx[(nCount * 4) + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);
				pVtx[(nCount * 4) + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);
				pVtx[(nCount * 4) + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.9f);


			}

			break;
		}

	}

	//頂点バッファをアンロックする
	g_pVtxBuffWater->Unlock();
}

//水の当たり判定
int WaterInteraction(D3DXVECTOR3*pPos,			//現在の位置
	D3DXVECTOR3*pMove,
	float fWidth,								//幅
	float fHeight)								//高さ)
{
	int nCount;						//数をカウントする変数を宣言
	int nInWater = 0;

	for (nCount = 0; nCount < MAX_WATER; nCount++)
	{
		if (g_aWater[nCount].bUse == true)
		{//水の中にいる場合
			if (pPos->x + (fWidth * 0.5f) >= g_aWater[nCount].pos.x - g_aWater[nCount].fWidth &&
				pPos->x - (fWidth * 0.5f) <= g_aWater[nCount].pos.x + g_aWater[nCount].fWidth &&
				pPos->y >= g_aWater[nCount].pos.y&&
				pPos->y - fHeight <= g_aWater[nCount].pos.y + g_aWater[nCount].fHeight)
			{
				nInWater = 1;
			}
		}
	}

	return nInWater;
}

//水の情報を取得
WATER*GetWater(void)
{
	return &g_aWater[0];
}