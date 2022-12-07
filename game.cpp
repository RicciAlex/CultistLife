//===================================================//
//                                                   //
//       �A�N�V�����Q�[���Q�[����ʂ̃t�@�C��        //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "game.h"

bool g_bTutorial;

//�Q�[����ʂ̏���������
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

	//�w�i�̏���������
	InitBg();

	//�X�C�b�`�̏���������
	InitSwitch();

	InitSChange();

	InitArrow();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	InitMinion();

	//�{�X�̏���������
	InitBoss();

	InitItem();

	//�v���b�g�t�H�[���̏���������
	InitPlatform();

	//�e�̏���������
	InitBullet();

	//���̏���������
	InitWater();

	//�����̏���������
	InitExplosion();

	InitPauseMenu();

	//�X�e�[�W�̐ݒ�
	SetStage();
}

//�Q�[����ʂ̏I������
void UninitGame(void)
{
	//�v���C���[�̏I������
	UninitPlayer();

	UninitTutorial();

	//�e�̏I������
	UninitBullet();

	//�G�̏I������
	UninitEnemy();

	UninitItem();

	UninitMinion();

	//�v���b�g�t�H�[���̏I������
	UninitPlatform();

	//�{�X�̏I������
	UninitBoss();

	//���̏I������
	UninitWater();

	//�X�C�b�`�̏I������
	UninitSwitch();

	//�����̏I������
	UninitExplosion();

	UninitArrow();

	UninitSChange();

	UninitPauseMenu();

	//�w�i�̏I������
	UninitBg();
}

//�Q�[����ʂ̍X�V����
void UpdateGame(void)
{
	//�Q�[�����|�[�Y����Ă��邩�ǂ���
	bool bPause;

	//�|�[�Y���j���[�̏����擾
	bPause = GetPauseMenu();

	if (g_bTutorial == false)
	{

		if (bPause == false)
		{
			//�w�i�̍X�V����
			UpdateBg();

			UpdateArrow();

			UpdateSChange();

			//�X�C�b�`�̍X�V����
			UpdateSwitch();

			//�v���b�g�t�H�[���̍X�V����
			UpdatePlatform();

			//�e�̍X�V����
			UpdateBullet();

			UpdateItem();

			//�G�̍X�V����
			UpdateEnemy();

			UpdateMinion();

			//�����̍X�V����
			UpdateExplosion();

			//���X�V����
			UpdateWater();

			UpdateScore();

			//�{�X�̍X�V����
			UpdateBoss();

			//�v���C���[�̍X�V����
			UpdatePlayer();
		}

		if (GetKeyboardTrigger(DIK_P) == true)
		{//�G���^�[�L�[�������ꍇ
			SetPauseMenu();
		}

		if (bPause == true)
		{
			//�|�[�Y���j���[�̍X�V����
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

//�Q�[����ʂ̕`�揈��
void DrawGame(void)
{
	if (g_bTutorial == true)
	{
		//�`���[�g���A���̕`�揈��
		DrawTutorial();
	}
	else
	{
		//�w�i�̕`�揈��
		DrawBg();

		DrawArrow();

		DrawSChange();

		DrawScore();

		//�X�C�b�`�̕`�揈��
		DrawSwitch();

		DrawItem();

		//�G�̕`�揈��
		DrawEnemy();

		DrawMinion();

		//�{�X�̕`�揈��
		DrawBoss();

		//�e�̕`�揈��
		DrawBullet();

		//�̕`�揈���v���b�g�t�H�[��
		DrawPlatform();

		//�v���C���[�̕`��I��
		DrawPlayer();

		//�����̕`�揈��
		DrawExplosion();

		//���̕`�揈��
		DrawWater();

		DrawPauseMenu();
	}
}

//�X�e�[�W�̐ݒ�
void SetStage(void)
{
	MODE Mode;				//���[�h

	Mode = GetMode();		//���[�h�̎擾

	switch (Mode)
	{
	case MODE_GAME_FIRSTSTAGE_1:
		//BonusStage();
		FirstStage();				//�ŏ��̃X�e�[�W
		break;
	case MODE_GAME_FIRSTSTAGE_2:
		FourthStage(); 				//�ŏ��̃{�X�X�e�[�W
		break;
	case MODE_GAME_FIRSTSTAGE_BOSS:
		SecondStage();				//�ŏ��̃{�X�X�e�[�W
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
	SpawnEnemy();					//�G�̐ݒ�
}