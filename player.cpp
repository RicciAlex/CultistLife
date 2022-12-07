//===================================================//
//                                                   //
//        �A�N�V�����Q�[���v���C���[�t�@�C��         //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "player.h"
#include "input.h"
#include "platform.h"
#include "water.h"
#include "boss.h"
#include "fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_apTexturePlayer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player g_Player;									//�v���C���[�^�̕ϐ���錾����
int g_nCountJump;									//�W�����v���ԃJ�E���^�[
float g_fGravity;									//�d��
float g_ftryFriction;								//���C (����ʂ͕��ʂŁA�E��ʂ͐��ł�)
int g_nStartingSpeed;
float g_fSliding;
int g_nAnim;
bool g_bWinPlayer;

//�v���C���[�̏���������
void InitPlayer(void)
{
	MODE mode;						//���[�h
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̏��ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^

	
	pDevice = GetDevice();			//�f�o�C�X�̎擾
	mode = GetMode();				//���[�h�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PlayerSpriteSheet.png",
		&g_apTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	//�O���o���ϐ��̏�����
	g_nCountJump = 0;
	g_fGravity = 0.01;
	g_nStartingSpeed = 0;
	g_ftryFriction = 1.0f;
	g_fSliding = 0.5f;
	g_nAnim = 0;
	g_bWinPlayer = false;

	//�v���C���[�̕ϐ��̏�����
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

	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	g_Player.nCounterAnim = 0;								//�A�j���[�V�����J�E���^�[
	g_Player.nPatternAnim = 0;								//�A�j���[�V�����p�^�[��
	g_Player.nDirectionMove = 0;							//����
	g_Player.MoveState = MOVESTATE_FALLING;					//�ړ����
	g_Player.nCurrentPlatform = MAX_PLATFORM;				//���݂̃u���b�N
	g_Player.state = PLAYERSTATE_NORMAL;					//���
	g_Player.nCounterState = 0;								//��ԃJ�E���^�[

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}

