//==========================================//
//                                          //
//              敵のファイル                //
//　　　　　　 Author: Ricci Alex           //
//                                          //
//==========================================//

//インクルードファイル
#include "Enemy.h"
#include "platform.h"

//マクロ定義
#define SLIME_WIDTH		(40.0f)								//スライムの幅
#define SLIME_HEIGHT	(40.0f)								//スライムの高さ

//グローバル変数を宣言
LPDIRECT3DTEXTURE9 g_apTextureSlime[2] = {};					//敵のテクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureMimic = NULL;
LPDIRECT3DTEXTURE9 g_apTextureCard = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵型の配列を宣言する
int g_aDamage[MAX_ENEMY];
int g_aMemoryInteraction[MAX_ENEMY];

//敵の初期化処理
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの情報へのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCntEnemy;					//数をカウントする変数を宣言する

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SpriteSheetCompleto.png",
		&g_apTextureSlime[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SlimeGreen_SpriteSheet2.png",
		&g_apTextureSlime[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Mimic_SpriteSheet.png",
		&g_apTextureMimic);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\CardEnemy.png",
		&g_apTextureCard);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//敵型の変数の各パラメータの初期化
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//現在の位置
		g_aEnemy[nCntEnemy].LastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//前回の位置
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量
		g_aEnemy[nCntEnemy].MoveState = MOVESTATE_FALLING;						//移動状態
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;							//敵の状態
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;		//プレイヤーが見えるかどうか
		g_aEnemy[nCntEnemy].fSight = 250.0f;									//視力
		g_aEnemy[nCntEnemy].fHeight = SLIME_HEIGHT;								//高さ
		g_aEnemy[nCntEnemy].fWidth = SLIME_WIDTH;								//高さ
		g_aEnemy[nCntEnemy].nType = ENEMYTYPE_BLUESLIME;						//種類
		g_aEnemy[nCntEnemy].nCountAnim = 0;										//アニメーションカウンター
		g_aEnemy[nCntEnemy].nPatternAnim = 0;									//アニメーションパターン
		g_aEnemy[nCntEnemy].nChaseCounter = 0;									//追いかけるカウンター
		g_aEnemy[nCntEnemy].nCounterState = 0;									//状態カウンター
		g_aEnemy[nCntEnemy].nCurrentPlatform = 101;								//現在のプラットフォーム
		g_aEnemy[nCntEnemy].nDirection = 1;										//向き
		g_aEnemy[nCntEnemy].bUse = false;										//使用されているかどうか

		//グローバル変数の初期化
		g_aDamage[nCntEnemy] = 0;
		g_aMemoryInteraction[nCntEnemy] = 0;

		//頂点設定
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.125f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
		pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//敵の終了処理
