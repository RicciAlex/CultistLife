//インクルードファイル
#include "minion.h"

//グローバル変数を宣言
LPDIRECT3DTEXTURE9 g_apTextureMinion = NULL;					//敵のテクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureTheChariot = NULL;
LPDIRECT3DTEXTURE9 g_apTextureTheDeath = NULL;
LPDIRECT3DTEXTURE9 g_apTextureTheHangedMan = NULL;
LPDIRECT3DTEXTURE9 g_apTextureTheDevil = NULL;
LPDIRECT3DTEXTURE9 g_apTextureTheSun = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMinion = NULL;				//頂点バッファへのポインタ
Minion g_aMinion[MAX_MINION];									//敵型の配列を宣言する

//敵の初期化処理
void InitMinion(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの情報へのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCntEnemy;					//数をカウントする変数を宣言する

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Minion1_Sprite.png",
		&g_apTextureMinion);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\VII TheChariot.png",
		&g_apTextureTheChariot);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\XIII DeathSpriteSheet.png",
		&g_apTextureTheDeath);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\XII TheHangedMan.png",
		&g_apTextureTheHangedMan);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\XV TheDevil.png",
		&g_apTextureTheDevil);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\XIX TheSun.png",
		&g_apTextureTheSun);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MINION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMinion,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMinion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_MINION; nCntEnemy++)
	{
		g_aMinion[MAX_MINION].pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);		//現在の位置
		g_aMinion[MAX_MINION].LastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
		g_aMinion[MAX_MINION].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
		g_aMinion[MAX_MINION].state = MINIONSTATE_NORMAL;					//状態
		g_aMinion[MAX_MINION].fWidth = 20.0f;								//幅
		g_aMinion[MAX_MINION].fHeight = 40.0f;								//高さ
		g_aMinion[MAX_MINION].nType = 0;									//種類
		g_aMinion[MAX_MINION].nCountAnim = 0;								//アニメーションカウンタ
		g_aMinion[MAX_MINION].nCounterState = 0;							//ステータスカウンタ
		g_aMinion[MAX_MINION].nPatternAnim = 0;								//アニメーションパターン番号
		g_aMinion[MAX_MINION].bUse = false;									//使用されているかどうか

		//頂点設定
		pVtx[1].pos = D3DXVECTOR3(101.0f, 101.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(103.0f, 101.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(101.0f, 103.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(103.0f, 103.0f, 0.0f);

		//rhw設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMinion->Unlock();
}

//敵の終了処理
void UninitMinion(void)
{
	//テクスチャへのポインタの破棄
	if (g_apTextureMinion != NULL)
	{
		g_apTextureMinion->Release();
		g_apTextureMinion = NULL;
	}
	if (g_apTextureTheChariot != NULL)
	{
		g_apTextureTheChariot->Release();
		g_apTextureTheChariot = NULL;
	}
	if (g_apTextureTheDeath != NULL)
	{
		g_apTextureTheDeath->Release();
		g_apTextureTheDeath = NULL;
	}
	if (g_apTextureTheHangedMan != NULL)
	{				  
		g_apTextureTheHangedMan->Release();
		g_apTextureTheHangedMan = NULL;
	}
	if (g_apTextureTheDevil != NULL)
	{				  
		g_apTextureTheDevil->Release();
		g_apTextureTheDevil = NULL;
	}
	if (g_apTextureTheSun != NULL)
	{				  
		g_apTextureTheSun->Release();
		g_apTextureTheSun = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMinion != NULL)
	{
		g_pVtxBuffMinion->Release();
		g_pVtxBuffMinion = NULL;
	}
}

//敵の更新
void UpdateMinion(void)
{
	MODE mode;

	mode = GetMode();

	if (mode == MODE_GAME_FIRSTSTAGE_BOSS)
	{
		UpdateBombBat();
	}
	else if (mode == MODE_GAME_SECONDSTAGE_BOSS)
	{
		UpdateTarotSummon();
	}
}

//敵の描画処理
void DrawMinion(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスの情報へのポインタ
	int nCntMinion;				//数をカウントする変数を宣言する

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMinion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntMinion = 0; nCntMinion < MAX_MINION; nCntMinion++)
	{
		if (g_aMinion[nCntMinion].bUse == true)
		{
			//テクスチャの設定

			switch (g_aMinion[nCntMinion].nType)
			{
			case 0:
				pDevice->SetTexture(0, g_apTextureMinion);
				break;

			case 1:
				pDevice->SetTexture(0, g_apTextureTheChariot);
				break;

			case 2:
				pDevice->SetTexture(0, g_apTextureTheHangedMan);
				break;

			case 3:
				pDevice->SetTexture(0, g_apTextureTheDeath);
				break;

			case 4:
				pDevice->SetTexture(0, g_apTextureTheDevil);
				break;

			case 5:
				pDevice->SetTexture(0, g_apTextureTheSun);
				break;
			}
			
			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMinion * 4, 2);
		}
	}
}

