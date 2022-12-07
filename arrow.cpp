//===================================================//
//                                                   //
//     　  アクションゲームアロー画面ファイル    　  //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "arrow.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;			//頂点バッファへのポインタ
Arrow g_Arrow[MAX_ARROW];								//アロー型のグローバル変数を宣言する
int g_nCntAnim;											//アニメーションカウンター
int g_nPAnim;											//アニメーションパターン

//アローの初期化処理
void InitArrow(void)
{
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	int nCntArrow;					//数をカウントする変数を宣言する
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//グローバル変数の初期化
	g_nCntAnim = 0;
	g_nPAnim = 1;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Arrow.png",
		&g_pTextureArrow);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ARROW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArrow,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		//アロー型の各パラメータの初期化
		g_Arrow[nCntArrow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_Arrow[nCntArrow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
		g_Arrow[nCntArrow].nType = 0;								//種類
		g_Arrow[nCntArrow].bUse = false;							//使用されているかどうか

		//弾座標の設定
		pVtx[1].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 25.0f, g_Arrow[nCntArrow].pos.y - 25.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 25.0f, g_Arrow[nCntArrow].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 25.0f, g_Arrow[nCntArrow].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 25.0f, g_Arrow[nCntArrow].pos.y + 25.0f, 0.0f);

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
	g_pVtxBuffArrow->Unlock();
}

//アローの終了処理
void UninitArrow(void)
{
	//テクスチャの破棄
	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffArrow != NULL)
	{
		g_pVtxBuffArrow->Release();
		g_pVtxBuffArrow = NULL;
	}
}

//アロー更新処理
void UpdateArrow(void)
{
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	g_nCntAnim++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == true)
		{//弾が使用されていない場合

			//アニメーション処理
			g_Arrow[nCntArrow].pos += g_Arrow[nCntArrow].move;

			if (g_nCntAnim % 30 == 29)
			{
				g_nPAnim *= -1;
			}
			if (g_nCntAnim % 60 == 59)
			{
				g_Arrow[nCntArrow].move.x *= -1;
			}

			if (g_nPAnim > 0)
			{
				//座標の更新
				pVtx[(nCntArrow * 4) + 1].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
				pVtx[(nCntArrow * 4) + 0].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
				pVtx[(nCntArrow * 4) + 3].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);
				pVtx[(nCntArrow * 4) + 2].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);

				pVtx[(nCntArrow * 4) + 0].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCntArrow * 4) + 1].tex = D3DXVECTOR2(1.0, 0.0f);
				pVtx[(nCntArrow * 4) + 2].tex = D3DXVECTOR2(0.5f, 1.0f);
				pVtx[(nCntArrow * 4) + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (g_nPAnim < 0)
			{
				//座標の更新
				pVtx[(nCntArrow * 4) + 1].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
				pVtx[(nCntArrow * 4) + 0].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
				pVtx[(nCntArrow * 4) + 3].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);
				pVtx[(nCntArrow * 4) + 2].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);

				pVtx[(nCntArrow * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[(nCntArrow * 4) + 1].tex = D3DXVECTOR2(0.5f, 0.0f);
				pVtx[(nCntArrow * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[(nCntArrow * 4) + 3].tex = D3DXVECTOR2(0.5f, 1.0f);
			}
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffArrow->Unlock();
}

//アローの描画処理
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntArrow;						//カウントする変数を宣言する

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureArrow);

	for (nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == true)
		{//使用されている場合
			//四角形を描画する
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntArrow * 4, 2);
		}
	}
}

//アローの設定処理
void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type)
{
	int nCntArrow;		//カウントする変数を宣言する
	MODE mode;			//モード型の変数
	VERTEX_2D*pVtx;		//頂点情報へのポインタ

	mode = GetMode();	//モードの取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == false)
		{//弾が使用されていない場合

			g_Arrow[nCntArrow].pos = pos;		//位置

			g_Arrow[nCntArrow].move = move;		//移動量

			//頂点座標の設定
			pVtx[1].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);

			//アイテムの種類の設定
			g_Arrow[nCntArrow].nType = type;

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

			//使用されているにする
			g_Arrow[nCntArrow].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffArrow->Unlock();
}