void UninitEnemy(void)
{
	int nCount;
	
	//テクスチャの破棄
	for (nCount = 0; nCount < 2; nCount++)
	{
		
		if (g_apTextureSlime[nCount] != NULL)
		{					
			g_apTextureSlime[nCount]->Release();
			g_apTextureSlime[nCount] = NULL;
		}
	}
	if (g_apTextureMimic != NULL)
	{			   
		g_apTextureMimic->Release();
		g_apTextureMimic = NULL;
	}
	if (g_apTextureCard != NULL)
	{			   
		g_apTextureCard->Release();
		g_apTextureCard = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//敵の更新処理
void UpdateEnemy(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	WATER*pWater;		//水情報へのポインタ
	Player*pPlayer;		//プレイヤー情報へのポインタ
	int nCount;			//数をカウントする変数を宣言
	int nCollision;		//ブロックの当たり判定

	pWater = GetWater();		//水の情報を取得
	pPlayer = GetPlayer();		//プレイヤー情報の取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (g_aEnemy[nCount].bUse == true)
		{//使用されている場合
			
			if (g_aEnemy[nCount].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCount].nType == ENEMYTYPE_GREENSLIME || g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
			{//スライムの場合、プレイヤーが見えるかどうか判定する
				EnemyEncounter(nCount, SLIME_HEIGHT);
			}
			
			//死んだ状態だったら、画面から出す
			if (g_aEnemy[nCount].state == ENEMYSTATE_DEATH)
			{
				if (g_aEnemy[nCount].pos.y <= 650.0f)
				{
					g_aEnemy[nCount].move.x = 0.0f;
					g_aEnemy[nCount].move.y = 5.0f;
				}
				if (g_aEnemy[nCount].pos.y >= 660.0f)
				{
					g_aEnemy[nCount].move.x = -5.0f;
					g_aEnemy[nCount].move.y = 0.0f;
				}
				
			}

			if (g_aEnemy[nCount].EncounterState != ENEMYSTATE_ENCOUNTER_FALSE)
			{//プレイヤーを見た場合
				g_aEnemy[nCount].nChaseCounter--;

				if (g_aEnemy[nCount].nChaseCounter <= 0)
				{
					if (g_aEnemy[nCount].nPatternAnim == 0)
					{
						//プレイヤーが見えない状態にする
						g_aEnemy[nCount].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
						g_aEnemy[nCount].nChaseCounter = 0;
					}
					
				}
			}

			
			if (g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT && g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{//落下の場合
				g_aEnemy[nCount].move.y += 0.5f;				//移動量の更新
			}
			if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART ||
				g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
			{
				g_aEnemy[nCount].move.y -= 0.5f;
			}

			//プレイヤーの位置の更新
			g_aEnemy[nCount].pos.x += g_aEnemy[nCount].move.x;
			g_aEnemy[nCount].pos.y += g_aEnemy[nCount].move.y;

			if (g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{
				// ブロックの当たり判定
					nCollision = BlockInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].LastPos, &g_aEnemy[nCount].move, 40.0f, 40.0f);

				if (nCollision == 1 || nCollision == 4)
				{//着地の場合
					g_aEnemy[nCount].MoveState = MOVESTATE_LANDED;
				}

				else if (nCollision == 2 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT)
				{//下から当たる場合
					g_aEnemy[nCount].MoveState = MOVESTATE_FALLING;
				}

				else if (nCollision == 3 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT)
				{
					g_aEnemy[nCount].MoveState = MOVESTATE_FALLING;
				}

				//コウモリスライムの場合、ブロックに当たると上に行く
				if (g_aEnemy[nCount].move.y != 0.0f && g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
				{
					g_aEnemy[nCount].move.y = 0.0f;
				}
				if (g_aEnemy[nCount].pos.x == g_aEnemy[nCount].LastPos.x && g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT && g_aEnemy[nCount].EncounterState != ENEMYSTATE_ENCOUNTER_LOST)
				{
					g_aEnemy[nCount].move.y = -2.0f;
				}

				nCollision = BlockInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].LastPos, &g_aEnemy[nCount].move, -40.0f, 40.0f);

				if (nCollision == 3 && g_aEnemy[nCount].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE ||
					g_aEnemy[nCount].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCount].nPatternAnim == 0 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT)
				{//ブロックから落ちないように
					g_aEnemy[nCount].move.x *= -1;
				}

				nCollision = WaterInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].move, (45.0f + (g_aEnemy[nCount].move.x * g_aEnemy[nCount].nDirection)), 40.0f);

				if (nCollision == 1 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT && g_aEnemy[nCount].EncounterState != ENEMYSTATE_ENCOUNTER_TRUE ||
					nCollision == 1 && g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
				{//水に入らないように
					g_aEnemy[nCount].pos.x -= g_aEnemy[nCount].move.x * g_aEnemy[nCount].nDirection;		//体半分以下水にあったら、早く出る
					g_aEnemy[nCount].move.x *= -1;															//方向を逆にする

					if (g_aMemoryInteraction[nCount] == 0)
					{
						g_aMemoryInteraction[nCount] = 1;
					}
					else
					{
						g_aEnemy[nCount].pos.x += 5.0f * g_aEnemy[nCount].nDirection;
						g_aEnemy[nCount].move.x *= -1;
					}
					
				}
				else
				{
					g_aMemoryInteraction[nCount] = 0;
				}

				nCollision = WaterInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].move, 0.0f, 40.0f);

				if (nCollision == 1)
				{//体半分以上水にある場合
					if (g_aEnemy[nCount].nType != ENEMYTYPE_CARD_DIAMOND && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_HEART &&
						g_aEnemy[nCount].nType != ENEMYTYPE_CARD_CLUB && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_SPADE)
					{
						PlaySound(SOUND_LABEL_SE_WATER);							//水の音を再生
						g_aEnemy[nCount].state = ENEMYSTATE_DEATH;					//死んだ状態にする
						//g_aEnemy[nCount].move.x *= -1;
					}
					
				}
			}
			
			if (g_aEnemy[nCount].nType != ENEMYTYPE_CARD_DIAMOND && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_HEART &&
				g_aEnemy[nCount].nType != ENEMYTYPE_CARD_CLUB && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_SPADE)
			{
				//ワープ処理
				WarpEnemy(nCount);
			}

			//頂点座標の更新
			if (g_aEnemy[nCount].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCount].nType == ENEMYTYPE_GREENSLIME || g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
			{//スライムの場合
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_MIMIC)
			{//ミミックの場合
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART ||
				g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
			{//カードの場合
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 25.0f, g_aEnemy[nCount].pos.y - 50.0f, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 25.0f, g_aEnemy[nCount].pos.y - 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 25.0f, g_aEnemy[nCount].pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 25.0f, g_aEnemy[nCount].pos.y, 0.0f);
			}

			//向きの更新
			if (g_aEnemy[nCount].move.x < 0 && g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{//左向き
				g_aEnemy[nCount].nDirection = -1;
			}
			else if (g_aEnemy[nCount].move.x > 0 && g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{//右向き
				g_aEnemy[nCount].nDirection = 1;
			}

			//アニメーション処理
			if (g_aEnemy[nCount].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCount].nType == ENEMYTYPE_GREENSLIME || g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
			{
				SlimeAnimation(nCount);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_MIMIC)
			{
				MimicAnimation(nCount);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND ||
				g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
			{
				CardAnimation(nCount);
			}

			if (g_aDamage[nCount] > 0)
			{
				g_aDamage[nCount]--;
			}

			if (pPlayer->pos.x - (PLAYER_WIDTH * 0.5f)< g_aEnemy[nCount].pos.x && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x&&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y ||
				pPlayer->pos.x - (PLAYER_WIDTH * 0.5f) < g_aEnemy[nCount].pos.x && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x&&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight ||
				pPlayer->pos.x - (PLAYER_WIDTH * 0.5f)< g_aEnemy[nCount].pos.x && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x &&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y ||
				pPlayer->pos.x - (PLAYER_WIDTH * 0.5f) < g_aEnemy[nCount].pos.x  && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x&&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight)
			{//プレイヤーに当たったら
				if (pPlayer->state != PLAYERSTATE_DAMAGE && g_aEnemy[nCount].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && pPlayer->state != PLAYERSTATE_DEATH)
				{//プレイヤー状態の確認
					AddScore(-250);								//スコアを下がる
					pPlayer->nCounterState = 180;				//状態カウンターの設定
					pPlayer->state = PLAYERSTATE_DAMAGE;		//プレイヤーの状態をダメージ状態にする
					SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS250);

					if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND ||
						g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
					{//ダメージサウンドを再生する
						PlaySound(SOUND_LABEL_SE_SLASH);
					}
					else
					{
						PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);
					}

					if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND ||
						g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
					{//ノックバックの処理
						pPlayer->move.x = 15.0f * g_aEnemy[nCount].nDirection;
					}
				}
			}
			

			//前回の位置の更新
			g_aEnemy[nCount].LastPos = g_aEnemy[nCount].pos;

		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();	

}

