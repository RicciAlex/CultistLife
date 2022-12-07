//===================================================//
//                                                   //
//        アクションゲームプレイヤーファイル         //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "player.h"
#include "input.h"
#include "platform.h"
#include "water.h"
#include "boss.h"
#include "fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTexturePlayer = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファへのポインタ
Player g_Player;									//プレイヤー型の変数を宣言する
int g_nCountJump;									//ジャンプ時間カウンター
float g_fGravity;									//重力
float g_ftryFriction;								//摩擦 (左画面は普通で、右画面は水です)
int g_nStartingSpeed;
float g_fSliding;
int g_nAnim;
bool g_bWinPlayer;

//プレイヤーの初期化処理
void InitPlayer(void)
{
	MODE mode;						//モード
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの情報へのポインタ
	VERTEX_2D*pVtx;					//頂点情報へのポインタ

	
	pDevice = GetDevice();			//デバイスの取得
	mode = GetMode();				//モードの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PlayerSpriteSheet.png",
		&g_apTexturePlayer);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//グロバル変数の初期化
	g_nCountJump = 0;
	g_fGravity = 0.01;
	g_nStartingSpeed = 0;
	g_ftryFriction = 1.0f;
	g_fSliding = 0.5f;
	g_nAnim = 0;
	g_bWinPlayer = false;

	//プレイヤーの変数の初期化
	if (mode == MODE_GAME_FIRSTSTAGE_1)
	{
		g_Player.pos = D3DXVECTOR3(100.0f, 550.0f, 0.0f);
		g_Player.LastPos = D3DXVECTOR3(100.0f, 550.0f, 0.0f);
	}
	else if (mode == MODE_GAME_FIRSTSTAGE_2)
	{
		g_Player.pos = D3DXVECTOR3(100.0f, 550.0f, 0.0f);
		g_Player.LastPos = D3DXVECTOR3(100.0f, 550.0f, 0.0f);
	}
	else if (mode == MODE_GAME_FIRSTSTAGE_BOSS)
	{
		g_Player.pos = D3DXVECTOR3(200.0f, 150.0f, 0.0f);
		g_Player.LastPos = D3DXVECTOR3(200.0f, 150.0f, 0.0f);
	}
	else if (mode == MODE_GAME_SECONDSTAGE_1)
	{
		g_Player.pos = D3DXVECTOR3(100.0f, 670.0f, 0.0f);
		g_Player.LastPos = D3DXVECTOR3(100.0f, 670.0f, 0.0f);
	}
	else if (mode == MODE_GAME_SECONDSTAGE_BOSS)
	{
		g_Player.pos = D3DXVECTOR3(100.0f, 670.0f, 0.0f);
		g_Player.LastPos = D3DXVECTOR3(100.0f, 670.0f, 0.0f);
	}
	else if (mode == MODE_GAME_BONUSSTAGE)
	{
		g_Player.pos = D3DXVECTOR3(100.0f, 650.0f, 0.0f);
		g_Player.LastPos = D3DXVECTOR3(100.0f, 650.0f, 0.0f);
	}

	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	g_Player.nCounterAnim = 0;								//アニメーションカウンター
	g_Player.nPatternAnim = 0;								//アニメーションパターン
	g_Player.nDirectionMove = 0;							//方向
	g_Player.MoveState = MOVESTATE_FALLING;					//移動状態
	g_Player.nCurrentPlatform = MAX_PLATFORM;				//現在のブロック
	g_Player.state = PLAYERSTATE_NORMAL;					//状態
	g_Player.nCounterState = 0;								//状態カウンター

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();
}