//�v���C���[�̏I������
void UninitPlayer(void)
{
	//�e�N�X�`���|�C���^�̔j��
	if (g_apTexturePlayer != NULL)
	{
		g_apTexturePlayer->Release();
		g_apTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//�v���C���[�̍X�V����
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	MODE mode;						//���[�h

	mode = GetMode();				//���[�h�̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//=====================================================//
	//                     ���C�̐ݒ�                      //
	int nWater;

	//���̓����蔻��
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
	//                   �L�[����������                    //
	if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
	{//D�L�[���͉E�̃A���[�L�[�������ꍇ
		g_Player.nDirectionMove = 0;

		if (g_Player.MoveState == MOVESTATE_LANDED)
		{//���n�̏ꍇ
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
		{//�W�����v���ɐi�ޏꍇ
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
		{//�W�����v�����ɖ߂肽���ꍇ
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
	{//A�L�[���͍��̃A���[�L�[�������ꍇ
		g_Player.nDirectionMove = 1;

		if (g_Player.MoveState == MOVESTATE_LANDED)
		{
			if (g_Player.move.x <= 4.0f && g_Player.move.x >= -4.0f)
			{//���n�̏ꍇ
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
		{//�W�����v���ɐi�ޏꍇ
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
		{//�W�����v�����ɖ߂肽���ꍇ
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
	{//�X�y�[�X�o�[���AW�L�[���͏�A���[�L�[�������ꍇ
		if (g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
		{
			//�W�����v�����Ԃɂ���
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
	//                  �A�j���[�V��������                 //
	if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_RIGHT) == true)
	{//�ړ���
		g_Player.nCounterAnim++;

		if (g_Player.nCounterAnim % 8 == 7 && g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
		{
			g_Player.nPatternAnim++;			//���̃p�^�[���ɐi��

			if (g_Player.nPatternAnim >= 2)
			{
				g_Player.nPatternAnim = 0;		//�p�^�[�������ɖ߂�
			}
		}
	}
	else
	{
		if (g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
		{//��~����ꍇ
			g_Player.nPatternAnim = 0;
		}
	}
	//=====================================================//
	//=====================================================//
	//					�_���[�W��Ԃ�������
	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		//�_���[�W�A�j���[�V����
		g_Player.nCounterState--;

		if (g_Player.nCounterState % 10 == 9)
		{
			g_nAnim ^= 1;
		}

		if (g_Player.nCounterState <= 0)
		{//�J�E���^�[��0�ɂȂ�ƁA���ʂ̏�Ԃɖ߂�
			g_nAnim = 1;
			g_Player.nCounterState <= 0;
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		//���_�J���[�̍X�V
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
	//                Y���W�̍X�V����                      //
	g_Player.move.y += 0.5f;					//�d��

	if (mode != MODE_GAME_FIRSTSTAGE_2 && mode != MODE_GAME_SECONDSTAGE_1) //============================================================================================================================
	{
		if (g_Player.pos.y > SCREEN_HEIGHT - 50.0f)
		{//�n�ʂɒ��n
			g_Player.pos.y = SCREEN_HEIGHT - 50.0f;
			g_Player.move.y = 0.0f;
			g_Player.MoveState = MOVESTATE_LANDED;
			g_nCountJump = 0;
			g_nStartingSpeed = 0;
		}
	}
	
	//=====================================================//

	//=====================================================//
	//                 ���̃X�e�[�W�ɐi��                  //
	if (g_Player.pos.x > SCREEN_WIDTH + (PLAYER_WIDTH / 2))
	{
		if (mode == MODE_GAME_FIRSTSTAGE_1)
		{
			SetFade(MODE_GAME_FIRSTSTAGE_2);				//�{�X
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
	//                     ���W�̍X�V                      //

	g_Player.pos.x += g_Player.move.x * g_ftryFriction;
	g_Player.pos.y += g_Player.move.y * g_ftryFriction;

	//�����̏���
	g_Player.move.x += (0.0f - g_Player.move.x) * (0.3f * g_fSliding / g_ftryFriction);

	//=====================================================//

	//=====================================================//
	//              �u���b�N�Ƃ̓����蔻��                 //
	int nCollision = BlockInteraction(&g_Player.pos, &g_Player.LastPos, &g_Player.move, (PLAYER_WIDTH / 2), PLAYER_HEIGHT);

	if (nCollision == 1)
	{//���n�̏ꍇ
		g_Player.MoveState = MOVESTATE_LANDED;
	}

	else if (nCollision == 2)
	{//�����瓖����ꍇ
		g_Player.MoveState = MOVESTATE_FALLING;
	}

	else if (nCollision == 3)
	{//�u���b�N���痎����
		g_Player.MoveState = MOVESTATE_FALLING;
		g_Player.nCurrentPlatform = MAX_PLATFORM;
	}

	else if (nCollision == 4)
	{//���n�̏ꍇ
		g_Player.MoveState = MOVESTATE_LANDED;
		g_fSliding = 0.05f;
	}
	else if (nCollision == 5)
	{//���n�̏ꍇ
		g_Player.MoveState = MOVESTATE_LANDED;
		g_Player.pos.x -= (g_Player.move.x * 0.7f);
	}

	if (nCollision != 4)
	{
		g_fSliding = 0.5f;
	}

	//=====================================================//

	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_WIDTH / 2), g_Player.pos.y + 1.0f, 0.0f);

	if (g_Player.MoveState != MOVESTATE_JUMP && g_Player.MoveState != MOVESTATE_FALLING)
	{
		if (g_Player.nDirectionMove == 0)
		{
			//�e�N�X�`�����W�̍X�V
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
			//�e�N�X�`�����W�̍X�V
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
	
	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();

	//�O��̈ʒu�̍X�V
	g_Player.LastPos = g_Player.pos;

	//======================================================================
	//						�{�X��|������A���̉�ʂɐi��
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
	//				���񂾂�A���U���g��ʂɐi��
	else if (g_Player.state == PLAYERSTATE_DEATH)
	{
		SetFade(MODE_RESULT);
	}
	//=====================================================//
}

//�v���C���[�̕`�揈��
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTexturePlayer);

	//�l�p�`��`�悷��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//�v���C���[�̎擾
Player*GetPlayer(void)
{
	return &g_Player;
}

bool GetWin(void)
{
	return g_bWinPlayer;
}