//敵の描画処理
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスの情報へのポインタ
	int nCntEnemy;				//数をカウントする変数を宣言する

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_MIMIC)
			{
				pDevice->SetTexture(0, g_apTextureMimic);
			}
			else if(g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_DIAMOND || 
				g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_SPADE)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureCard);
			}
			else
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_apTextureSlime[0]);
			}
			

			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
	
}

//敵の設定
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE nType)
{
	int nCntEnemy;		//数をカウントする変数を宣言する

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//敵の各ステータスを設定する
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//敵の位置
			g_aEnemy[nCntEnemy].pos = pos;
			//敵の前回の位置の設定
			g_aEnemy[nCntEnemy].LastPos = pos;
			//敵の移動量
			g_aEnemy[nCntEnemy].move = move;
			//敵の状態
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			//種類
			g_aEnemy[nCntEnemy].nType = nType;
			//状態カウンター
			g_aEnemy[nCntEnemy].nCounterState = 0;
			//幅
			if (g_aEnemy[nCntEnemy].nType < 3)
			{
				g_aEnemy[nCntEnemy].fWidth = 20.0f;
			}
			else if (g_aEnemy[nCntEnemy].nType == 3)
			{
				g_aEnemy[nCntEnemy].fWidth = 15.0f;
			}

			//使用されているにする
			g_aEnemy[nCntEnemy].bUse = true;

			//頂点の設定
			pVtx[1].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y - 40.0f, pos.z);
			pVtx[0].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y - 40.0f, pos.z);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y, pos.z);
			pVtx[2].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y, pos.z);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.125f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
			pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);

			if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_SLIMEBAT || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_GREENSLIME)
			{
				g_aEnemy[nCntEnemy].MoveState = MOVESTATE_LANDED;

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			}
			else if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_MIMIC)
			{
				pVtx[1].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y - 50.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y - 50.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y, pos.z);

				pVtx[3].tex = D3DXVECTOR2(0.0f, 0.25f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f, 0.25f);
				pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
			}
			else if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_DIAMOND ||
				g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_SPADE)
			{
				pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 80.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 80.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y, pos.z);

				g_aEnemy[nCntEnemy].MoveState = MOVESTATE_LANDED;

				//カード敵のテクスチャ座標の設定
				switch (g_aEnemy[nCntEnemy].nType)
				{
				case ENEMYTYPE_CARD_HEART:
					pVtx[3].tex = D3DXVECTOR2(0.043f, 0.59f);
					pVtx[1].tex = D3DXVECTOR2(0.043f, 0.53f);
					pVtx[2].tex = D3DXVECTOR2(0.083f, 0.59f);
					pVtx[0].tex = D3DXVECTOR2(0.083f, 0.53f);
					break;

				case ENEMYTYPE_CARD_DIAMOND:
					pVtx[3].tex = D3DXVECTOR2(0.5f, 0.625f);
					pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
					pVtx[2].tex = D3DXVECTOR2(0.625f, 0.625f);
					pVtx[0].tex = D3DXVECTOR2(0.625f, 0.5f);
					break;

				case ENEMYTYPE_CARD_CLUB:
					pVtx[3].tex = D3DXVECTOR2(0.0f, 0.75f);
					pVtx[1].tex = D3DXVECTOR2(0.0f, 0.625f);
					pVtx[2].tex = D3DXVECTOR2(0.125f, 0.75f);
					pVtx[0].tex = D3DXVECTOR2(0.125f, 0.625f);
					break;

				case ENEMYTYPE_CARD_SPADE:
					pVtx[3].tex = D3DXVECTOR2(0.5f, 0.75f);
					pVtx[1].tex = D3DXVECTOR2(0.5f, 0.625f);
					pVtx[2].tex = D3DXVECTOR2(0.625f, 0.75f);
					pVtx[0].tex = D3DXVECTOR2(0.625f, 0.625f);
					break;
				}
				
			}

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//ワープ処理
void WarpEnemy(int nCntEnemy)
{
	Player*pPlayer;					//プレス情報へのポインタ

	pPlayer = GetPlayer();			//プレス情報の取得

	if (g_aEnemy[nCntEnemy].pos.x >= SCREEN_WIDTH - 30.0f && g_aEnemy[nCntEnemy].move.x > 0)
	{//画面の右側から出た場合
		
		if (g_aEnemy[nCntEnemy].MoveState == MOVESTATE_LANDED)
		{
			g_aEnemy[nCntEnemy].move.x *= -1.0f;
		}
		else
		{
			g_aEnemy[nCntEnemy].pos.x = -20.0f;
		}
	}
	if (g_aEnemy[nCntEnemy].pos.x <= 30.0f && g_aEnemy[nCntEnemy].move.x < 0)
	{//画面の左側から出た場合
		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth <= 0.0f)
		{//敵が水に落ちた場合
			AddScore(500);								//スコアを加算する
			g_aEnemy[nCntEnemy].bUse = false;			//敵を使用されていない状態にする
			SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_PLUS500);
		}

		if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_DEATH)
		{//他の状態の場合
			if (g_aEnemy[nCntEnemy].MoveState == MOVESTATE_LANDED)
			{
				g_aEnemy[nCntEnemy].move.x *= -1.0f;
			}
			else
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH + 20.0f;
			}
		}
		
	}
	/*if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT - 25.0f)
	{
		g_aEnemy[nCntEnemy].pos.y = SCREEN_HEIGHT - 25.0f;
		g_aEnemy[nCntEnemy].MoveState = MOVESTATE_LANDED;
	}*/
}