//プレイヤーの終了処理
void UninitPlayer(void)
{
	//テクスチャポインタの破棄
	if (g_apTexturePlayer != NULL)
	{
		g_apTexturePlayer->Release();
		g_apTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//プレイヤーの更新処理
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx;					//頂点情報へのポインタ
	MODE mode;						//モード

	mode = GetMode();				//モードの取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//=====================================================//
	//                     摩擦の設定                      //
	int nWater;

	//水の当たり判定
	nWater = WaterInteraction(&g_Player.pos, &g_Player.move, PLAYER_WIDTH, PLAYER_HEIGHT);

	if (nWater == 0)
	{
		g_ftryFriction = 1.0f;
	}
	else if (nWater == 1)
	{
		g_ftryFriction = 0.65f;
	}

	//=====================================================//

	//=====================================================//
	//                   キーを押したら                    //
	if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
	{//Dキー又は右のアローキーを押す場合
		g_Player.nDirectionMove = 0;

		if (g_Player.MoveState == MOVESTATE_LANDED)
		{//着地の場合
			if (g_Player.move.x <= 4.0f && g_Player.move.x >= -4.0f)
			{
				if (g_fSliding >= 0.4f)
				{
					g_Player.move.x += sin(D3DX_PI * 0.5f) * 1.5f;
				}
				else
				{
					g_Player.move.x += sin(D3DX_PI * 0.5f) * 0.1f;
				}

			}
			if (g_Player.move.y <= 4.0f && g_Player.move.y >= -4.0f)
			{
				g_Player.move.y += cos(D3DX_PI * 0.5f) * 1.5f;
			}
		}
		else if (g_Player.MoveState != MOVESTATE_LANDED && g_nStartingSpeed >= 0)
		{//ジャンプ中に進む場合
			if (g_Player.move.x <= 4.0f && g_Player.move.x >= -4.0f)
			{
				g_Player.move.x += sin(D3DX_PI * 0.5f) * 1.5f;
			}
			if (g_Player.move.y <= 4.0f && g_Player.move.y >= -4.0f)
			{
				g_Player.move.y += cos(D3DX_PI * 0.5f) * 1.5f;
			}
			g_nStartingSpeed = 1;
		}
		else
		{//ジャンプ中後ろに戻りたい場合
			if (g_Player.move.x <= 3.0f && g_Player.move.x >= -3.0f)
			{
				g_Player.move.x += sin(D3DX_PI * 0.5f) * 0.7f;
			}
			if (g_Player.move.y <= 4.0f && g_Player.move.y >= -4.0f)
			{
				g_Player.move.y += cos(D3DX_PI * 0.5f) * 0.7f;
			}
		}
	}
	else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
	{//Aキー又は左のアローキーを押す場合
		g_Player.nDirectionMove = 1;

		if (g_Player.MoveState == MOVESTATE_LANDED)
		{
			if (g_Player.move.x <= 4.0f && g_Player.move.x >= -4.0f)
			{//着地の場合
				if (g_fSliding >= 0.4f)
				{
					g_Player.move.x += sin(-D3DX_PI * 0.5f) * 1.5f;
				}
				else
				{
					g_Player.move.x += sin(-D3DX_PI * 0.5f) * 0.1f;
				}
			}
			if (g_Player.move.y <= 4.0f && g_Player.move.y >= -4.0f)
			{
				g_Player.move.y += cos(-D3DX_PI * 0.5f) * 1.5f;
			}
		}
		else if (g_Player.MoveState != MOVESTATE_LANDED && g_nStartingSpeed <= 0)
		{//ジャンプ中に進む場合
			if (g_Player.move.x <= 4.0f && g_Player.move.x >= -4.0f)
			{
				g_Player.move.x += sin(-D3DX_PI * 0.5f) * 1.5f;
			}
			if (g_Player.move.y <= 4.0f && g_Player.move.y >= -4.0f)
			{
				g_Player.move.y += cos(-D3DX_PI * 0.5f) * 1.5f;
			}
			g_nStartingSpeed = -1;
		}
		else
		{//ジャンプ中後ろに戻りたい場合
			if (g_Player.move.x <= 3.0f && g_Player.move.x >= -3.0f)
			{
				g_Player.move.x += sin(-D3DX_PI * 0.5f) * 0.7f;
			}
			if (g_Player.move.y <= 4.0f && g_Player.move.y >= -4.0f)
			{
				g_Player.move.y += cos(-D3DX_PI * 0.5f) * 0.7f;
			}
		}
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
	{//スペースバー又、Wキー又は上アローキーを押す場合
		if (g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
		{
			//ジャンプする状態にする
			g_Player.MoveState = MOVESTATE_JUMP;

			g_Player.nCurrentPlatform = MAX_PLATFORM;

			g_Player.move.y -= 12.0f;

			if (g_Player.move.x > 0)
			{
				g_nStartingSpeed = 1;
			}
			else if (g_Player.move.x < 0)
			{
				g_nStartingSpeed = -1;
			}
			else
			{
				g_nStartingSpeed = 0;
			}
		}
	}

#ifdef _DEBUG

	if (GetKeyboardTrigger(DIK_L) == true)
	{
		g_Player.pos = D3DXVECTOR3(1200.0f, 150.0f, 0.0f);
	}



	if (GetKeyboardTrigger(DIK_N) == true)
	{
		Boss*pBoss;

		pBoss = GetBoss();

		pBoss->nLife = 0;
	}

#endif // DEBUG

	//=====================================================//

	//=====================================================//
	//                  アニメーション処理                 //
	if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_RIGHT) == true)
	{//移動中
		g_Player.nCounterAnim++;

		if (g_Player.nCounterAnim % 8 == 7 && g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
		{
			g_Player.nPatternAnim++;			//次のパターンに進む

			if (g_Player.nPatternAnim >= 2)
			{
				g_Player.nPatternAnim = 0;		//パターンを元に戻す
			}
		}
	}
	else
	{
		if (g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
		{//停止する場合
			g_Player.nPatternAnim = 0;
		}
	}
	//=====================================================//
	//=====================================================//
	//					ダメージ状態だったら
	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		//ダメージアニメーション
		g_Player.nCounterState--;

		if (g_Player.nCounterState % 10 == 9)
		{
			g_nAnim ^= 1;
		}

		if (g_Player.nCounterState <= 0)
		{//カウンターが0になると、普通の状態に戻す
			g_nAnim = 1;
			g_Player.nCounterState <= 0;
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		//頂点カラーの更新
		pVtx[0].col = D3DCOLOR_RGBA(255, 255 * (g_nAnim), 255 * (g_nAnim), 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255 * (g_nAnim), 255 * (g_nAnim), 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255 * (g_nAnim), 255 * (g_nAnim), 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255 * (g_nAnim), 255 * (g_nAnim), 255);
	}
	else
	{
		if (g_nAnim != 0)
		{
			g_nAnim = 0;
		}
	}

	//=====================================================//
	//                Y座標の更新処理                      //
	g_Player.move.y += 0.5f;					//重力

	if (mode != MODE_GAME_FIRSTSTAGE_2 && mode != MODE_GAME_SECONDSTAGE_1) //============================================================================================================================
	{
		if (g_Player.pos.y > SCREEN_HEIGHT - 50.0f)
		{//地面に着地
			g_Player.pos.y = SCREEN_HEIGHT - 50.0f;
			g_Player.move.y = 0.0f;
			g_Player.MoveState = MOVESTATE_LANDED;
			g_nCountJump = 0;
			g_nStartingSpeed = 0;
		}
	}
	
	//=====================================================//

	//=====================================================//
	//                 次のステージに進む                  //
	if (g_Player.pos.x > SCREEN_WIDTH + (PLAYER_WIDTH / 2))
	{
		if (mode == MODE_GAME_FIRSTSTAGE_1)
		{
			SetFade(MODE_GAME_FIRSTSTAGE_2);				//ボス
		}
		else if (mode == MODE_GAME_FIRSTSTAGE_2)
		{
			SetFade(MODE_GAME_FIRSTSTAGE_BOSS);
		}
		else if (mode == MODE_GAME_SECONDSTAGE_1)
		{
			SetFade(MODE_GAME_BONUSSTAGE);
		}
		else if (mode == MODE_GAME_BONUSSTAGE)
		{
			SetFade(MODE_GAME_SECONDSTAGE_BOSS);
		}
	}
	//=====================================================//

	//=====================================================//
	//                     座標の更新                      //

	g_Player.pos.x += g_Player.move.x * g_ftryFriction;
	g_Player.pos.y += g_Player.move.y * g_ftryFriction;

	//慣性の処理
	g_Player.move.x += (0.0f - g_Player.move.x) * (0.3f * g_fSliding / g_ftryFriction);

	//=====================================================//

	//=====================================================//
	//              ブロックとの当たり判定                 //
	int nCollision = BlockInteraction(&g_Player.pos, &g_Player.LastPos, &g_Player.move, (PLAYER_WIDTH / 2), PLAYER_HEIGHT);

	if (nCollision == 1)
	{//着地の場合
		g_Player.MoveState = MOVESTATE_LANDED;
	}

	else if (nCollision == 2)
	{//下から当たる場合
		g_Player.MoveState = MOVESTATE_FALLING;
	}

	else if (nCollision == 3)
	{//ブロックから落ちる
		g_Player.MoveState = MOVESTATE_FALLING;
		g_Player.nCurrentPlatform = MAX_PLATFORM;
	}

	else if (nCollision == 4)
	{//着地の場合
		g_Player.MoveState = MOVESTATE_LANDED;
		g_fSliding = 0.05f;
	}
	else if (nCollision == 5)
	{//着地の場合
		g_Player.MoveState = MOVESTATE_LANDED;
		g_Player.pos.x -= (g_Player.move.x * 0.7f);
	}

	if (nCollision != 4)
	{
		g_fSliding = 0.5f;
	}

	//=====================================================//

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f, 0.0f);

	if (g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
	{
		if (g_Player.nDirectionMove == 0)
		{
			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.078f + (0.5f * g_Player.nPatternAnim), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.47f + (0.5f * g_Player.nPatternAnim), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.078f + (0.5f * g_Player.nPatternAnim), 0.49f);
			pVtx[3].tex = D3DXVECTOR2(0.47f + (0.5f * g_Player.nPatternAnim), 0.49f);
		}
		else if (g_Player.nDirectionMove == 1)
		{
			pVtx[1].tex = D3DXVECTOR2(0.078f + (0.5f * g_Player.nPatternAnim), 0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.47f + (0.5f * g_Player.nPatternAnim), 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.078f + (0.5f * g_Player.nPatternAnim), 0.49f);
			pVtx[2].tex = D3DXVECTOR2(0.47f + (0.5f * g_Player.nPatternAnim), 0.49f);
		}
	}
	else
	{
		if (g_Player.nDirectionMove == 0)
		{
			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.078f, 0.53f);
			pVtx[1].tex = D3DXVECTOR2(0.47f, 0.53f);
			pVtx[2].tex = D3DXVECTOR2(0.078f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.47f, 1.0f);
		}
		else if (g_Player.nDirectionMove == 1)
		{
			pVtx[1].tex = D3DXVECTOR2(0.078f, 0.53f);
			pVtx[0].tex = D3DXVECTOR2(0.47f, 0.53f);
			pVtx[3].tex = D3DXVECTOR2(0.078f, 1.0f);
			pVtx[2].tex = D3DXVECTOR2(0.47f, 1.0f);
		}
	}
	
	

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();

	//前回の位置の更新
	g_Player.LastPos = g_Player.pos;

	//======================================================================
	//						ボスを倒したら、次の画面に進む
	if (g_Player.state == PLAYERSTATE_WIN)
	{
		switch (mode)
		{
		case MODE_GAME_FIRSTSTAGE_BOSS:
			SetFade(MODE_GAME_SECONDSTAGE_1);
			break;
		case MODE_GAME_SECONDSTAGE_BOSS:
			g_bWinPlayer = true;
			SetFade(MODE_RESULT);
			break;
		}
	}
	//=====================================================//
	//=====================================================//
	//				死んだら、リザルト画面に進む
	else if (g_Player.state == PLAYERSTATE_DEATH)
	{
		SetFade(MODE_RESULT);
	}
	//=====================================================//
}

//プレイヤーの描画処理
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTexturePlayer);

	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//プレイヤーの取得
Player*GetPlayer(void)
{
	return &g_Player;
}

bool GetWin(void)
{
	return g_bWinPlayer;
}