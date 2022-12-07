//===================================================//
//                                                   //
//     　	 アクションゲーム弾のファイル	         //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "bullet.h"
#include "sound.h"

//マクロ定義
#define MAX_BULLET		(128)							//弾の最大数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBulletBoss = NULL;				//テクスチャへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureSlashBoss = NULL;
LPDIRECT3DTEXTURE9 g_pTextureDevil = NULL;
LPDIRECT3DTEXTURE9 g_pTextureSun = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];							//Bullet型の配列を宣言する

//弾の初期化処理
void InitBullet(void)
{
	int nCntBullet;					//数をカウントする変数を宣言する
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bulletBlue001.png",
		&g_pTextureBulletBoss);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Slash.png",
		&g_pTextureSlashBoss);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\DevilBullet.png",
		&g_pTextureDevil);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SunBullet.png",
		&g_pTextureSun);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		g_aBullet[nCntBullet].LastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
		g_aBullet[nCntBullet].Accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//加速
		g_aBullet[nCntBullet].nLife = 120;									
		g_aBullet[nCntBullet].nType = 0;									//種類
		g_aBullet[nCntBullet].nCntDelay = 0;								
		g_aBullet[nCntBullet].nCounterAnim = 0;								//アニメーションカウンター
		g_aBullet[nCntBullet].nPatternAnim = 0;								//弾のアニメーションパターン
		g_aBullet[nCntBullet].bUse = false;									//使用しているかどうか

		//弾座標の設定
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);

		//rthの設定
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}


//弾の終了処理
void UninitBullet(void)
{
	//テクスチャのポインタの破棄
	if (g_pTextureBulletBoss != NULL)
	{
		g_pTextureBulletBoss->Release();
		g_pTextureBulletBoss = NULL;
	}
	if (g_pTextureSlashBoss != NULL)
	{			  
		g_pTextureSlashBoss->Release();
		g_pTextureSlashBoss = NULL;
	}
	if (g_pTextureDevil != NULL)
	{			  
		g_pTextureDevil->Release();
		g_pTextureDevil = NULL;
	}
	if (g_pTextureSun != NULL)
	{			  
		g_pTextureSun->Release();
		g_pTextureSun = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//弾の更新処理
void UpdateBullet(void)
{
	int nCntBullet;		//弾をカウントする変数を宣言
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	int nInteraction;	
	Player*pPlayer;

	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//位置と移動量の更新
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;
			if (g_aBullet[nCntBullet].nType != 2)
			{
				g_aBullet[nCntBullet].move += g_aBullet[nCntBullet].Accel;
			}
			else
			{
				if (g_aBullet[nCntBullet].move.x * g_aBullet[nCntBullet].Accel.x < 0)
				{
					g_aBullet[nCntBullet].move += g_aBullet[nCntBullet].Accel;
				}
				else
				{
					g_aBullet[nCntBullet].nLife -= 2;
					g_aBullet[nCntBullet].move.x = 0.0f;
				}
			}

			g_aBullet[nCntBullet].nLife--;	
			
			if (g_aBullet[nCntBullet].nType == 0)
			{
				//ブロックの当たり判定
				nInteraction = BlockInteractionBullet(&g_aBullet[nCntBullet].pos, &g_aBullet[nCntBullet].LastPos, &g_aBullet[nCntBullet].move, 10.0f, 20.0f);

				if (nInteraction == 1)
				{//ブロックの上に当たったら
					g_aBullet[nCntBullet].bUse = false;
				}

			}
			else if (g_aBullet[nCntBullet].nType == 1)
			{
				if ((pPlayer->pos.y - g_aBullet[nCntBullet].pos.y) * g_aBullet[nCntBullet].Accel.y < 0)
				{
					g_aBullet[nCntBullet].move.y *= 0.5f;
					g_aBullet[nCntBullet].Accel.y *= -1;
				}
			}

			if (g_aBullet[nCntBullet].pos.y < pPlayer->pos.y && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_HEIGHT && 
				g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - (PLAYER_WIDTH * 0.5) && g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + (PLAYER_WIDTH * 0.5) &&
				pPlayer->state != PLAYERSTATE_DAMAGE && pPlayer->state != PLAYERSTATE_DEATH)
			{//プレイヤーに当たったら、ダメージ状態にする
				g_aBullet[nCntBullet].bUse = false;
				pPlayer->state = PLAYERSTATE_DAMAGE;
				pPlayer->nCounterState = 180;
				AddScore(-250);
				SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS250);

				if (g_aBullet[nCntBullet].nType == 4 || g_aBullet[nCntBullet].nType == 5)
				{//火の音
					PlaySound(SOUND_LABEL_SE_FIRE);
				}
				else if (g_aBullet[nCntBullet].nType == 2)
				{//切りつけの音
					PlaySound(SOUND_LABEL_SE_SLASH);
				}
				else
				{//普通攻撃の音
					PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);
				}
			}

			if (g_aBullet[nCntBullet].nType == 2)
			{
				//各頂点の位置の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 30.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 30.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 30.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 30.0f, g_aBullet[nCntBullet].pos.z);
			}
			else if (g_aBullet[nCntBullet].nType == 3)
			{
				g_aBullet[nCntBullet].nCounterAnim++;

				if (g_aBullet[nCntBullet].nCounterAnim % 15 == 14)
				{
					g_aBullet[nCntBullet].nPatternAnim ^= 1;
				}

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y - 15.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y - 15.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y + 15.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y + 15.0f, g_aBullet[nCntBullet].pos.z);

				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBullet[nCntBullet].nPatternAnim), 0.0f);
			}
			else if (g_aBullet[nCntBullet].nType == 4)
			{
				if (g_aBullet[nCntBullet].move.x > 0)
				{
					if (g_aBullet[nCntBullet].pos.x > 640.0f)
					{
						g_aBullet[nCntBullet].bUse = false;
					}

					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
				}
				else
				{
					if (g_aBullet[nCntBullet].pos.x < 640.0f)
					{
						g_aBullet[nCntBullet].bUse = false;
					}

					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y - 15.0f, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 30.0f, g_aBullet[nCntBullet].pos.y + 15.0f, 0.0f);
				}
			}
			else if (g_aBullet[nCntBullet].nType == 5)
			{
				if (g_aBullet[nCntBullet].pos.y < 500.0f)
				{
					g_aBullet[nCntBullet].bUse = false;
				}

				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y - 30.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 15.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 15.0f, g_aBullet[nCntBullet].pos.y + 30.0f, 0.0f);
			}
			else
			{
				//各頂点の位置の設定
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, g_aBullet[nCntBullet].pos.z);
			}
			

			//前回の位置の更新
			g_aBullet[nCntBullet].LastPos = g_aBullet[nCntBullet].pos;

			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				if (g_aBullet[nCntBullet].nCounterAnim != 0)
				{
					g_aBullet[nCntBullet].nCounterAnim = 0;
					g_aBullet[nCntBullet].nPatternAnim = 0;
				}

				g_aBullet[nCntBullet].bUse = false;					//使用されていない状態にする
			}
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//弾の描画処理
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;						//カウントする変数を宣言する

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//テクスチャの設定
			if (g_aBullet[nCntBullet].nType == 2)
			{
				pDevice->SetTexture(0, g_pTextureSlashBoss);
			}
			else if (g_aBullet[nCntBullet].nType == 3)
			{
				pDevice->SetTexture(0, g_pTextureDevil);
			}
			else if (g_aBullet[nCntBullet].nType == 4 || g_aBullet[nCntBullet].nType == 5)
			{
				pDevice->SetTexture(0, g_pTextureSun);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureBulletBoss);
			}

			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}

	}
}

