//===================================================//
//                                                   //
//     　   アクションゲーム爆発のファイル  　       //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "explosion.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//頂点バッファへのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];					//爆発型の配列を宣言する

//爆発の初期化処理
void InitExplosion(void)
{
	int nCntExplosion;				//数をカウントする変数を宣言する
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();			//デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion000.png",
		&g_pTextureExplosion);

	//爆発の各パラメータを初期化する
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//カラー
		g_aExplosion[nCntExplosion].nCounterAnim = 0;								//アニメーションカウンター
		g_aExplosion[nCntExplosion].nPatternAnim = 0;								//アニメーションパターンの番号
		g_aExplosion[nCntExplosion].nSize = 1;										//大きさ
		g_aExplosion[nCntExplosion].bUse = false;									//使用しているカウンターかどうか
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点の設定
		pVtx[1].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);
		pVtx[0].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * g_aExplosion[nCntExplosion].nSize, 0.0f);

		//rhw設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.05f, 1.0f);

		//テクスチャ座標の設定
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//爆発の終了処理
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//爆発の更新処理
void UpdateExplosion(void)
{
	int nCntExplosion;	//数をカウントする変数を宣言する
	VERTEX_2D*pVtx;		//頂点情報へのポインタ
	Player*pPlayer;

	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//テクスチャの更新
		g_aExplosion[nCntExplosion].nCounterAnim++;

		if (g_aExplosion[nCntExplosion].bUse == true)
		{

			//頂点の設定
			pVtx[1].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) + 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) - 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);
			pVtx[0].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) - 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) - 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) + 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) + 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x) - 30.0f * g_aExplosion[nCntExplosion].nSize, (g_aExplosion[nCntExplosion].pos.y) + 30.0f * g_aExplosion[nCntExplosion].nSize, 0.0f);

			//アニメーション処理
			if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)			//アニメーションの速さを決める条件
			{
				g_aExplosion[nCntExplosion].nPatternAnim += 1;				//カウンターNo.を更新する

				if (g_aExplosion[nCntExplosion].nPatternAnim == 9)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}

				if (pPlayer->state != PLAYERSTATE_DAMAGE && pPlayer->state != PLAYERSTATE_DEATH)
				{
					if ((pPlayer->pos.x - g_aExplosion[nCntExplosion].pos.x) * (pPlayer->pos.x - g_aExplosion[nCntExplosion].pos.x) +
						((pPlayer->pos.y - 37.5f) - g_aExplosion[nCntExplosion].pos.y) * ((pPlayer->pos.y - 37.5f) - g_aExplosion[nCntExplosion].pos.y) <
						(g_aExplosion[nCntExplosion].nSize * 30.0f) * (g_aExplosion[nCntExplosion].nSize * 30.0f))
					{
						pPlayer->nCounterState = 180;
						pPlayer->state = PLAYERSTATE_DAMAGE;
						AddScore(-500);
						SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS500);
					}
				}

				//テクスチャ座標の設定
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//爆発の描画処理
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//使用されている場合
		 //四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//爆発の設定
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, int size)
{
	int nCntExplosion;		//数をカウントする変数を宣言する

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//爆発の
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//使用されていない場合

		 //爆発の位置の設定
			g_aExplosion[nCntExplosion].pos = pos;

			//爆発の色の設定
			g_aExplosion[nCntExplosion].col = col;

			//爆発の大きさの設定
			g_aExplosion[nCntExplosion].nSize = size;

			//頂点の設定
			pVtx[1].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * size, 0.0f);
			pVtx[0].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y - 30.0f) * size, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x + 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * size, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((g_aExplosion[nCntExplosion].pos.x - 30.0f) * size, (g_aExplosion[nCntExplosion].pos.y + 30.0f) * size, 0.0f);



			//テクスチャ座標の設定
			pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
			
			//テクスチャカウンターの設定
			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			//アニメーションカウンターNo.の設定
			g_aExplosion[nCntExplosion].nPatternAnim = 0;
			//使用されている状態にする
			g_aExplosion[nCntExplosion].bUse = true;

			PlaySound(SOUND_LABEL_SE_EXPLOSION);
			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}