//敵のアニメーション処理
void SlimeAnimation(int nCntEnemy)
{
	Player*pPlayer;							//プレス情報へのポインタ

	pPlayer = GetPlayer();					//プレイヤー情報の取得

	g_aEnemy[nCntEnemy].nCountAnim++;		//アニメーションカウンターの更新

	switch (g_aEnemy[nCntEnemy].nType)
	{
		//==================================================================================================================================================================
		//															青スライム
	case ENEMYTYPE_BLUESLIME:

		switch (g_aEnemy[nCntEnemy].EncounterState)
		{
		case ENEMYSTATE_ENCOUNTER_FALSE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:

				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//普通の移動
					g_aEnemy[nCntEnemy].nPatternAnim++;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				break;

			case 1:

				g_aEnemy[nCntEnemy].move.x = 2.0f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 10)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}


			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_TRUE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 1:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{//普通の移動
					g_aEnemy[nCntEnemy].move.x = 6.0f * g_aEnemy[nCntEnemy].nDirection;
					g_aEnemy[nCntEnemy].move.y = -8.0f;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 2:
				
				if (g_aEnemy[nCntEnemy].nCountAnim >= 12)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 3:
				g_aEnemy[nCntEnemy].move.x -= 0.19f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 4:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 5:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}
			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 4, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_LOST:

			g_aEnemy[nCntEnemy].move.x = 0.0f;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;

			if (g_aEnemy[nCntEnemy].nCountAnim % 30 == 29)
			{//普通の移動
				g_aEnemy[nCntEnemy].nDirection *= -1;
			}
			if (g_aEnemy[nCntEnemy].nCountAnim >= 120)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
			}

			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.126f);

			break;
		}
		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH)
		{
			g_aEnemy[nCntEnemy].nDirection = 1;

			if (g_aEnemy[nCntEnemy].nCountAnim % 15 == 14)
			{//普通の移動
				if (g_aEnemy[nCntEnemy].nPatternAnim == 1)
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 2;
				}
				else
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 1;
				}
			}
			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 4, 0.125f, 0.126f);
		}

		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															緑スライム
	case ENEMYTYPE_GREENSLIME:

		switch (g_aEnemy[nCntEnemy].EncounterState)
		{
		case ENEMYSTATE_ENCOUNTER_FALSE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:

				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//普通の移動
					g_aEnemy[nCntEnemy].nPatternAnim++;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				break;

			case 1:

				g_aEnemy[nCntEnemy].move.x = 2.0f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 10)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}


			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_TRUE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 1:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{//普通の移動
					g_aEnemy[nCntEnemy].move.x = 4.0f * g_aEnemy[nCntEnemy].nDirection;
					g_aEnemy[nCntEnemy].move.y = -6.0f;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 2:

				if (g_aEnemy[nCntEnemy].nCountAnim >= 12)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 3:
				g_aEnemy[nCntEnemy].move.x -= 0.19f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 4:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 60)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 5:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim == 1)
				{
					SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y - (SLIME_HEIGHT * 0.5f), 0.0f),
						D3DXVECTOR3(4.0f * g_aEnemy[nCntEnemy].nDirection, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
					PlaySound(SOUND_LABEL_SE_NORMALBULLET);
				}
				else if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//普通の移動
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}
			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_LOST:

			g_aEnemy[nCntEnemy].move.x = 0.0f;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;

			if (g_aEnemy[nCntEnemy].nCountAnim % 30 == 29)
			{//普通の移動
				g_aEnemy[nCntEnemy].nDirection *= -1;
			}
			if (g_aEnemy[nCntEnemy].nCountAnim >= 120)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
			}

			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.126f);

			break;
		}
		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH)
		{
			g_aEnemy[nCntEnemy].nDirection = 1;

			if (g_aEnemy[nCntEnemy].nCountAnim % 15 == 14)
			{//普通の移動
				if (g_aEnemy[nCntEnemy].nPatternAnim == 1)
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 2;
				}
				else
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 1;
				}
			}
			//テクスチャ座標の更新
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.126f);
		}

		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															コウモリスライム
		case ENEMYTYPE_SLIMEBAT:

			switch (g_aEnemy[nCntEnemy].EncounterState)
			{
			case ENEMYSTATE_ENCOUNTER_FALSE:

				g_aEnemy[nCntEnemy].move.x = 2.0f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{//普通の移動
					g_aEnemy[nCntEnemy].nPatternAnim++;

					if (g_aEnemy[nCntEnemy].nPatternAnim >= 2)
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 0;
					}

					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				//テクスチャ座標の更新
				UpdateEnemyTex(nCntEnemy, 6, 0.125f, 0.126f);

				break;
			case ENEMYSTATE_ENCOUNTER_TRUE:

				if ((g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x) * g_aEnemy[nCntEnemy].nDirection < 0)
				{
					g_aEnemy[nCntEnemy].move.x = 4.0f * g_aEnemy[nCntEnemy].nDirection;
				}
				else
				{
					g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
				}
				
				if (g_aEnemy[nCntEnemy].nCountAnim >= 10)
				{//普通の移動
					g_aEnemy[nCntEnemy].nPatternAnim++;

					if (g_aEnemy[nCntEnemy].nPatternAnim >= 2)
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 0;
					}

					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				//テクスチャ座標の更新
				UpdateEnemyTex(nCntEnemy, 6, 0.125f, 0.126f);
				break;

			case ENEMYSTATE_ENCOUNTER_LOST:

				g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;

				break;
			}
			if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH)
			{
				g_aEnemy[nCntEnemy].nDirection = 1;

				if (g_aEnemy[nCntEnemy].nCountAnim % 15 == 14)
				{//普通の移動
					if (g_aEnemy[nCntEnemy].nPatternAnim == 1)
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 2;
					}
					else
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 1;
					}
				}
				//テクスチャ座標の更新
				UpdateEnemyTex(nCntEnemy, 6, 0.125f, 0.126f);
			}

			break;
			//==================================================================================================================================================================
	}
}

