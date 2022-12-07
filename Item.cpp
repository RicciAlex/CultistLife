#include "Item.h"
#include "sound.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;			//頂点バッファへのポインタ
ITEM g_aItem[MAX_ITEM];									//Item型の配列を宣言する

void InitItem(void)
{
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCntItem;					//数をカウントする変数を宣言する
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Cards.png",
		&g_pTextureItem);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//Bullet型の各情報を代入する
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].EqPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nCntAnim = 0;
		g_aItem[nCntItem].nType = ITEMTYPE_NULL;
		g_aItem[nCntItem].bUse = false;

		//弾座標の設定
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 25.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 25.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);


		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//アイテムの終了処理
void UninitItem(void)
{
	//テクスチャの破棄
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//アイテムの更新処理
void UpdateItem(void)
{
	VERTEX_2D*pVtx;						//頂点情報へのポインタ
	Player*pPlayer;						//プレイヤーへのポインタ
	int nCntItem;						//カウントする変数を宣言する

										//プレイヤー情報の取得
	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].pos += g_aItem[nCntItem].move;

			if (g_aItem[nCntItem].pos.y >= g_aItem[nCntItem].EqPoint.y + 10.0f || g_aItem[nCntItem].pos.y <= g_aItem[nCntItem].EqPoint.y - 10.0f)
			{
				g_aItem[nCntItem].move.y *= -1;
			}

			if (/*g_aItem[nCntItem].pos.x >= pPlayer->pos.x - 60 && g_aItem[nCntItem].pos.x <= pPlayer->pos.x + 60 &&
				g_aItem[nCntItem].pos.y >= pPlayer->pos.y - 60 && g_aItem[nCntItem].pos.y <= pPlayer->pos.y + 60*/
				((g_aItem[nCntItem].pos.x - pPlayer->pos.x) *(g_aItem[nCntItem].pos.x - pPlayer->pos.x)) + ((g_aItem[nCntItem].pos.y - (pPlayer->pos.y - 40.0f)) *(g_aItem[nCntItem].pos.y - (pPlayer->pos.y - 40.0f))) <= 2500.0f)
			{
				PlaySound(SOUND_LABEL_SE_GETITEM);
				g_aItem[nCntItem].bUse = false;
				AddScore(2000);
			}

			//頂点座標の設定
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//アイテムの描画処理
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;						//カウントする変数を宣言する

										//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureItem);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}

	}
}

//アイテムの設定処理
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type)
{
	int nCntItem;		//カウントする変数を宣言する
	MODE mode;
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	mode = GetMode();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{//弾が使用されていない場合

			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].EqPoint = pos;
			g_aItem[nCntItem].nCntAnim = 0;

			//頂点座標の設定
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);

			//アイテムの種類の設定
			g_aItem[nCntItem].nType = type;

			switch (mode)
			{
			case MODE_GAME_FIRSTSTAGE_1:
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			case MODE_GAME_FIRSTSTAGE_2:
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
				break;
			case MODE_GAME_SECONDSTAGE_1:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);
				break;
			case MODE_GAME_BONUSSTAGE:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
				break;
			}

			

			//使用されているにする
			g_aItem[nCntItem].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}