//敵の設定
void SetMinion(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntMinion;		//数をカウントする変数を宣言する

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMinion->Lock(0, 0, (void**)&pVtx, 0);

	//敵の各ステータスを設定する
	for (nCntMinion = 0; nCntMinion < MAX_MINION; nCntMinion++)
	{
		if (g_aMinion[nCntMinion].bUse == false)
		{
			//敵の位置
			g_aMinion[nCntMinion].pos = pos;
			//敵の前回の位置の設定
			g_aMinion[nCntMinion].LastPos = pos;
			//敵の移動量
			g_aMinion[nCntMinion].move = move;
			//敵の状態
			g_aMinion[nCntMinion].state = MINIONSTATE_NORMAL;
			//敵の種類
			g_aMinion[nCntMinion].nType = nType;
			//使用されているにする
			g_aMinion[nCntMinion].bUse = true;

			//頂点カラーの設定
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			switch (g_aMinion[nCntMinion].nType)
			{
			case 0:

				//頂点の設定
				pVtx[1].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y - 40.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y - 40.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y, pos.z);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);

				break;

			case 1:

				//頂点の設定
				pVtx[1].pos = D3DXVECTOR3(pos.x + 80.0f, pos.y - 120.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 80.0f, pos.y - 120.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 80.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 80.0f, pos.y, pos.z);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

				break;

			case 2:
				//頂点の設定
				pVtx[1].pos = D3DXVECTOR3(pos.x + 60.0f, pos.y - 1000.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 60.0f, pos.y - 1000.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 60.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 60.0f, pos.y, pos.z);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.1f);
				pVtx[1].tex = D3DXVECTOR2(0.2f, 0.1f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.2f, 1.0f);

				break;

			case 3:

				//頂点の設定
				pVtx[1].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y - 100.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y - 100.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y, pos.z);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.33f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.33f);

				break;

			case 4:

				g_aMinion[nCntMinion].state = MINIONSTATE_APPEAR;

				//頂点の設定
				pVtx[1].pos = D3DXVECTOR3(pos.x + 80.0f, pos.y - 200.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 80.0f, pos.y - 200.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 80.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 80.0f, pos.y, pos.z);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

				break;

			case 5:

				g_aMinion[nCntMinion].state = MINIONSTATE_APPEAR;

				//頂点の設定
				pVtx[1].pos = D3DXVECTOR3(pos.x + 100.0f, pos.y - 200.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 100.0f, pos.y - 200.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 100.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 100.0f, pos.y, pos.z);

				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125f);
				pVtx[3].tex = D3DXVECTOR2(0.125f, 0.125f);

				break;
			}

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMinion->Unlock();
}

void UpdateBombBat(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	Boss*pBoss;			//ボスの情報へのポインタ
	Player*pPlayer;		//プレイヤーの情報へのポインタ
	int nNumberMinion = 0;	//敵の数をカウントする変数を宣言

	pBoss = GetBoss();		//敵の情報を取得
	pPlayer = GetPlayer();	//プレイヤーの情報を取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMinion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMinion = 0; nCntMinion < MAX_MINION; nCntMinion++)
	{
		if (pBoss->bUse == true)
		{
			//ボスの当たり判定
			if (g_aMinion[nCntMinion].bUse == true)
			{
				if (g_aMinion[nCntMinion].pos.y - 40.0f >= pBoss->pos.y &&
					g_aMinion[nCntMinion].pos.x > pBoss->pos.x - 45.0f &&
					g_aMinion[nCntMinion].pos.x < pBoss->pos.x + 45.0f)
				{//ボスに当たったら
					g_aMinion[nCntMinion].bUse = false;			//使用されていない状態にする
					pBoss->bDamage = true;						//ボスにダメージを与える
				}

				//位置の更新
				g_aMinion[nCntMinion].pos += g_aMinion[nCntMinion].move;

				//アニメーション処理
				g_aMinion[nCntMinion].nCountAnim++;

				if (g_aMinion[nCntMinion].nCountAnim % 7 == 6)
				{
					g_aMinion[nCntMinion].nPatternAnim++;

					if (g_aMinion[nCntMinion].nPatternAnim >= 2)
					{
						g_aMinion[nCntMinion].nPatternAnim = 0;
					}
				}

				//画面を出た場合
				if (g_aMinion[nCntMinion].pos.x >= SCREEN_WIDTH || g_aMinion[nCntMinion].pos.x <= 0)
				{
					g_aMinion[nCntMinion].bUse = false;
				}

				//向きの更新
				if (g_aMinion[nCntMinion].move.x > 0)
				{
					g_aMinion[nCntMinion].nDirection = 1;
				}
				else
				{
					g_aMinion[nCntMinion].nDirection = -1;
				}

				//頂点の更新
				pVtx[(nCntMinion * 4) + 1].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 20.0f, g_aMinion[nCntMinion].pos.y - 40.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 0].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 20.0f, g_aMinion[nCntMinion].pos.y - 40.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 3].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 20.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 2].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 20.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);

				//テクスチャ座標の更新
				if (g_aMinion[nCntMinion].nDirection == 1)
				{
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.5f);
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.5f);
				}
				else
				{

					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.5f);
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.5f);

				}

				//プレイヤーの当たり判定
				if (g_aMinion[nCntMinion].state != MINIONSTATE_EXPLODE)
				{
					if (pPlayer->pos.x + PLAYER_WIDTH > g_aMinion[nCntMinion].pos.x - g_aMinion[nCntMinion].fWidth &&
						pPlayer->pos.x - PLAYER_WIDTH < g_aMinion[nCntMinion].pos.x - g_aMinion[nCntMinion].fWidth &&
						pPlayer->pos.y - PLAYER_HEIGHT < g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight &&
						pPlayer->pos.y > g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight ||
						pPlayer->pos.x - PLAYER_WIDTH < g_aMinion[nCntMinion].pos.x + g_aMinion[nCntMinion].fWidth &&
						pPlayer->pos.x + PLAYER_WIDTH > g_aMinion[nCntMinion].pos.x + g_aMinion[nCntMinion].fWidth &&
						pPlayer->pos.y - PLAYER_HEIGHT < g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight &&
						pPlayer->pos.y > g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight)
					{
						g_aMinion[nCntMinion].state = MINIONSTATE_EXPLODE;			//爆発する状態にする
						g_aMinion[nCntMinion].nCounterState = 180;					//状態カウンターを設定する
					}
				}

				if (g_aMinion[nCntMinion].state == MINIONSTATE_EXPLODE)
				{//爆発する状態の場合
					g_aMinion[nCntMinion].nCounterState--;

					//頂点カラーの更新
					if (g_aMinion[nCntMinion].nPatternAnim == 0)
					{
						pVtx[(nCntMinion * 4) + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[(nCntMinion * 4) + 0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[(nCntMinion * 4) + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[(nCntMinion * 4) + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						pVtx[(nCntMinion * 4) + 1].col = D3DXCOLOR(0.7f, 0.2f, 0.2f, 1.0f);
						pVtx[(nCntMinion * 4) + 0].col = D3DXCOLOR(0.7f, 0.2f, 0.2f, 1.0f);
						pVtx[(nCntMinion * 4) + 3].col = D3DXCOLOR(0.7f, 0.2f, 0.2f, 1.0f);
						pVtx[(nCntMinion * 4) + 2].col = D3DXCOLOR(0.7f, 0.2f, 0.2f, 1.0f);
					}

					if (g_aMinion[nCntMinion].nCounterState <= 0)
					{
						SetExplosion(g_aMinion[nCntMinion].pos, D3DXCOLOR(1.0f, 0.4f, 0.05f, 1.0f), 2);			//爆発の設定
						g_aMinion[nCntMinion].nCounterState = 0;
						g_aMinion[nCntMinion].bUse = false;														//使用されていない状態にする
					}
				}
			}
			//else
			//{//使用していない敵を数える
			//	nNumberMinion++;
			//	if (nNumberMinion == MAX_MINION)
			//	{//使用している敵がいない場合

			//		//敵の設定
			//		SetMinion(D3DXVECTOR3(0.0f, 370.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 0);
			//		SetMinion(D3DXVECTOR3(1280.0f, 370.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);
			//	}
			//}

		}

	}

	//頂点バッファをアンロックする
	g_pVtxBuffMinion->Unlock();
}

