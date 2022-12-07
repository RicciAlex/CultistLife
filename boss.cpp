//==========================================//
//                                          //
//             ボスのファイル               //
//　　　　　　 Author: Ricci Alex           //
//                                          //
//==========================================//

//インクルードファイル
#include "boss.h"
#include <time.h>

//グローバル変数を宣言
LPDIRECT3DTEXTURE9 g_apTextureBoss;						//ボスのテクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureSnakeSlime;				//スライムボスのテクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_apTextureTarotMaster;				//タロットボスへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;			//頂点バッファへのポインタ
Boss g_Boss;											//ボス型の配列を宣言する

//ボスの初期化処理
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの情報へのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	pDevice = GetDevice();			//デバイスの情報の取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SlimeBlue_SpriteSheet2.png",
		&g_apTextureBoss);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\GigantSnakeSlimeSprite.png",
		&g_apTextureSnakeSlime);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TarotMaster_Sprite.png",
		&g_apTextureTarotMaster);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//ボス型の変数の各パラメータの初期化
	g_Boss.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//現在の位置
	g_Boss.LastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//前回の位置
	g_Boss.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量
	g_Boss.MoveState = MOVESTATE_FALLING;						//移動状態
	g_Boss.BossState = BOSS_STATE_APPEAR;						//ボスの状態
	g_Boss.fHeight = 50.0f;										//高さ
	g_Boss.nCountAnim = 0;										//アニメーションカウンター
	g_Boss.nPatternAnim = 0;									//アニメーションパターン
	g_Boss.nChaseCounter = 0;									//追いかけるカウンター
	g_Boss.bDamage = false;										//向き
	g_Boss.nCounterShoot = 0;									//ボスの弾発射のカウンター
	g_Boss.nCounterState = 0;									//ボスの状態カウンター
	g_Boss.nLife = 3;											//体力
	g_Boss.nType = 0;											//種類
	g_Boss.bUse = false;										//使用されているかどうか

	//頂点設定
	pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();
}

//ボスの終了処理
void UninitBoss(void)
{
	//テクスチャの破棄
	if (g_apTextureBoss != NULL)
	{
		g_apTextureBoss->Release();
		g_apTextureBoss = NULL;
	}
	if (g_apTextureSnakeSlime != NULL)
	{			   
		g_apTextureSnakeSlime->Release();
		g_apTextureSnakeSlime = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//ボスの更新処理
void UpdateBoss(void)
{
	if (g_Boss.bUse == true)
	{//使用されている場合

		if (g_Boss.nType == 1)
		{//スライムボスの場合
			UpdateSlimeSnake();
		}
		else if (g_Boss.nType == 2)
		{//タロットボスの場合
			UpdateTarotMaster();
		}
	}
}

//ボスの描画処理
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスの情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Boss.bUse == true)
	{
		if (g_Boss.nType == 0)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBoss);
		}
		else if (g_Boss.nType == 1)
		{//スライムボスの場合
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureSnakeSlime);
		}
		else if (g_Boss.nType == 2)
		{//タロットボスの場合
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureTarotMaster);
		}

		//四角形を描画する
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//ボスの設定
void SetBoss(D3DXVECTOR3 pos, int type)
{

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Boss.bUse == false)
	{
		g_Boss.pos = pos;			//現在の位置の設定
		g_Boss.LastPos = pos;		//前回の位置の位置
		g_Boss.nType = type;		//種類の設定
		g_Boss.bUse = true;			//使用されている状態にする

		if (type == 0)
		{
			//頂点設定
			pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y - 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y, 0.0f);

			//テクスチャ座標の設定
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.125f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
			pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);
		}
		else if (type == 1)
		{//スライムボスの場合
			g_Boss.nCountAnim = 30;

			//頂点設定
			pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y + 400.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y + 400.0f, 0.0f);

			//テクスチャ座標の設定
			pVtx[3].tex = D3DXVECTOR2(0.5, 0.25);
			pVtx[1].tex = D3DXVECTOR2(0.5, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		}
		else if (type == 2)
		{//タロットボスの場合
			g_Boss.BossState = BOSS_STATE_SLEEP;				//ボスの状態

			g_Boss.nLife = 5;									//ボスの体力

			//頂点設定
			pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y - 100, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y - 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 50.0f, g_Boss.pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 50.0f, g_Boss.pos.y, 0.0f);

			//テクスチャ座標の設定
			pVtx[3].tex = D3DXVECTOR2(0.125, 0.125);
			pVtx[1].tex = D3DXVECTOR2(0.125, 0.0);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();
}