//弾の設定処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 acc, int type)
{
	int nCntBullet;		//カウントする変数を宣言する

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない場合

		 //弾の位置の設定
			g_aBullet[nCntBullet].pos = pos;

			g_aBullet[nCntBullet].LastPos = pos;			//前回の位置の設定

			//各頂点の位置の設定
			pVtx[0].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y - 10.0f, pos.z);
			pVtx[1].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y - 10.0f, pos.z);
			pVtx[2].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y + 10.0f, pos.z);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y + 10.0f, pos.z);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);


			//弾の移動量の設定
			g_aBullet[nCntBullet].move = move;

			//弾の加速
			g_aBullet[nCntBullet].Accel = acc;
			//弾の種類
			g_aBullet[nCntBullet].nType = type;
			//弾の体力の設定
			g_aBullet[nCntBullet].nLife = 200;

			g_aBullet[nCntBullet].nCntDelay = 0;

			//弾が使用されている状態にする
			g_aBullet[nCntBullet].bUse = true;

			switch (g_aBullet[nCntBullet].nType)
			{
			case 0:

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.5f, 0.2f, 1.0f);
				break;

			case 1:

				//頂点カラーの設定
				pVtx[0].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);
				pVtx[1].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);
				pVtx[2].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);
				pVtx[3].col = D3DXCOLOR(0.38f, 0.05f, 0.2f, 0.75f);

				break;

			case 2:

				pVtx[0].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y - 30.0f, pos.z);
				pVtx[1].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y - 30.0f, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y + 30.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y + 30.0f, pos.z);

				if (move.x > 0)
				{
					//テクスチャ座標の設定
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				}
				else
				{
					//テクスチャ座標の設定
					pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
					pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				}

				//頂点カラーの設定
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				break;

			case 3:

				pVtx[0].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y - 15.0f, pos.z);
				pVtx[1].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y - 15.0f, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y + 15.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y + 15.0f, pos.z);

				//頂点カラーの設定
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

				break;

			case 4:

				if (move > 0)
				{
					pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 15.0f, pos.z);
					pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 15.0f, pos.z);
					pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 15.0f, pos.z);
					pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 15.0f, pos.z);
				}
				else
				{
					pVtx[1].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 15.0f, pos.z);
					pVtx[0].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 15.0f, pos.z);
					pVtx[3].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y + 15.0f, pos.z);
					pVtx[2].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y + 15.0f, pos.z);
				}
				

				//頂点カラーの設定
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

				break;

			case 5:

				pVtx[0].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y - 30.0f, pos.z);
				pVtx[1].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y - 30.0f, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 15.0f, pos.y + 30.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 15.0f, pos.y + 30.0f, pos.z);

				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);

				pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

				break;
			}

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}