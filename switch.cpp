//===================================================//
//                                                   //
//    　 　  アクションゲームスイッチ 関数       　  //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "switch.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureSwitch = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSwitch = NULL;	//頂点バッファへのポインタ
SWITCH g_aSwitch[MAX_SWITCH];						//プラットフォーム型の配列を宣言する
int g_nCountDelaySwitch[MAX_SWITCH];				
int g_nActive;

//スイッチの初期化処理
void InitSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの情報へのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCount;						//数をカウントする変数を宣言
	g_nActive = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\LevaSprite.png",
		&g_apTextureSwitch);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SWITCH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSwitch,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_SWITCH; nCount++)
	{
		//スイッチ型の変数の各パラメータの初期化
		g_aSwitch[nCount].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSwitch[nCount].nCountSwitch = 0;
		g_aSwitch[nCount].bActive = false;
		g_aSwitch[nCount].bUse = false;

		g_nCountDelaySwitch[nCount] = 0;
		
		//頂点座標の設定
		pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		//テクスチャ頂点の設定
		pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.5f, 1.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSwitch->Unlock();
}

//スイッチの終了処理
void UninitSwitch(void)
{
	//テクスチャポインタの破棄
	if (g_apTextureSwitch != NULL)
	{			   
		g_apTextureSwitch->Release();
		g_apTextureSwitch = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffSwitch != NULL)
	{			  
		g_pVtxBuffSwitch->Release();
		g_pVtxBuffSwitch = NULL;
	}
}

//スイッチの更新処理
void UpdateSwitch(void)
{
	Player*pPlayer;					//プレイヤーの情報へのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	WATER*pWater;					//水の情報へのポインタ
	MODE mode;

	mode = GetMode();
	pWater = GetWater();			//水の情報を取得
	pPlayer = GetPlayer();			//プレイヤーの情報の取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_SWITCH; nCount++, pWater++)
	{
		if (g_aSwitch[nCount].bUse == true)
		{
			if (mode == MODE_GAME_FIRSTSTAGE_BOSS && g_nActive == 0 || mode == MODE_GAME_SECONDSTAGE_BOSS && g_nActive == 0)
			{
				g_aSwitch[nCount].bActive = true;
			}

			if (g_nCountDelaySwitch[nCount] > 0)
			{
				g_nCountDelaySwitch[nCount]--;
			}

			if (g_aSwitch[nCount].Pos.x >= pPlayer->pos.x - PLAYER_WIDTH / 2 &&
				g_aSwitch[nCount].Pos.x <= pPlayer->pos.x + PLAYER_WIDTH / 2 &&
				g_aSwitch[nCount].Pos.y <= pPlayer->pos.y &&
				g_aSwitch[nCount].Pos.y >= pPlayer->pos.y - PLAYER_HEIGHT &&
				g_nCountDelaySwitch[nCount] <= 0)
			{

				if (GetKeyboardTrigger(DIK_RETURN) == true)
				{
					if (g_aSwitch[nCount].bActive == true)
					{
						g_aSwitch[nCount].bActive = false;
						if (mode == MODE_GAME_FIRSTSTAGE_1 || mode == MODE_GAME_FIRSTSTAGE_2)
						{
							pWater->wState = WATERSTATE_CLOSING;
						}
						else if (mode == MODE_GAME_FIRSTSTAGE_BOSS || mode == MODE_GAME_BONUSSTAGE || mode == MODE_GAME_SECONDSTAGE_BOSS)
						{
							g_nActive++;
						}
					}
					else if (g_aSwitch[nCount].bActive == false)
					{
						g_aSwitch[nCount].bActive = true;
						if (mode == MODE_GAME_FIRSTSTAGE_1 || mode == MODE_GAME_FIRSTSTAGE_2)
						{
							pWater->wState = WATERSTATE_OPEN;
						}
						else if (mode == MODE_GAME_FIRSTSTAGE_BOSS || mode == MODE_GAME_BONUSSTAGE || mode == MODE_GAME_SECONDSTAGE_BOSS)
						{
							g_nActive--;
						}
					}
					g_nCountDelaySwitch[nCount] = 180;

				}

			}
			
			//テクスチャ座標の更新
			if (g_aSwitch[nCount].bActive == true)
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.5f, 1.0f);
			}
			else
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			//===================================================================
			if (mode == MODE_GAME_BONUSSTAGE)
			{
				if (g_aSwitch[nCount].Pos.y < pPlayer->pos.y + 55.0f && g_aSwitch[nCount].Pos.y > pPlayer->pos.y - 130.0f &&
					g_aSwitch[nCount].Pos.x < pPlayer->pos.x + 120.0f && g_aSwitch[nCount].Pos.x > pPlayer->pos.x - 120.0f)
				{
					pVtx[(nCount * 4) + 0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[(nCount * 4) + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[(nCount * 4) + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[(nCount * 4) + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				else
				{
					pVtx[(nCount * 4) + 0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					pVtx[(nCount * 4) + 1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					pVtx[(nCount * 4) + 2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
					pVtx[(nCount * 4) + 3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			//===================================================================
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSwitch->Unlock();
}

//スイッチの描画処理
void DrawSwitch(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSwitch, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_SWITCH; nCount++)
	{
		if (g_aSwitch[nCount].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureSwitch);


			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}

//スイッチの設定処理
void SetSwitch(D3DXVECTOR3 pos, int nNumberSwitch, bool Active)
{
	int nCount;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSwitch->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_SWITCH; nCount++)
	{
		if (g_aSwitch[nCount].bUse == false)
		{
			//スイッチの各パラメータの設定
			g_aSwitch[nCount].Pos = pos;							//スイッチの位置
			g_aSwitch[nCount].nCountSwitch = nNumberSwitch;			//スイッチの番号
			g_aSwitch[nCount].bActive = Active;						//スイッチの状態
			g_aSwitch[nCount].bUse = true;							//スイッチが使用されている状態にする

			//頂点座標の設定
			pVtx[(nCount * 4) + 0].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x - 15.0f, g_aSwitch[nCount].Pos.y - 15.0f, 0.0f);
			pVtx[(nCount * 4) + 1].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x + 15.0f, g_aSwitch[nCount].Pos.y - 15.0f, 0.0f);
			pVtx[(nCount * 4) + 2].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x - 15.0f, g_aSwitch[nCount].Pos.y + 15.0f, 0.0f);
			pVtx[(nCount * 4) + 3].pos = D3DXVECTOR3(g_aSwitch[nCount].Pos.x + 15.0f, g_aSwitch[nCount].Pos.y + 15.0f, 0.0f);

			//テクスチャ座標の設定
			if (Active == true)
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(0.5f, 1.0f);
			}
			else
			{
				pVtx[(nCount * 4) + 0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCount * 4) + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[(nCount * 4) + 2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[(nCount * 4) + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			break;
		}
		
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSwitch->Unlock();
}

int*GetActiveSwitch(void)
{
	return &g_nActive;
}