//まだ途中です
void UpdateTarotSummon(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	Boss*pBoss;
	Player*pPlayer;
	int*pSwitch;
	int nNumberMinion = 0;

	pBoss = GetBoss();
	pPlayer = GetPlayer();
	pSwitch = GetActiveSwitch();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMinion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMinion = 0; nCntMinion < MAX_MINION; nCntMinion++)
	{
		if (g_aMinion[nCntMinion].bUse == true)
		{
			g_aMinion[nCntMinion].pos += g_aMinion[nCntMinion].move;

			switch (g_aMinion[nCntMinion].nType)
			{
			case 1:																					//VII戦車

				switch (g_aMinion[nCntMinion].state)
				{
				case MINIONSTATE_NORMAL:

					if (pPlayer->MoveState == MOVESTATE_LANDED)
					{

						g_aMinion[nCntMinion].pos.y = pPlayer->pos.y + 10.0f;

						if (pPlayer->pos.x >= SCREEN_WIDTH * 0.5f)
						{
							g_aMinion[nCntMinion].pos.x = -90.0f;
							g_aMinion[nCntMinion].nDirection = 1;
							g_aMinion[nCntMinion].move.x = 10.0f;
						}
						else
						{
							g_aMinion[nCntMinion].pos.x = SCREEN_WIDTH + 90.0f;
							g_aMinion[nCntMinion].nDirection = -1;
							g_aMinion[nCntMinion].move.x = -10.0f;
						}

						g_aMinion[nCntMinion].state = MINIONSTATE_ATTACK;

					}
					break;

				case MINIONSTATE_ATTACK:

					g_aMinion[nCntMinion].nCountAnim++;

					if (g_aMinion[nCntMinion].nCountAnim % 3 == 2)
					{
						g_aMinion[nCntMinion].nPatternAnim ^= 1;
					}

					if (g_aMinion[nCntMinion].pos.x >= SCREEN_WIDTH + 90.0f && g_aMinion[nCntMinion].move.x > 0 ||
						g_aMinion[nCntMinion].pos.x <= -90.0f && g_aMinion[nCntMinion].move.x < 0)
					{
						g_aMinion[nCntMinion].state = MINIONSTATE_NORMAL;
					}

					if (pPlayer->state != PLAYERSTATE_DAMAGE && pPlayer->state != PLAYERSTATE_DEATH)
					{
						if (pPlayer->pos.y > g_aMinion[nCntMinion].pos.y - 90.0f && pPlayer->pos.y - PLAYER_HEIGHT < g_aMinion[nCntMinion].pos.y - 90.0f &&
							pPlayer->pos.x > g_aMinion[nCntMinion].pos.x - 80.0f && pPlayer->pos.x < g_aMinion[nCntMinion].pos.x + 80.0f ||
							pPlayer->pos.y <= g_aMinion[nCntMinion].pos.y && pPlayer->pos.y - PLAYER_HEIGHT > g_aMinion[nCntMinion].pos.y - 90.0f &&
							pPlayer->pos.x > g_aMinion[nCntMinion].pos.x - 80.0f && pPlayer->pos.x < g_aMinion[nCntMinion].pos.x + 80.0f ||
							pPlayer->pos.y > g_aMinion[nCntMinion].pos.y && pPlayer->pos.y - PLAYER_HEIGHT < g_aMinion[nCntMinion].pos.y &&
							pPlayer->pos.x > g_aMinion[nCntMinion].pos.x - 80.0f && pPlayer->pos.x < g_aMinion[nCntMinion].pos.x + 80.0f)
						{

							pPlayer->state = PLAYERSTATE_DAMAGE;
							pPlayer->nCounterState = 180;
							AddScore(-250);
							PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);
							SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS250);
						}
					}
				

					break;
				}
				//頂点の設定
				pVtx[(nCntMinion * 4) + 1].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 80.0f, g_aMinion[nCntMinion].pos.y - 120.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 0].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 80.0f, g_aMinion[nCntMinion].pos.y - 120.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 3].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 80.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 2].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 80.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);

				if (g_aMinion[nCntMinion].nDirection > 0)
				{

					//テクスチャ座標の設定
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 1.0f);
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 1.0f);
					
				}
				else if(g_aMinion[nCntMinion].nDirection < 0)
				{
					//テクスチャ座標の設定
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 0.0f);
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.0f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 1.0f);
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aMinion[nCntMinion].nPatternAnim), 1.0f);
				}
				//=======================================================================================================================================================
				if (pBoss->nLife < 4)
				{
					g_aMinion[nCntMinion].bUse = false;
				}

				break;

				//=======================================================================================================================================================
				//=======================================================================================================================================================

			case 2:																					//XXII 吊された男

				if (pPlayer->pos.x >= g_aMinion[nCntMinion].pos.x)
				{
					g_aMinion[nCntMinion].nDirection = 1;
				}
				else if (pPlayer->pos.x < g_aMinion[nCntMinion].pos.x)
				{
					g_aMinion[nCntMinion].nDirection = -1;
				}

				switch (g_aMinion[nCntMinion].state)
				{
				case MINIONSTATE_NORMAL:
					
					if (g_aMinion[nCntMinion].pos.x > pPlayer->pos.x)
					{
						g_aMinion[nCntMinion].move.x = -5.0f;
					}
					else if (g_aMinion[nCntMinion].pos.x < pPlayer->pos.x)
					{
						g_aMinion[nCntMinion].move.x = 5.0f;
					}

					if (g_aMinion[nCntMinion].pos.x >= pPlayer->pos.x - 25.0f && g_aMinion[nCntMinion].pos.x <= pPlayer->pos.x + 25.0f)
					{
						g_aMinion[nCntMinion].move.x = 0.0f;
						g_aMinion[nCntMinion].state = MINIONSTATE_ATTACK;
						g_aMinion[nCntMinion].nCounterState = 60.0f;
					}
					break;

				case MINIONSTATE_ATTACK:

					if (g_aMinion[nCntMinion].nCounterState > 0)
					{
						g_aMinion[nCntMinion].nCounterState--;
					}

					if (g_aMinion[nCntMinion].nCounterState <= 0)
					{
						g_aMinion[nCntMinion].nCounterState = 0;

						if (g_aMinion[nCntMinion].pos.y < pPlayer->pos.y - (PLAYER_HEIGHT * 0.5f))
						{
							g_aMinion[nCntMinion].move.y = 8.0f;
						}
						else
						{
							g_aMinion[nCntMinion].move.y = 0.0f;

							g_aMinion[nCntMinion].nCountAnim++;

							if (g_aMinion[nCntMinion].nPatternAnim == 3 && g_aMinion[nCntMinion].nCountAnim == 9)
							{
								PlaySound(SOUND_LABEL_SE_NORMALBULLET);
								SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 75.0f, 0.0f),
									D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
								SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 75.0f, 0.0f),
									D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
								SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 75.0f, 0.0f),
									D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, -2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1);
							}
							else if (g_aMinion[nCntMinion].nPatternAnim == 3 && g_aMinion[nCntMinion].nCountAnim == 19)
							{
								PlaySound(SOUND_LABEL_SE_NORMALBULLET);
								SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 75.0f, 0.0f),
									D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.05, 0.0f), 1);
								SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 75.0f, 0.0f),
									D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.01f, 0.0f), 1);
								SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 75.0f, 0.0f),
									D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, -2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.01f, 0.0f), 1);
							}


							if (g_aMinion[nCntMinion].nCountAnim % 20 == 19)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
								g_aMinion[nCntMinion].nCountAnim = 0;

								if (g_aMinion[nCntMinion].nPatternAnim == 5)
								{
									g_aMinion[nCntMinion].state = MINIONSTATE_RETURN;
									g_aMinion[nCntMinion].nPatternAnim = 0;
									g_aMinion[nCntMinion].nCountAnim = 0;
								}
							}
						}
					}

					if (pPlayer->pos.y - PLAYER_HEIGHT < g_aMinion[nCntMinion].pos.y && pPlayer->pos.x > g_aMinion[nCntMinion].pos.x - (PLAYER_WIDTH * 0.5f) - 40.0f &&
						pPlayer->pos.x < g_aMinion[nCntMinion].pos.x + (PLAYER_WIDTH * 0.5f) + 40.0f && pPlayer->state != PLAYERSTATE_DAMAGE && pPlayer->state != PLAYERSTATE_DEATH)
					{
						pPlayer->state = PLAYERSTATE_DAMAGE;
						pPlayer->nCounterState = 180;
						AddScore(-250);
						PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);
						SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS250);
					}

					break;

				case MINIONSTATE_RETURN:

					g_aMinion[nCntMinion].nCountAnim++;

					if (g_aMinion[nCntMinion].nCountAnim % 5 == 4)
					{
						g_aMinion[nCntMinion].nPatternAnim++;
						g_aMinion[nCntMinion].nCountAnim = 0;

						if (g_aMinion[nCntMinion].nPatternAnim == 1)
						{
							g_aMinion[nCntMinion].nPatternAnim = 0;
						}
					}

					g_aMinion[nCntMinion].move = D3DXVECTOR3(0.0f, -5.0f, 0.0f);
					if (g_aMinion[nCntMinion].pos.y <= -10.0f)
					{
						g_aMinion[nCntMinion].pos.y = -10.0f;
						g_aMinion[nCntMinion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						g_aMinion[nCntMinion].state = MINIONSTATE_NORMAL;
					}

					break;
				}

				//頂点の更新
				pVtx[(nCntMinion * 4) + 1].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 60.0f, g_aMinion[nCntMinion].pos.y - 1000.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 0].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 60.0f, g_aMinion[nCntMinion].pos.y - 1000.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 3].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 60.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 2].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 60.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);

				if (g_aMinion[nCntMinion].nDirection > 0)
				{
					//テクスチャ座標の設定
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 0.1f);
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.2f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 0.1f);
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 1.0f);
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.2f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 1.0f);
				}
				else if (g_aMinion[nCntMinion].nDirection < 0)
				{
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 0.1f);
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.2f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 0.1f);
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 1.0f);
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.2f + (g_aMinion[nCntMinion].nPatternAnim * 0.2f), 1.0f);
				}
				//=======================================================================================================================================================
				if (pBoss->nLife < 3)
				{
					g_aMinion[nCntMinion].bUse = false;
				}

				break;

				//=======================================================================================================================================================
				//=======================================================================================================================================================
			case 3:																							//XIII 死神

				if (g_aMinion[nCntMinion].pos.x <= SCREEN_WIDTH * 0.5f)
				{
					g_aMinion[nCntMinion].nDirection = 1;
				}
				else
				{
					g_aMinion[nCntMinion].nDirection = -1;
				}

				switch (g_aMinion[nCntMinion].state)
				{
				case MINIONSTATE_NORMAL:

					if (g_aMinion[nCntMinion].nPatternAnim != 0)
					{
						g_aMinion[nCntMinion].nPatternAnim = 0;
					}

					g_aMinion[nCntMinion].pos = D3DXVECTOR3(-100.0f, 300.0f, 0.0f);

					if (pPlayer->pos.x - PLAYER_WIDTH <= 40.0f)
					{
						g_aMinion[nCntMinion].pos = D3DXVECTOR3(0.0f - g_aMinion[nCntMinion].fWidth, pPlayer->pos.y + 2.5f, 0.0f);
						g_aMinion[nCntMinion].state = MINIONSTATE_ATTACK;
						g_aMinion[nCntMinion].nCountAnim = 0;
					}
					else if (pPlayer->pos.x + PLAYER_WIDTH >= SCREEN_WIDTH - 40.0f)
					{
						g_aMinion[nCntMinion].pos = D3DXVECTOR3(SCREEN_WIDTH + g_aMinion[nCntMinion].fWidth, pPlayer->pos.y + 2.5f, 0.0f);
						g_aMinion[nCntMinion].state = MINIONSTATE_ATTACK;
						g_aMinion[nCntMinion].nCountAnim = 0;
					}
					break;

				case MINIONSTATE_ATTACK:

					if (g_aMinion[nCntMinion].pos.x < 20.0f && g_aMinion[nCntMinion].nDirection > 0)
					{
						g_aMinion[nCntMinion].move.x = 2.5f;
					}
					else if (g_aMinion[nCntMinion].pos.x > SCREEN_WIDTH - 20.0f && g_aMinion[nCntMinion].nDirection < 0)
					{
						g_aMinion[nCntMinion].move.x = -2.5f;
					}
					
					if (g_aMinion[nCntMinion].pos.x > 20.0f && g_aMinion[nCntMinion].nDirection > 0 || 
						g_aMinion[nCntMinion].pos.x < SCREEN_WIDTH - 20.0f&& g_aMinion[nCntMinion].nDirection < 0)
					{
						g_aMinion[nCntMinion].move.x = 0.0f;
					}
					
						g_aMinion[nCntMinion].nCountAnim++;

						switch (g_aMinion[nCntMinion].nPatternAnim)
						{
						case 0:
							if (g_aMinion[nCntMinion].nCountAnim >= 60)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
								g_aMinion[nCntMinion].nCountAnim = 0;
								SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(2.5f * g_aMinion[nCntMinion].nDirection, 0.0f, 0.0f), D3DXVECTOR3(-0.05f * g_aMinion[nCntMinion].nDirection, 0.0f, 0.0f), 2);
								PlaySound(SOUND_LABEL_SE_DEATHSLASH);
							}
							break;

						case 1:
							if (g_aMinion[nCntMinion].nCountAnim >= 60)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
								g_aMinion[nCntMinion].nCountAnim = 0;
							}
							break;
						case 2:
							if (g_aMinion[nCntMinion].nCountAnim >= 10)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
								g_aMinion[nCntMinion].nCountAnim = 0;
							}
							break;
						case 3:
							if (g_aMinion[nCntMinion].nCountAnim >= 10)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
								g_aMinion[nCntMinion].nCountAnim = 0;
							}
							break;
						case 4:
							if (g_aMinion[nCntMinion].nCountAnim >= 10)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
								g_aMinion[nCntMinion].nCountAnim = 0;
							}
							break;
						case 5:
							if (g_aMinion[nCntMinion].nCountAnim >= 10)
							{
								g_aMinion[nCntMinion].nCountAnim = 0;
								g_aMinion[nCntMinion].state = MINIONSTATE_NORMAL;
							}
							break;
						}
					
					break;
				}

				if (g_aMinion[nCntMinion].pos.x < SCREEN_WIDTH * 0.5f)
				{
					//テクスチャ座標の設定
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.0f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.0f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.5f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.0f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.0f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.33f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.5f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.33f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
				}
				else
				{
					//テクスチャ座標の設定
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.0f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.0f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.5f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.0f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.0f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.33f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.5f + ((g_aMinion[nCntMinion].nPatternAnim % 2) * 0.5), 0.33f + (0.33 * (g_aMinion[nCntMinion].nPatternAnim / 2)));
				}
				
				//頂点の更新
				pVtx[(nCntMinion * 4) + 1].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 75.0f, g_aMinion[nCntMinion].pos.y - 150.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 0].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 75.0f, g_aMinion[nCntMinion].pos.y - 150.0f, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 3].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 75.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);
				pVtx[(nCntMinion * 4) + 2].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 75.0f, g_aMinion[nCntMinion].pos.y, g_aMinion[nCntMinion].pos.z);

				break;

				//=======================================================================================================================================================
				//=======================================================================================================================================================

			case 4:																												//XV 悪魔

				switch (g_aMinion[nCntMinion].state)
				{
				case MINIONSTATE_APPEAR:

					if (g_aMinion[nCntMinion].pos.y <= 610.0f)
					{
						g_aMinion[nCntMinion].pos.y = 610.0f;
						g_aMinion[nCntMinion].move.y = 0.1f;
						g_aMinion[nCntMinion].state = MINIONSTATE_NORMAL;
						g_aMinion[nCntMinion].nCounterState = 120;
						*pSwitch = 0;
					}
					break;

				case MINIONSTATE_NORMAL:

					g_aMinion[nCntMinion].nCounterState--;

					if (g_aMinion[nCntMinion].pos.y <= 610.0f)
					{
						g_aMinion[nCntMinion].pos.y = 610.0f;
						g_aMinion[nCntMinion].move.y *= -1;
					}
					else if(g_aMinion[nCntMinion].pos.y >= 690.0f)
					{
						g_aMinion[nCntMinion].pos.y = 690.0f;
						g_aMinion[nCntMinion].move.y *= -1;
					}

					if (g_aMinion[nCntMinion].nCounterState <= 0)
					{
						g_aMinion[nCntMinion].state = MINIONSTATE_ATTACK;
					}

					break;

				case MINIONSTATE_ATTACK:

					g_aMinion[nCntMinion].nCountAnim++;

					if (g_aMinion[nCntMinion].nCountAnim % 10 == 9)
					{
						g_aMinion[nCntMinion].nPatternAnim++;

						if (g_aMinion[nCntMinion].nPatternAnim == 2)
						{
							PlaySound(SOUND_LABEL_SE_FIRE);
							SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 20.0f, g_aMinion[nCntMinion].pos.y - 20.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR3(0.25f, 0.0f, 0.0f), 3);
							SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 20.0f, g_aMinion[nCntMinion].pos.y - 20.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR3(-0.25f, 0.0f, 0.0f), 3);
							SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 20.0f, g_aMinion[nCntMinion].pos.y - 20.0f, 0.0f), D3DXVECTOR3(7.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.07f, 0.0f), 3);
							SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 20.0f, g_aMinion[nCntMinion].pos.y - 20.0f, 0.0f), D3DXVECTOR3(-7.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.07f, 0.0f), 3);
							SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 20.0f, g_aMinion[nCntMinion].pos.y - 20.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), D3DXVECTOR3(0.2f, -0.2f, 0.0f), 3);
							SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 20.0f, g_aMinion[nCntMinion].pos.y - 20.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.2f, -0.2f, 0.0f), 3);
							SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.2f, 0.0f), 3);
						}
						else if (g_aMinion[nCntMinion].nPatternAnim == 4)
						{
							g_aMinion[nCntMinion].state = MINIONSTATE_NORMAL;
							g_aMinion[nCntMinion].nCounterState = 240;
							g_aMinion[nCntMinion].nCountAnim = 0;
							g_aMinion[nCntMinion].nPatternAnim = 0;
						}
					}

					break;
				}

				//頂点の設定
				pVtx[(nCntMinion * 4 ) + 1].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 80.0f, g_aMinion[nCntMinion].pos.y - 200.0f, 0.0f);
				pVtx[(nCntMinion * 4 ) + 0].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 80.0f, g_aMinion[nCntMinion].pos.y - 200.0f, 0.0f);
				pVtx[(nCntMinion * 4 ) + 3].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 80.0f, g_aMinion[nCntMinion].pos.y, 0.0f);
				pVtx[(nCntMinion * 4 ) + 2].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 80.0f, g_aMinion[nCntMinion].pos.y, 0.0f);

				//テクスチャ座標の設定
				pVtx[(nCntMinion * 4 ) + 0].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.25f), 0.0f);
				pVtx[(nCntMinion * 4 ) + 1].tex = D3DXVECTOR2(0.25f + (g_aMinion[nCntMinion].nPatternAnim * 0.25f), 0.0f);
				pVtx[(nCntMinion * 4 ) + 2].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.25f), 1.0f);
				pVtx[(nCntMinion * 4 ) + 3].tex = D3DXVECTOR2(0.25f + (g_aMinion[nCntMinion].nPatternAnim * 0.25f), 1.0f);

				break;

				//=======================================================================================================================================================
				//=======================================================================================================================================================

			case 5:																												//XIX 太陽

				if (g_aMinion[nCntMinion].pos.x <= SCREEN_WIDTH * 0.5f)
				{
					g_aMinion[nCntMinion].nDirection = 1;
				}
				else
				{
					g_aMinion[nCntMinion].nDirection = -1;
				}

				if (g_aMinion[nCntMinion].state == MINIONSTATE_APPEAR)
				{
					if (g_aMinion[nCntMinion].pos.y < 200.0f)
					{
						g_aMinion[nCntMinion].move.y = 2.0f;
					}
					else
					{
						g_aMinion[nCntMinion].move.y = 0.0f;
						g_aMinion[nCntMinion].nCounterState++;
						g_aMinion[nCntMinion].nCountAnim++;
					}

					if (g_aMinion[nCntMinion].nCounterState == 180)
					{
						g_aMinion[nCntMinion].nPatternAnim++;
					}

					if (g_aMinion[nCntMinion].nCounterState >= 360)
					{
						g_aMinion[nCntMinion].state = MINIONSTATE_RETURN;
						*pSwitch = 0;
					}
					
					//テクスチャ座標の設定
					pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.0f);
					pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.125f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.0f);
					pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.125f);
					pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.125f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.125f);
				}
				else if (g_aMinion[nCntMinion].state == MINIONSTATE_RETURN)
				{
					if (g_aMinion[nCntMinion].pos.x < 640.0f)
					{
						g_aMinion[nCntMinion].move.x = -2.0f;
					}
					else
					{
						g_aMinion[nCntMinion].move.x = 2.0f;
					}

					if (g_aMinion[nCntMinion].pos.x <= -100.0f || g_aMinion[nCntMinion].pos.x >= SCREEN_WIDTH + 100.0f)
					{
						g_aMinion[nCntMinion].pos.y = 360.0f;
						g_aMinion[nCntMinion].move.x = 0.0f;
						g_aMinion[nCntMinion].state = MINIONSTATE_NORMAL;
						g_aMinion[nCntMinion].nCounterState = 240;
					}
				}
				else if (g_aMinion[nCntMinion].state == MINIONSTATE_NORMAL)
				{
					g_aMinion[nCntMinion].nCounterState--;

					if (g_aMinion[nCntMinion].nCounterState <= 0)
					{
						g_aMinion[nCntMinion].nCountAnim = 0;
						g_aMinion[nCntMinion].nPatternAnim = 0;
						g_aMinion[nCntMinion].nCounterState = 90;
						g_aMinion[nCntMinion].state = MINIONSTATE_ATTACK;

						if (pPlayer->pos.x <= 640.0f)
						{
							g_aMinion[nCntMinion].pos.x = -100.0f;
						}
						else
						{
							g_aMinion[nCntMinion].pos.x = SCREEN_WIDTH + 100.0f;
						}
					}
				}
				else if (g_aMinion[nCntMinion].state == MINIONSTATE_ATTACK)
				{
					g_aMinion[nCntMinion].nCountAnim++;
					g_aMinion[nCntMinion].nCounterState--;

					if (g_aMinion[nCntMinion].pos.x < 0.0f && g_aMinion[nCntMinion].nDirection > 0)
					{
						g_aMinion[nCntMinion].move.x = 2.5f;

						if (g_aMinion[nCntMinion].nCountAnim % 5 == 4)
						{
							g_aMinion[nCntMinion].nPatternAnim ^= 1;
						}
					}
					else if (g_aMinion[nCntMinion].pos.x > SCREEN_WIDTH && g_aMinion[nCntMinion].nDirection < 0)
					{
						g_aMinion[nCntMinion].move.x = -2.5f;

						if (g_aMinion[nCntMinion].nCountAnim % 5 == 4)
						{
							g_aMinion[nCntMinion].nPatternAnim ^= 1;
						}
					}
					else
					{
						g_aMinion[nCntMinion].move.x = 0.0f;

						switch (g_aMinion[nCntMinion].nPatternAnim)
						{
						case 0:
							g_aMinion[nCntMinion].nPatternAnim = 2;
							break;

						case 1:
							g_aMinion[nCntMinion].nPatternAnim = 2;
							break;

						case 2:
							if (g_aMinion[nCntMinion].nCountAnim % 30 == 29)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
							}
							break;

						case 6:
							if (g_aMinion[nCntMinion].nCountAnim % 5 == 4)
							{
								g_aMinion[nCntMinion].nPatternAnim = 3;
							}
							break;

						default:
							if (g_aMinion[nCntMinion].nCountAnim % 5 == 4)
							{
								g_aMinion[nCntMinion].nPatternAnim++;
							}
							break;

						}

						if (pPlayer->pos.y <= g_aMinion[nCntMinion].pos.y + PLAYER_HEIGHT && pPlayer->pos.y >= g_aMinion[nCntMinion].pos.y - 200.0f &&
							pPlayer->pos.x >= g_aMinion[nCntMinion].pos.x - (PLAYER_WIDTH * 0.5f) - 50.0f && pPlayer->pos.x <= g_aMinion[nCntMinion].pos.x + (PLAYER_WIDTH * 0.5f) + 50.0f)
						{
							if(pPlayer->state != PLAYERSTATE_DAMAGE && pPlayer->state != PLAYERSTATE_DEATH)
							{
								pPlayer->state = PLAYERSTATE_DAMAGE;
								pPlayer->nCounterState = 180;
								AddScore(-250);
								PlaySound(SOUND_LABEL_SE_FIRE);
								SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS250);
							}
						}

						//テクスチャ座標の設定
						pVtx[(nCntMinion * 4) + 0].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.125f);
						pVtx[(nCntMinion * 4) + 1].tex = D3DXVECTOR2(0.125f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.125f);
						pVtx[(nCntMinion * 4) + 2].tex = D3DXVECTOR2(0.0f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.25f);
						pVtx[(nCntMinion * 4) + 3].tex = D3DXVECTOR2(0.125f + (g_aMinion[nCntMinion].nPatternAnim * 0.125f), 0.25f);
					}

					if (g_aMinion[nCntMinion].nCounterState <= 0)
					{
						PlaySound(SOUND_LABEL_SE_FIRE);

						SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(10.0f * g_aMinion[nCntMinion].nDirection, 0.0f, 0.0f), D3DXVECTOR3(0.01f, 0.0f, 0.0f), 4);
						SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(7.0f * g_aMinion[nCntMinion].nDirection, 7.0f, 0.0f), D3DXVECTOR3(0.007f, 0.007f, 0.0f), 4);
						SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(7.0f * g_aMinion[nCntMinion].nDirection, -7.0f, 0.0f), D3DXVECTOR3(0.007f, 0.007f, 0.0f), 4);

						SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(8.7f * g_aMinion[nCntMinion].nDirection, 5.0f, 0.0f), D3DXVECTOR3(0.09f, 0.005f, 0.0f), 4);
						SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(8.7f * g_aMinion[nCntMinion].nDirection, -5.0f, 0.0f), D3DXVECTOR3(0.09f, 0.005f, 0.0f), 4);

						SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, 8.7f, 0.0f), D3DXVECTOR3(0.005f, 0.09f, 0.0f), 4);
						SetBullet(D3DXVECTOR3(g_aMinion[nCntMinion].pos.x, g_aMinion[nCntMinion].pos.y - 50.0f, 0.0f), D3DXVECTOR3(5.0f * g_aMinion[nCntMinion].nDirection, -8.7f, 0.0f), D3DXVECTOR3(0.005f, 0.09f, 0.0f), 4);

						g_aMinion[nCntMinion].nCounterState = 20;
					}
					if (g_aMinion[nCntMinion].nCountAnim >= 300)
					{
						g_aMinion[nCntMinion].state = MINIONSTATE_RETURN;
					}
				}

				//頂点の設定
				pVtx[(nCntMinion * 4) + 1].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 100.0f, g_aMinion[nCntMinion].pos.y - 200.0f, 0.0f);
				pVtx[(nCntMinion * 4) + 0].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 100.0f, g_aMinion[nCntMinion].pos.y - 200.0f, 0.0f);
				pVtx[(nCntMinion * 4) + 3].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x + 100.0f, g_aMinion[nCntMinion].pos.y, 0.0f);
				pVtx[(nCntMinion * 4) + 2].pos = D3DXVECTOR3(g_aMinion[nCntMinion].pos.x - 100.0f, g_aMinion[nCntMinion].pos.y, 0.0f);

				break;
			}
		}

		//if (pPlayer->pos.x + PLAYER_WIDTH > g_aMinion[nCntMinion].pos.x - g_aMinion[nCntMinion].fWidth &&
		//	pPlayer->pos.x - PLAYER_WIDTH < g_aMinion[nCntMinion].pos.x - g_aMinion[nCntMinion].fWidth &&
		//	pPlayer->pos.y - PLAYER_HEIGHT < g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight &&
		//	pPlayer->pos.y > g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight ||
		//	pPlayer->pos.x - PLAYER_WIDTH < g_aMinion[nCntMinion].pos.x + g_aMinion[nCntMinion].fWidth &&
		//	pPlayer->pos.x + PLAYER_WIDTH > g_aMinion[nCntMinion].pos.x + g_aMinion[nCntMinion].fWidth &&
		//	pPlayer->pos.y - PLAYER_HEIGHT < g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight &&
		//	pPlayer->pos.y > g_aMinion[nCntMinion].pos.y - g_aMinion[nCntMinion].fHeight)
		//{
		//	//ダメージ
		//}		
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMinion->Unlock();
}

Minion*GetMinion(void)
{
	return &g_aMinion[0];
}