//スライムボスの更新処理
void UpdateSlimeSnake(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	Player*pPlayer;		//プレイヤーの情報へのポインタ
	bool bEnd = false;	
	int*pSwitch;		//スイッチ情報へのポインタ

	pSwitch = GetActiveSwitch();	//スイッチ情報の取得
	pPlayer = GetPlayer();			//プレイヤーの情報の取得

	int nInteraction = 0;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Boss.BossState == BOSS_STATE_APPEAR)
	{//発生する場合

		//アニメーション処理
		if (g_Boss.nCountAnim > 0)
		{
			g_Boss.nCountAnim--;
		}
		if (g_Boss.nCountAnim <= 0)
		{
			g_Boss.move.y = -1.0f;
		}

		if (g_Boss.pos.y <= 500.0f)
		{
			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_Boss.nCountAnim = 0;								//アニメーションカウンターを０にする
			g_Boss.move.y = 0.0f;								//Y座標の移動量を０にする
			g_Boss.BossState = BOSS_STATE_NORMAL;				//普通状態にする
			PlaySound(SOUND_LABEL_BGMBOSS);						//ボスBGMを再生する
		}

		//テクスチャ座標の設定
		pVtx[3].tex = D3DXVECTOR2(0.5, 0.25);
		pVtx[1].tex = D3DXVECTOR2(0.5, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	}
	if (g_Boss.BossState == BOSS_STATE_NORMAL)
	{//普通の状態の場合
		//アニメション処理
		g_Boss.nCountAnim++;

		if (g_Boss.nCounterShoot > 0)
		{//弾の発生カウンター
			g_Boss.nCounterShoot--;
		}

		if (*pSwitch == 4)
		{
			//敵の設定
			SetMinion(D3DXVECTOR3(0.0f, 370.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 0);
			SetMinion(D3DXVECTOR3(1280.0f, 370.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 0);
			*pSwitch = 0;
		}

		if (g_Boss.nCounterShoot <= 0 && pPlayer->pos.y <= 250.0f)
		{//プレイヤーが直接に攻撃できる範囲以外だったら、弾発生
			PlaySound(SOUND_LABEL_SE_NORMALBULLET);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y + 5.0f, 0.0f), D3DXVECTOR3(0.0f, -8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.08f, 0.0f), 0);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y + 5.0f, 0.0f), D3DXVECTOR3(2.07f, -8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.08f, 0.0f), 0);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x, g_Boss.pos.y + 5.0f, 0.0f), D3DXVECTOR3(-2.07f, -8.0f, 0.0f), D3DXVECTOR3(0.0f, 0.08f, 0.0f), 0);

			g_Boss.nCounterShoot = 120;						//弾の発生カウンターの設定
		}

		//=====================================================================================================================================================
		//													アニメション処理
		if (g_Boss.nCountAnim % 30 == 29)
		{
			g_Boss.nPatternAnim++;

			if (g_Boss.nPatternAnim == 4)
			{
				g_Boss.nPatternAnim = 0;
			}

			if (g_Boss.nPatternAnim == 0 || g_Boss.nPatternAnim == 2)
			{
				g_Boss.move.y = -0.25f;
			}
			else if (g_Boss.nPatternAnim == 1 || g_Boss.nPatternAnim == 3)
			{
				g_Boss.move.y = 0.25f;
			}

			if (g_Boss.pos.x + 75.0f <= pPlayer->pos.x)
			{
				g_Boss.move.x = 1.0f;
			}
			else if (g_Boss.pos.x - 75.0f >= pPlayer->pos.x)
			{
				g_Boss.move.x = -1.0f;
			}
			//=====================================================================================================================================================
			//=====================================================================================================================================================
			//									プレイヤーは攻撃できる範囲で、ボスの上にいる場合、攻撃状態にする
			if (g_Boss.pos.x + 75.0f >= pPlayer->pos.x && g_Boss.pos.x - 75.0f <= pPlayer->pos.x)
			{
				if (pPlayer->pos.y >= 250.0f)
				{
					g_Boss.BossState = BOSS_STATE_ATTACK;				//攻撃状態にする
					g_Boss.nChaseCounter = 100.0f;						//追いかけるカウンターの設定
					g_Boss.nCountAnim = 0;								//アニメーションカウンターの設定
					g_Boss.nPatternAnim = 0;							//アニメーションパターンの設定
					g_Boss.move.x = 0.0f;								//移動量を０にする
					g_Boss.move.y = 0.0f;								//移動量を０にする
				}

			}
		}

		//テクスチャ座標の設定
		pVtx[3].tex = D3DXVECTOR2(0.5, 0.25 + (0.25f * g_Boss.nPatternAnim));
		pVtx[1].tex = D3DXVECTOR2(0.5, 0.0 + (0.25f * g_Boss.nPatternAnim));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25 + (0.25f * g_Boss.nPatternAnim));
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (0.25f * g_Boss.nPatternAnim));
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																				攻撃状態の場合
	else if (g_Boss.BossState == BOSS_STATE_ATTACK)
	{
		g_Boss.nChaseCounter--;

		if (g_Boss.nChaseCounter >= 70)
		{//上に移動
			g_Boss.move.y = -8.0f;
		}
		else if (g_Boss.nChaseCounter >= 30 && g_Boss.nChaseCounter < 70)
		{//動かない
			g_Boss.move.y = 0.0f;
		}
		else if (g_Boss.nChaseCounter < 30 && g_Boss.nChaseCounter >= 0)
		{//下に戻る
			g_Boss.move.y = 8.0f;
		}
		else if (g_Boss.nChaseCounter < 0)
		{//普通状態に戻す
			g_Boss.move.y = 0.0f;								//移動量を０にする
			g_Boss.move.x = 0.0f;								//移動量を０にする
			g_Boss.pos.y = 500.0f;								//Y座標の位置の設定
			g_Boss.nChaseCounter = 0;							//攻撃カウンターを０にする
			g_Boss.BossState = BOSS_STATE_NORMAL;				//普通状態にする

			if (g_Boss.bDamage == true)
			{//爆発する敵に当たった場合
				g_Boss.nCounterState = 10;						//状態カウンターの設定
				g_Boss.BossState = BOSS_STATE_DAMAGE;			//ダメージ状態にする
			}
		}

		//===========================================================================================================================================================================================
		//																					プレイヤーに当たった場合
		if (pPlayer->pos.y > g_Boss.pos.y && pPlayer->pos.x >= g_Boss.pos.x - 100.0f && pPlayer->pos.x <= g_Boss.pos.x + 100.0f && pPlayer->state != PLAYERSTATE_DAMAGE &&pPlayer->state != PLAYERSTATE_DEATH)
		{
			pPlayer->state = PLAYERSTATE_DAMAGE;					//プレイヤーをダメージ状態にする
			pPlayer->nCounterState = 180;							//状態カウンターの設定
			AddScore(-500);											//スコアを下がる
			PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);					//ダメージサウンドを再生する
			SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS500);
		}

		//テクスチャ座標の設定
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.25f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	}
	//===========================================================================================================================================================================================
	//																						ダメージ状態の場合
	else if (g_Boss.BossState == BOSS_STATE_DAMAGE)
	{
		g_Boss.nCounterState--;										//色アニメーションカウンターの更新

		if (g_Boss.nCounterState == 1)
		{
			PlaySound(SOUND_LABEL_SE_EXPLOSION);					//爆発サウンドを再生
		}
		else if (g_Boss.nCounterState <= 0)
		{//アニメーション処理
			g_Boss.nCountAnim++;

			if (g_Boss.nCountAnim % 8 == 7)
			{
				//頂点カラーの更新
				if (g_Boss.nPatternAnim == 0)
				{
					g_Boss.nPatternAnim = 1;

					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{
					g_Boss.nPatternAnim = 0;

					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
				if (g_Boss.nCountAnim >= 120)
				{//ダメージを与えて、体力の判定
					g_Boss.nLife--;						//体力を下がる
					g_Boss.nPatternAnim = 0;			//アニメーションパターンを０にする
					g_Boss.nCountAnim = 0;				//アニメーションカウンターを０にする
					g_Boss.bDamage = false;				

					if (g_Boss.nLife <= 0)
					{//体力が0になった場合
						g_Boss.BossState = BOSS_STATE_DEATH;		//死んだ状態にする
						g_Boss.nCounterState = 150;					//アニメーションカウンターの設定
					}
					else
					{//体力は０でない場合
						g_Boss.BossState = BOSS_STATE_NORMAL;		//普通状態に戻す
					}
					//頂点カラーの更新
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
			//テクスチャ座標の設定
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0 + (0.25f * g_Boss.nPatternAnim));
			pVtx[2].tex = D3DXVECTOR2(0.5f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f + (0.25f * g_Boss.nPatternAnim));
		}
		else
		{
			//テクスチャ座標の設定
			pVtx[3].tex = D3DXVECTOR2(0.5f, 0.25f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.25f);
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																							死んだら
	else if (g_Boss.BossState == BOSS_STATE_DEATH)
	{
		g_Boss.nCounterState--;								//ステータスカウンターの更新
		g_Boss.move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//移動量の更新

		//アニメーション処理
		g_Boss.nCountAnim++;

		if (g_Boss.nCountAnim % 8 == 7)
		{
			if (g_Boss.nPatternAnim == 0)
			{
				g_Boss.nPatternAnim = 1;

				//頂点カラーの更新
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				g_Boss.nPatternAnim = 0;

				//頂点カラーの更新
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//テクスチャ座標の設定
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0 + (0.25f * g_Boss.nPatternAnim));
			pVtx[2].tex = D3DXVECTOR2(0.5f, 0.25 + (0.25f * g_Boss.nPatternAnim));
			pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f + (0.25f * g_Boss.nPatternAnim));
		}
		if (g_Boss.nCounterState <= 0)
		{
			g_Boss.nCountAnim = 0;
			g_Boss.nPatternAnim = 0;
			g_Boss.nCounterState = 0;

			//頂点カラーの更新
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			bEnd = true;
			AddScore(10000);
			g_Boss.bUse = false;					//使用されていない状態にする
		}
	}

	//ボスの位置の更新
	g_Boss.pos += g_Boss.move;


	//頂点設定
	pVtx[1].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y, 0.0f);
	pVtx[0].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Boss.pos.x + 150.0f, g_Boss.pos.y + 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Boss.pos.x - 150.0f, g_Boss.pos.y + 400.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();

	if (bEnd == true)
	{//ボスが死んだら、プレイヤーを勝った状態にする
		pPlayer->state = PLAYERSTATE_WIN;
	}
}

//タロットボスの更新処理
void UpdateTarotMaster(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	Player*pPlayer;		//プレス情報へのポインタ
	bool bEnd = false;	
	int*pSwitch;		//スイッチ情報へのポインタ
	Minion*pMinion;		//敵情報へのポインタ

	pMinion = GetMinion();			//敵の情報を取得
	pPlayer = GetPlayer();			//プレイヤーの情報の取得
	pSwitch = GetActiveSwitch();	//スイッチ情報の取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//===========================================================================================================================================================================================
	//																						寝ている状態の場合
	if (g_Boss.BossState == BOSS_STATE_SLEEP)
	{
		if (/*pPlayer->pos.x > 500.0f && pPlayer->pos.x < 780.0f && pPlayer->pos.y > 530.0f*/
			(pPlayer->pos.x - g_Boss.pos.x) * (pPlayer->pos.x - g_Boss.pos.x) + (pPlayer->pos.y - g_Boss.pos.y) * (pPlayer->pos.y - g_Boss.pos.y) < 160000)
		{
			g_Boss.BossState = BOSS_STATE_APPEAR;						//発生状態にする
			g_Boss.nPatternAnim++;										//アニメーションパターンの更新
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																						発生状態の場合
	if (g_Boss.BossState == BOSS_STATE_APPEAR)
	{
		//アニメーション処理
		g_Boss.nCountAnim++;

		switch (g_Boss.nPatternAnim)
		{
		case 1:
			if (g_Boss.nCountAnim % 15 == 14)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
				PlaySound(SOUND_LABEL_BGMBOSS);						//ボスサウンドを再生する
			}
			break;

		case 2:
			if (g_Boss.nCountAnim % 60 == 59)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
			}
			break;

		case 3:
			if (g_Boss.nCountAnim % 10 == 9)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
			}
			break;

		case 4:
			if (g_Boss.nCountAnim % 60 == 59)
			{
				g_Boss.nPatternAnim++;
				g_Boss.nCountAnim = 0;
			}
			break;

		case 5:
			if (g_Boss.nCountAnim % 30 == 29)
			{//アニメーションが終わったら
				g_Boss.BossState = BOSS_STATE_ATTACK;					//攻撃状態にする
				g_Boss.nPatternAnim = 0;								//アニメーションパターンを０にする
				g_Boss.nCountAnim = 0;									//アニメーションカウンターを０にする
				*pSwitch = 0;											//スイッチが使われていない状態にする
			}
			break;
		}
		//テクスチャ座標の更新
		if (g_Boss.BossState == BOSS_STATE_APPEAR)
		{
			UpdateBossTex(0, 0.125f, 0.125f);
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																				攻撃状態の場合
	else if (g_Boss.BossState == BOSS_STATE_ATTACK)
	{//攻撃状態の場合

		//アニメション処理
		g_Boss.nCountAnim++;

		if (g_Boss.nCountAnim % 30 == 29)
		{
			if (g_Boss.nLife == 5 && g_Boss.nPatternAnim < 4 || g_Boss.nLife < 5 && g_Boss.nPatternAnim < 6)
			{
				g_Boss.nPatternAnim++;

				if (g_Boss.nPatternAnim == 5)
				{
					*pSwitch = 0;
				}

				if (g_Boss.nLife == 5 && g_Boss.nPatternAnim == 4 || g_Boss.nLife < 5 && g_Boss.nPatternAnim == 6)
				{
					switch (g_Boss.nLife)
					{
					case 5:
						SetMinion(D3DXVECTOR3(810.0f, 0.0f, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 1);							//戦車
						break;
					case 4:
						SetMinion(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3);								//死神
						break;
					case 3:
						SetMinion(D3DXVECTOR3(600.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 2);							//吊された男
						break;
					case 2:
						SetMinion(D3DXVECTOR3(200.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);						//太陽
						break;
					case 1:
						SetMinion(D3DXVECTOR3(640.0f, SCREEN_HEIGHT + 180.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 4);		//悪魔
						break;
					}
				}
			}
			g_Boss.nCountAnim = 0;
		}
		//テクスチャ座標の更新
		switch (g_Boss.nLife)
		{
		case 5:
			UpdateBossTex(1, 0.125f, 0.125f);
			break;
		case 4:
			UpdateBossTex(2, 0.125f, 0.125f);
			break;
		case 3:
			UpdateBossTex(3, 0.125f, 0.125f);
			break;
		case 2:
			UpdateBossTex(4, 0.125f, 0.125f);
			break;
		case 1:
			UpdateBossTex(5, 0.125f, 0.125f);
			break;
		}
		//===========================================================================================================================================================================================
		//																						スイッチ全部使ったら										
		if (*pSwitch == 8)
		{
			g_Boss.BossState = BOSS_STATE_DAMAGE;				//ダメージ状態にする
			g_Boss.nCounterState = 120;							//状態カウンターの設定
			g_Boss.nPatternAnim = 7;							//アニメーションパターンの設定

			//頂点カラーの更新
			pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
		}
	}
	//===========================================================================================================================================================================================
	//																							ダメージ状態の場合
	else if (g_Boss.BossState == BOSS_STATE_DAMAGE)
	{
		g_Boss.nCounterState--;

		if (g_Boss.nCounterState % 10 == 0)
		{
			PlaySound(SOUND_LABEL_SE_FIRE);						//炎のサウンドを再生

			//弾の設定
			SetBullet(D3DXVECTOR3(g_Boss.pos.x + 25.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x - 35.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
			SetBullet(D3DXVECTOR3(g_Boss.pos.x - 5.0f, 700.0f, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5);
		}

		if (g_Boss.nCounterState % 8 == 7)
		{
			//頂点カラーの更新
			if (g_Boss.nPatternAnim == 7)
			{//普通
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				g_Boss.nPatternAnim = 5;
			}
			else
			{//赤い
				pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f);

				g_Boss.nPatternAnim = 7;
			}
			//テクスチャ座標の更新
			if (g_Boss.nPatternAnim == 5)
			{
				UpdateBossTex(1, 0.125f, 0.125f);
			}
			else
			{
				UpdateBossTex(2, 0.125f, 0.125f);
			}
		}

		if (g_Boss.nCounterState <= 0)
		{//状態カウンターが0になったら、体力判定する
			g_Boss.nCounterState = 0;

			if (g_Boss.nLife > 1)
			{//体力が０でない場合
				g_Boss.nLife--;									//体力の更新
				g_Boss.nCountAnim = 0;							//アニメーションカウンターを０にする
				g_Boss.nPatternAnim = 0;						//アニメーションパターンを０にする
				g_Boss.BossState = BOSS_STATE_ATTACK;			//攻撃状態にする
				*pSwitch = 0;									//スイッチが使われていない状態にする

				//頂点カラーを普通のカラーに戻す
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{//体力が０になった場合
				g_Boss.BossState = BOSS_STATE_DEATH;			//死んだ状態にする
				g_Boss.nCountAnim = 0;							//アニメーションカウンターを０にする
				g_Boss.nPatternAnim = 0;						//アニメーションカウンターを０にする
				g_Boss.nCounterState = 300;						//状態カウンターの設定
				*pSwitch = 0;									//スイッチが使われていない状態にする

				//頂点カラーを普通のカラーに戻す
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}
	//===========================================================================================================================================================================================
	//===========================================================================================================================================================================================
	//																											死んだら
	else if (g_Boss.BossState == BOSS_STATE_DEATH)
	{
		//アニメション処理
		g_Boss.nCountAnim++;
		g_Boss.nCounterState--;

		if (g_Boss.nCountAnim % 8 == 7)
		{
			g_Boss.nPatternAnim++;

			if (g_Boss.nPatternAnim >= 4)
			{
				g_Boss.nPatternAnim = 0;
			}
		}
		if (g_Boss.nCounterState == 10)
		{
			AddScore(15000);							//スコアの更新
		}

		//頂点カラーの更新
		if (g_Boss.nPatternAnim % 2 == 0)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f * (g_Boss.nCounterState * 0.0033f));
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * (g_Boss.nCounterState * 0.0033f));
		}
		//テクスチャ座標の更新
		UpdateBossTex(6, 0.125f, 0.125f);
	}

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_O) == true)
	{
		g_Boss.nLife--;

		g_Boss.nPatternAnim = 0;
		g_Boss.nCountAnim = 0;
	}

#endif // _DEBUG

	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();

	if (g_Boss.BossState == BOSS_STATE_DEATH && g_Boss.nCounterState <= 0)
	{//死んだら、プレイヤーを勝った状態にする
		g_Boss.bUse = false;												//ボスが使われていない状態にする
		pPlayer->state = PLAYERSTATE_WIN;									//プレイヤーを勝った状態にする
	}
}

//ボステクスチャ座標の更新処理
void UpdateBossTex(int nSheetLine, float nU, float nV)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	 //テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(nU + (g_Boss.nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[1].tex = D3DXVECTOR2(0.0f + (g_Boss.nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[2].tex = D3DXVECTOR2(nU + (g_Boss.nPatternAnim * nU), nV + (nV * nSheetLine));
		pVtx[3].tex = D3DXVECTOR2(0.0f + (g_Boss.nPatternAnim * nU), nV + (nV * nSheetLine));

	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();
}

//ボスの情報を取得
Boss*GetBoss(void)
{
	return &g_Boss;
}