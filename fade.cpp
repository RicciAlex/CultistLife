#include "fade.h"

//グローバル変数を宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		//頂点バッファへのポインタ
MODE g_modeNext;
FADE g_fade;
D3DXCOLOR g_colorFade;

//フェードの初期化処理
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	g_fade = FADE_IN;										//フェードインにする
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);		//カラーの初期化

															//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();

	InitTitle();
	//SetMode(g_modeNext);
}

//フェードの終了処理
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//フェードの更新処理
void UpdateFade(void)
{
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	MODE mode;

	mode = GetMode();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//フェードの更新
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorFade.a -= 0.05f;
			if (g_colorFade <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;

			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += 0.05f;
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;

				if (mode != MODE_RESULT)
				{
					//サウンドを止まる処理
					StopSound();
				}
						
				/*if (mode == MODE_TITLE)
				{
					UninitTitle();
				}
				else if (mode == MODE_RESULT)
				{
					UninitResult();
				}
				else
				{
					UninitGame();
				}*/
				/*else if (mode == MODE_RANKING)
				{
					UninitRanking();
				}*/

				//モードを設定する
				SetMode(g_modeNext);

			}
		}

		//頂点カラーの設定
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
}

//フェードの描画処理
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//フェードの設定処理
void SetFade(MODE modeNext)
{
	g_modeNext = modeNext;
	g_fade = FADE_OUT;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//フェードの取得
FADE GetFade(void)
{
	return g_fade;
}