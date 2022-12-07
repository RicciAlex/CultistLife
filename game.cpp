//===================================================//
//                                                   //
//       アクションゲームゲーム画面のファイル        //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//インクルードファイル
#include "game.h"

bool g_bTutorial;

//ゲーム画面の初期化処理
void InitGame(void)
{
	MODE mode;

	mode = GetMode();

	if (mode == MODE_GAME_FIRSTSTAGE_1)
	{
		g_bTutorial = true;
	}
	else
	{
		g_bTutorial = false;
	}

	//背景の初期化処理
	InitBg();

	//スイッチの初期化処理
	InitSwitch();

	InitSChange();

	InitArrow();

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	InitMinion();

	//ボスの初期化処理
	InitBoss();

	InitItem();

	//プラットフォームの初期化処理
	InitPlatform();

	//弾の初期化処理
	InitBullet();

	//水の初期化処理
	InitWater();

	//爆発の初期化処理
	InitExplosion();

	InitPauseMenu();

	//ステージの設定
	SetStage();
}

//ゲーム画面の終了処理
void UninitGame(void)
{
	//プレイヤーの終了処理
	UninitPlayer();

	UninitTutorial();

	//弾の終了処理
	UninitBullet();

	//敵の終了処理
	UninitEnemy();

	UninitItem();

	UninitMinion();

	//プラットフォームの終了処理
	UninitPlatform();

	//ボスの終了処理
	UninitBoss();

	//水の終了処理
	UninitWater();

	//スイッチの終了処理
	UninitSwitch();

	//爆発の終了処理
	UninitExplosion();

	UninitArrow();

	UninitSChange();

	UninitPauseMenu();

	//背景の終了処理
	UninitBg();
}

//ゲーム画面の更新処理
void UpdateGame(void)
{
	//ゲームがポーズされているかどうか
	bool bPause;

	//ポーズメニューの情報を取得
	bPause = GetPauseMenu();

	if (g_bTutorial == false)
	{

		if (bPause == false)
		{
			//背景の更新処理
			UpdateBg();

			UpdateArrow();

			UpdateSChange();

			//スイッチの更新処理
			UpdateSwitch();

			//プラットフォームの更新処理
			UpdatePlatform();

			//弾の更新処理
			UpdateBullet();

			UpdateItem();

			//敵の更新処理
			UpdateEnemy();

			UpdateMinion();

			//爆発の更新処理
			UpdateExplosion();

			//水更新処理
			UpdateWater();

			UpdateScore();

			//ボスの更新処理
			UpdateBoss();

			//プレイヤーの更新処理
			UpdatePlayer();
		}

		if (GetKeyboardTrigger(DIK_P) == true)
		{//エンターキーを押す場合
			SetPauseMenu();
		}

		if (bPause == true)
		{
			//ポーズメニューの更新処理
			UpdatePauseMenu();
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_bTutorial = false;
		}
	}
}

//ゲーム画面の描画処理
void DrawGame(void)
{
	if (g_bTutorial == true)
	{
		//チュートリアルの描画処理
		DrawTutorial();
	}
	else
	{
		//背景の描画処理
		DrawBg();

		DrawArrow();

		DrawSChange();

		DrawScore();

		//スイッチの描画処理
		DrawSwitch();

		DrawItem();

		//敵の描画処理
		DrawEnemy();

		DrawMinion();

		//ボスの描画処理
		DrawBoss();

		//弾の描画処理
		DrawBullet();

		//の描画処理プラットフォーム
		DrawPlatform();

		//プレイヤーの描画終了
		DrawPlayer();

		//爆発の描画処理
		DrawExplosion();

		//水の描画処理
		DrawWater();

		DrawPauseMenu();
	}
}

//ステージの設定
void SetStage(void)
{
	MODE Mode;				//モード

	Mode = GetMode();		//モードの取得

	switch (Mode)
	{
	case MODE_GAME_FIRSTSTAGE_1:
		//BonusStage();
		FirstStage();				//最初のステージ
		break;
	case MODE_GAME_FIRSTSTAGE_2:
		FourthStage(); 				//最初のボスステージ
		break;
	case MODE_GAME_FIRSTSTAGE_BOSS:
		SecondStage();				//最初のボスステージ
		break;
	case MODE_GAME_SECONDSTAGE_1:
		//BonusStage();
		FifthStage();
		break;
	case MODE_GAME_SECONDSTAGE_BOSS:
		ThirdStage();
		break;
	case MODE_GAME_BONUSSTAGE:
		BonusStage();
		break;
	default:
		break;
	}
	if (Mode != MODE_GAME_FIRSTSTAGE_BOSS && Mode != MODE_GAME_SECONDSTAGE_BOSS)
	{
		PlaySound(SOUND_LABEL_BGMNORMALSTAGE);
	}
	SpawnEnemy();					//敵の設定
}