#include "scorechange.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureSChange = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSChange = NULL;			//頂点バッファへのポインタ
ScoreChange g_SChange[MAX_SCHANGE];
int g_nCntAnim[MAX_SCHANGE];
int g_nPAnim[MAX_SCHANGE];

void InitSChange(void)
{
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCntSChange;					//数をカウントする変数を宣言する
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ChangeValue.png",
		&g_pTextureSChange);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCHANGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSChange,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSChange->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		g_SChange[nCntSChange].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_SChange[nCntSChange].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_SChange[nCntSChange].nType = 0;
		g_SChange[nCntSChange].bUse = false;

		g_nCntAnim[nCntSChange] = 0;
		g_nPAnim[nCntSChange] = 1;

		//弾座標の設定
		pVtx[1].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 25.0f, g_SChange[nCntSChange].pos.y - 25.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 25.0f, g_SChange[nCntSChange].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 25.0f, g_SChange[nCntSChange].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 25.0f, g_SChange[nCntSChange].pos.y + 25.0f, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);


		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSChange->Unlock();
}

//アイテムの終了処理
void UninitSChange(void)
{
	//テクスチャの破棄
	if (g_pTextureSChange != NULL)
	{
		g_pTextureSChange->Release();
		g_pTextureSChange = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffSChange != NULL)
	{
		g_pVtxBuffSChange->Release();
		g_pVtxBuffSChange = NULL;
	}
}

void UpdateSChange(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSChange->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		if (g_SChange[nCntSChange].bUse == true)
		{//弾が使用されていない場合

			g_nCntAnim[nCntSChange]++;

			//座標の更新
			pVtx[1].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (g_nCntAnim[nCntSChange] * 0.008f));
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (g_nCntAnim[nCntSChange] * 0.008f));
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (g_nCntAnim[nCntSChange] * 0.008f));
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (g_nCntAnim[nCntSChange] * 0.008f));

			if (g_nCntAnim[nCntSChange] >= 120)
			{
				g_nCntAnim[nCntSChange] = 0;
				g_SChange[nCntSChange].bUse = false;
			}

			switch (g_SChange[nCntSChange].value)
			{
			case CHANGEVALUE_MINUS250:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);
				break;
			case CHANGEVALUE_MINUS500:
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
				break;
			case CHANGEVALUE_PLUS250:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
				break;
			case CHANGEVALUE_PLUS500:
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			}
		}
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSChange->Unlock();
}

void DrawSChange(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntSChange;						//カウントする変数を宣言する

										//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffSChange, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureSChange);

	for (nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		if (g_SChange[nCntSChange].bUse == true)
		{
			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSChange * 4, 2);
		}
	}
}

void SetSChange(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type, CHANGEVALUE Value)
{
	int nCntSChange;		//カウントする変数を宣言する
	MODE mode;
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	mode = GetMode();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffSChange->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		if (g_SChange[nCntSChange].bUse == false)
		{//弾が使用されていない場合

			g_SChange[nCntSChange].pos = D3DXVECTOR3(850.0f, 60.0f, 0.0f);

			g_SChange[nCntSChange].move = move;

			g_SChange[nCntSChange].value = Value;

			//頂点座標の設定
			pVtx[1].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//アイテムの種類の設定
			g_SChange[nCntSChange].nType = type;

			switch (Value)
			{
			case CHANGEVALUE_MINUS250:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);
				break;
			case CHANGEVALUE_MINUS500:
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);
				break;
			case CHANGEVALUE_PLUS250:
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);
				break;		 
			case CHANGEVALUE_PLUS500:
				pVtx[0].tex = D3DXVECTOR2(0.5f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			}

			

			//使用されているにする
			g_SChange[nCntSChange].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffSChange->Unlock();
}