//ミミックのアニメーションと攻撃処理
void MimicAnimation(int nCntEnemy)
{
	Player*pPlayer;		//プレイヤーへのポインタ
	int nInteraction;	
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	MODE mode;			//モード

	mode = GetMode();			//モードの取得
	pPlayer = GetPlayer();		//プレイヤー情報の取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//ミミックの近くにエンターキーを押したら
	if (pPlayer->pos.x - (PLAYER_WIDTH * 0.5f) <= g_aEnemy[nCntEnemy].pos.x + 30.0f && pPlayer->pos.y > g_aEnemy[nCntEnemy].pos.y - 30.0f && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCntEnemy].pos.y - 30.0f ||
		pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) >= g_aEnemy[nCntEnemy].pos.x + 30.0f && pPlayer->pos.y > g_aEnemy[nCntEnemy].pos.y - 30.0f && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCntEnemy].pos.y - 30.0f)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_TRUE;			//攻撃状態にする
			g_aEnemy[nCntEnemy].nPatternAnim++;										//パターンの更新
			g_aEnemy[nCntEnemy].nCounterState = 60;									//状態カウンターの設定
			g_aEnemy[nCntEnemy].nChaseCounter = 500;								//攻撃カウンターの設定
		}
	}

	//普通の状態に戻す
	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_LOST)
	{
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
	}

	//アニメーションカウンターを0に戻す
	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE)
	{
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCountAnim = 0;
	}

	//==================================================================================================================================================================
	//															攻撃状態のアニメーション
	else if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE)
	{
		if (g_aEnemy[nCntEnemy].nCounterState > 0)
		{
			g_aEnemy[nCntEnemy].nCounterState--;

			if (g_aEnemy[nCntEnemy].nCounterState == 30)
			{
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			else if (g_aEnemy[nCntEnemy].nCounterState == 0)
			{
				g_aEnemy[nCntEnemy].nPatternAnim = 0;
			}
		}
		if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x)
		{
			g_aEnemy[nCntEnemy].nDirection = 1;
		}
		else
		{
			g_aEnemy[nCntEnemy].nDirection = -1;
		}

		if (g_aEnemy[nCntEnemy].nCounterState <= 0)
		{
			g_aEnemy[nCntEnemy].move.x = 2.5f * g_aEnemy[nCntEnemy].nDirection;
			g_aEnemy[nCntEnemy].nCountAnim++;

			if (g_aEnemy[nCntEnemy].nCountAnim % 5 == 4)
			{
				g_aEnemy[nCntEnemy].nPatternAnim++;

				if (g_aEnemy[nCntEnemy].nPatternAnim >= 4)
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
			}
		}

	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//																ブロックの当たり判定
	nInteraction = BlockInteraction(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].LastPos, &g_aEnemy[nCntEnemy].move, -45.0f, 60.0f);

	//ブロックから落ちないように
	if (nInteraction == 3)
	{
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
		g_aEnemy[nCntEnemy].move.x = 0;
	}

	//==================================================================================================================================================================
	//															攻撃カウンターが0になると普通の状態に戻す
	if (g_aEnemy[nCntEnemy].nChaseCounter <= 0)
	{
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
		g_aEnemy[nCntEnemy].move.x = 0;
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//																	テクスチャ座標の更新
	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nCounterState != 0 || g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE)
	{
		UpdateEnemyTex(nCntEnemy, 0, 0.25, 0.22);
	}
	else if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nCounterState == 0)
	{
		UpdateEnemyTex(nCntEnemy, 1, 0.25, 0.22);
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//														頂点カラーの更新
	if (mode == MODE_GAME_BONUSSTAGE)
	{//ボーナスステージの場合

	 //==================================================================================================================================================================
	 //										プレイヤーが遠かったら、真っ黒にして、近づくと普通に表示する
		if (g_aEnemy[nCntEnemy].pos.y < pPlayer->pos.y + 10.0f && g_aEnemy[nCntEnemy].pos.y > pPlayer->pos.y - 100.0f &&
			g_aEnemy[nCntEnemy].pos.x < pPlayer->pos.x + 150.0f && g_aEnemy[nCntEnemy].pos.x > pPlayer->pos.x - 150.0f)
		{
			pVtx[(nCntEnemy * 4) + 0].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[(nCntEnemy * 4) + 1].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[(nCntEnemy * 4) + 2].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[(nCntEnemy * 4) + 3].col = D3DCOLOR_RGBA(150, 150, 150, 255);
		}
		else
		{
			pVtx[(nCntEnemy * 4) + 0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
			pVtx[(nCntEnemy * 4) + 1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
			pVtx[(nCntEnemy * 4) + 2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
			pVtx[(nCntEnemy * 4) + 3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		}
	}
	//==================================================================================================================================================================
	else
	{//他の場合
		pVtx[(nCntEnemy * 4) + 0].col = D3DCOLOR_RGBA(200, 200, 200, 255);
		pVtx[(nCntEnemy * 4) + 1].col = D3DCOLOR_RGBA(200, 200, 200, 255);
		pVtx[(nCntEnemy * 4) + 2].col = D3DCOLOR_RGBA(200, 200, 200, 255);
		pVtx[(nCntEnemy * 4) + 3].col = D3DCOLOR_RGBA(200, 200, 200, 255);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//カード敵の更新処理
void CardAnimation(int nCntEnemy)
{
	Player*pPlayer;		//プレイヤー情報へのポインタ
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	int nSuit;			//カードの種類を格納する変数
	MODE mode;			//モード

	mode = GetMode();			//モードの取得
	pPlayer = GetPlayer();		//プレイヤー情報の取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//==================================================================================================================================================================
	//													スプライトの最初の列の設定
	switch (g_aEnemy[nCntEnemy].nType)
	{
	case ENEMYTYPE_CARD_HEART:
		nSuit = 0;
		break;
	case ENEMYTYPE_CARD_DIAMOND:
		nSuit = 1;
		break;
	case ENEMYTYPE_CARD_CLUB:
		nSuit = 0;
		break;
	case ENEMYTYPE_CARD_SPADE:
		nSuit = 1;
		break;
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//													頂点カラーの更新
	if (mode == MODE_GAME_BONUSSTAGE)
	{//ボーナスステージの場合
		if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE)
		{
			pVtx[(nCntEnemy * 4) + 0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			pVtx[(nCntEnemy * 4) + 1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			pVtx[(nCntEnemy * 4) + 2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			pVtx[(nCntEnemy * 4) + 3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		}
		else
		{//他の場合
			pVtx[(nCntEnemy * 4) + 0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[(nCntEnemy * 4) + 1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[(nCntEnemy * 4) + 2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[(nCntEnemy * 4) + 3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	//==================================================================================================================================================================
	//												敵はプレイヤーが見えるかどうかを判定する処理
	if ((pPlayer->pos.y >= g_aEnemy[nCntEnemy].pos.y - 50.0f && pPlayer->pos.y <= g_aEnemy[nCntEnemy].pos.y) ||
		(pPlayer->pos.y - PLAYER_HEIGHT >= g_aEnemy[nCntEnemy].pos.y - 50.0f && pPlayer->pos.y - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y))
	{
		if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE)
		{
			g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_TRUE;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
			if (g_aEnemy[nCntEnemy].nDirection * (g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x) > 0)
			{
				g_aEnemy[nCntEnemy].nDirection *= -1;
			}
		}
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//												プレイヤーが見えなくなったら、普通の状態に戻す
	if (g_aEnemy[nCntEnemy].pos.x < 25.0f)
	{
		g_aEnemy[nCntEnemy].pos.x = 25.0f;
		g_aEnemy[nCntEnemy].move.x = 0.0f;
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
	}
	else if (g_aEnemy[nCntEnemy].pos.x > 1255.0f)
	{
		g_aEnemy[nCntEnemy].pos.x = 1255.0f;
		g_aEnemy[nCntEnemy].move.x = 0.0f;
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//																アニメション処理
	g_aEnemy[nCntEnemy].nCountAnim++;

	switch (g_aEnemy[nCntEnemy].EncounterState)
	{
		//==================================================================================================================================================================
		//															普通の状態の状態の場合
	case ENEMYSTATE_ENCOUNTER_FALSE:

		if (nSuit == 1 && g_aEnemy[nCntEnemy].nPatternAnim < 4)
		{
			g_aEnemy[nCntEnemy].nPatternAnim = 4;
		}

		g_aEnemy[nCntEnemy].move.y = 0.0f;
		
		if (g_aEnemy[nCntEnemy].nCountAnim >= 45)
		{
			g_aEnemy[nCntEnemy].nCountAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim++;

			if (g_aEnemy[nCntEnemy].nPatternAnim >= 3 + (nSuit * 4))
			{
				g_aEnemy[nCntEnemy].nPatternAnim = 0 + (nSuit * 4);
			}
		}
		//敵の種類によって、敵のテクスチャ座標の更新
		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_DIAMOND)
		{
			UpdateEnemyTex(nCntEnemy, 4, 0.125f, 0.125f);
		}
		else if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_SPADE)
		{
			UpdateEnemyTex(nCntEnemy, 5, 0.125f, 0.125f);
		}
		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															攻撃状態の場合
	case ENEMYSTATE_ENCOUNTER_TRUE:

		switch (g_aEnemy[nCntEnemy].nPatternAnim)
		{
		case 0:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 45)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 1:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 2:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 3:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
			{
				g_aEnemy[nCntEnemy].move.x = 5.0f * g_aEnemy[nCntEnemy].nDirection;
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 4:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				PlaySound(SOUND_LABEL_SE_CARDSWING);
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 5:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 6:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				PlaySound(SOUND_LABEL_SE_CARDSWING);
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 7:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim = 4;

				if (g_aEnemy[nCntEnemy].pos == g_aEnemy[nCntEnemy].LastPos)
				{//ブロックに当たると、普通の状態に戻す
					g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
				}
			}
			break;
			//==================================================================================================================================================================
		}
		//==================================================================================================================================================================
		//															テクスチャ座標の更新
		switch (g_aEnemy[nCntEnemy].nType)
		{
		case ENEMYTYPE_CARD_HEART:
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_DIAMOND:
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_CLUB:
			UpdateEnemyTex(nCntEnemy, 2, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_SPADE:
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.125f);
			break;
		}
		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															攻撃後のアニメーション
	case ENEMYSTATE_ENCOUNTER_LOST:

		if (g_aEnemy[nCntEnemy].nPatternAnim != 7 && g_aEnemy[nCntEnemy].nPatternAnim > 3)
		{
			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 4:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 5:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 6:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;
			}
		}
		else
		{
			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 7:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 2;
				}
				break;
			case 2:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim--;
				}
				break;
			case 1:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim--;
				}
				break;
			case 0:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].move.x = 0.0f;
					g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
				}
				break;

			}
		}
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															テクスチャ座標の更新

		switch (g_aEnemy[nCntEnemy].nType)
		{
		case ENEMYTYPE_CARD_HEART:
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_DIAMOND:
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_CLUB:
			UpdateEnemyTex(nCntEnemy, 2, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_SPADE:
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.125f);
			break;
		}
		break;
		//==================================================================================================================================================================
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//敵のテクスチャ座標の更新
void UpdateEnemyTex(int nCntEnemy, int nSheetLine, float nU, float nV)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	
	if (g_aEnemy[nCntEnemy].nDirection <= 0)
	{//左向きの場合
		//テクスチャ座標の設定
		pVtx[(nCntEnemy * 4) + 0].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 1].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 2].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 3].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
	}
	else if (g_aEnemy[nCntEnemy].nDirection > 0)
	{//右向きの場合
		//テクスチャ座標の設定
		pVtx[(nCntEnemy * 4) + 1].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 0].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 3].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 2].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//プレイヤーが見えるかどうか
void EnemyEncounter(int nCntEnemy, float Height)
{
	Player*pPlayer;					//プレイヤーの情報へのポインタ

	//プレイヤーの情報の取得
	pPlayer = GetPlayer();

	if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - (0.9f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + (0.2f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.y - PLAYER_HEIGHT - 10.0f <= g_aEnemy[nCntEnemy].pos.y &&
		pPlayer->pos.y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight - 25.0f &&
		g_aEnemy[nCntEnemy].nDirection < 0 &&
		g_aEnemy[nCntEnemy].EncounterState != ENEMYSTATE_ENCOUNTER_TRUE ||
		pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + (0.9f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - (0.2f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.y - PLAYER_HEIGHT - 10.0f <= g_aEnemy[nCntEnemy].pos.y &&
		pPlayer->pos.y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight - 25.0f &&
		g_aEnemy[nCntEnemy].nDirection >= 0 &&
		g_aEnemy[nCntEnemy].EncounterState != ENEMYSTATE_ENCOUNTER_TRUE)
	{//プレイヤーが見えるかどうか判定する
		if (g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT &&
			g_aEnemy[nCntEnemy].nDirection > 0 &&
			pPlayer->pos.x < g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0 ||
			g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT &&
			g_aEnemy[nCntEnemy].nDirection < 0 &&
			pPlayer->pos.x > g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0)
		{//カウンターが０でなかったら、アニメーションが終わったら、プレイヤーを追いかける
			g_aEnemy[nCntEnemy].nDirection *= -1;
			g_aEnemy[nCntEnemy].move.x *= -1;
		}

		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_TRUE;				//プレイヤーを見た状態にする
		g_aEnemy[nCntEnemy].nChaseCounter = 180;									//追いかけるカウンターの設定

		//コウモリスライムの場合
		if (g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT)
		{
			g_aEnemy[nCntEnemy].nCountAnim = 0;											//アニメーションカウンターの設定
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
		}
	}

	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nDirection > 0 &&
		pPlayer->pos.x < g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0 &&
		g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT ||
		g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nDirection < 0 &&
		pPlayer->pos.x > g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0 &&
		g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT)
	{
		g_aEnemy[nCntEnemy].nDirection *= -1;
		g_aEnemy[nCntEnemy].move.x *= -1;
	}
}

//敵の情報の取得
Enemy*GetEnemy(void)
{
	return &g_aEnemy[0];
}

//敵を出す処理
void SpawnEnemy(void)
{
	MODE mode;					//モード

	mode = GetMode();			//モードの取得

	if (mode == MODE_GAME_FIRSTSTAGE_1)
	{//ステージ　1
		SetEnemy(D3DXVECTOR3(100.0f, 120.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.5f, 0.0f), ENEMYTYPE_BLUESLIME);
		SetEnemy(D3DXVECTOR3(400.0f, 125.0f, 0.0f), D3DXVECTOR3(1.0f, 0.5f, 0.0f), ENEMYTYPE_GREENSLIME);
		SetEnemy(D3DXVECTOR3(300.0f, 325.0f, 0.0f), D3DXVECTOR3(1.0f, 0.5f, 0.0f), ENEMYTYPE_GREENSLIME);
		SetEnemy(D3DXVECTOR3(850.0f, 325.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.5f, 0.0f), ENEMYTYPE_BLUESLIME);
		SetEnemy(D3DXVECTOR3(1000.0f, 555.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), ENEMYTYPE_SLIMEBAT);
		/*SetEnemy(D3DXVECTOR3(50.0f, 507.5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);
		SetEnemy(D3DXVECTOR3(500.0f, 167.5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);*/
	}
	else if (mode == MODE_GAME_FIRSTSTAGE_2)
	{//ステージ　2
		SetEnemy(D3DXVECTOR3(50.0f, 445.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);
		SetEnemy(D3DXVECTOR3(400.0f, 250.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), ENEMYTYPE_SLIMEBAT);
		SetEnemy(D3DXVECTOR3(850.0f, 260.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), ENEMYTYPE_SLIMEBAT);
		SetEnemy(D3DXVECTOR3(750.0f, 595.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMYTYPE_BLUESLIME);
		SetEnemy(D3DXVECTOR3(950.0f, 595.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), ENEMYTYPE_GREENSLIME);
		SetEnemy(D3DXVECTOR3(320.0f, 295.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), ENEMYTYPE_GREENSLIME);

	}
	else if (mode == MODE_GAME_FIRSTSTAGE_BOSS)
	{//ボス　1
		SetBoss(D3DXVECTOR3(640, 700.0f, 0.0f), 1);
	}
	else if (mode == MODE_GAME_BONUSSTAGE)
	{//ボーナスステージ
		SetEnemy(D3DXVECTOR3(50.0f, 507.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);
		SetEnemy(D3DXVECTOR3(30.0f, 125.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_HEART);
		SetEnemy(D3DXVECTOR3(1250.0f, 125.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_CLUB);
		SetEnemy(D3DXVECTOR3(30.0f, 290.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_SPADE);
		SetEnemy(D3DXVECTOR3(1250.0f, 480.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_DIAMOND);

	}
	else if (mode == MODE_GAME_SECONDSTAGE_BOSS)
	{//ボーナ　2
		SetBoss(D3DXVECTOR3(640.0f, 670.0f, 0.0f), 2);
	}
}