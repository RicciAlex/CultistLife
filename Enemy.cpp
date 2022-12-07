//==========================================//
//                                          //
//              �G�̃t�@�C��                //
//�@�@�@�@�@�@ Author: Ricci Alex           //
//                                          //
//==========================================//

//�C���N���[�h�t�@�C��
#include "Enemy.h"
#include "platform.h"

//�}�N����`
#define SLIME_WIDTH		(40.0f)								//�X���C���̕�
#define SLIME_HEIGHT	(40.0f)								//�X���C���̍���

//�O���[�o���ϐ���錾
LPDIRECT3DTEXTURE9 g_apTextureSlime[2] = {};					//�G�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_apTextureMimic = NULL;
LPDIRECT3DTEXTURE9 g_apTextureCard = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G�^�̔z���錾����
int g_aDamage[MAX_ENEMY];
int g_aMemoryInteraction[MAX_ENEMY];

//�G�̏���������
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̏��ւ̃|�C���^
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCntEnemy;					//�����J�E���g����ϐ���錾����

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SpriteSheetCompleto.png",
		&g_apTextureSlime[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\SlimeGreen_SpriteSheet2.png",
		&g_apTextureSlime[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Mimic_SpriteSheet.png",
		&g_apTextureMimic);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\CardEnemy.png",
		&g_apTextureCard);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�G�^�̕ϐ��̊e�p�����[�^�̏�����
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���݂̈ʒu
		g_aEnemy[nCntEnemy].LastPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�O��̈ʒu
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���
		g_aEnemy[nCntEnemy].MoveState = MOVESTATE_FALLING;						//�ړ����
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;							//�G�̏��
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;		//�v���C���[�������邩�ǂ���
		g_aEnemy[nCntEnemy].fSight = 250.0f;									//����
		g_aEnemy[nCntEnemy].fHeight = SLIME_HEIGHT;								//����
		g_aEnemy[nCntEnemy].fWidth = SLIME_WIDTH;								//����
		g_aEnemy[nCntEnemy].nType = ENEMYTYPE_BLUESLIME;						//���
		g_aEnemy[nCntEnemy].nCountAnim = 0;										//�A�j���[�V�����J�E���^�[
		g_aEnemy[nCntEnemy].nPatternAnim = 0;									//�A�j���[�V�����p�^�[��
		g_aEnemy[nCntEnemy].nChaseCounter = 0;									//�ǂ�������J�E���^�[
		g_aEnemy[nCntEnemy].nCounterState = 0;									//��ԃJ�E���^�[
		g_aEnemy[nCntEnemy].nCurrentPlatform = 101;								//���݂̃v���b�g�t�H�[��
		g_aEnemy[nCntEnemy].nDirection = 1;										//����
		g_aEnemy[nCntEnemy].bUse = false;										//�g�p����Ă��邩�ǂ���

		//�O���[�o���ϐ��̏�����
		g_aDamage[nCntEnemy] = 0;
		g_aMemoryInteraction[nCntEnemy] = 0;

		//���_�ݒ�
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.125f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
		pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//�G�̏I������
void UninitEnemy(void)
{
	int nCount;
	
	//�e�N�X�`���̔j��
	for (nCount = 0; nCount < 2; nCount++)
	{
		
		if (g_apTextureSlime[nCount] != NULL)
		{					
			g_apTextureSlime[nCount]->Release();
			g_apTextureSlime[nCount] = NULL;
		}
	}
	if (g_apTextureMimic != NULL)
	{			   
		g_apTextureMimic->Release();
		g_apTextureMimic = NULL;
	}
	if (g_apTextureCard != NULL)
	{			   
		g_apTextureCard->Release();
		g_apTextureCard = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//�G�̍X�V����
void UpdateEnemy(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	WATER*pWater;		//�����ւ̃|�C���^
	Player*pPlayer;		//�v���C���[���ւ̃|�C���^
	int nCount;			//�����J�E���g����ϐ���錾
	int nCollision;		//�u���b�N�̓����蔻��

	pWater = GetWater();		//���̏����擾
	pPlayer = GetPlayer();		//�v���C���[���̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		if (g_aEnemy[nCount].bUse == true)
		{//�g�p����Ă���ꍇ
			
			if (g_aEnemy[nCount].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCount].nType == ENEMYTYPE_GREENSLIME || g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
			{//�X���C���̏ꍇ�A�v���C���[�������邩�ǂ������肷��
				EnemyEncounter(nCount, SLIME_HEIGHT);
			}
			
			//���񂾏�Ԃ�������A��ʂ���o��
			if (g_aEnemy[nCount].state == ENEMYSTATE_DEATH)
			{
				if (g_aEnemy[nCount].pos.y <= 650.0f)
				{
					g_aEnemy[nCount].move.x = 0.0f;
					g_aEnemy[nCount].move.y = 5.0f;
				}
				if (g_aEnemy[nCount].pos.y >= 660.0f)
				{
					g_aEnemy[nCount].move.x = -5.0f;
					g_aEnemy[nCount].move.y = 0.0f;
				}
				
			}

			if (g_aEnemy[nCount].EncounterState != ENEMYSTATE_ENCOUNTER_FALSE)
			{//�v���C���[�������ꍇ
				g_aEnemy[nCount].nChaseCounter--;

				if (g_aEnemy[nCount].nChaseCounter <= 0)
				{
					if (g_aEnemy[nCount].nPatternAnim == 0)
					{
						//�v���C���[�������Ȃ���Ԃɂ���
						g_aEnemy[nCount].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
						g_aEnemy[nCount].nChaseCounter = 0;
					}
					
				}
			}

			
			if (g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT && g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{//�����̏ꍇ
				g_aEnemy[nCount].move.y += 0.5f;				//�ړ��ʂ̍X�V
			}
			if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART ||
				g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
			{
				g_aEnemy[nCount].move.y -= 0.5f;
			}

			//�v���C���[�̈ʒu�̍X�V
			g_aEnemy[nCount].pos.x += g_aEnemy[nCount].move.x;
			g_aEnemy[nCount].pos.y += g_aEnemy[nCount].move.y;

			if (g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{
				// �u���b�N�̓����蔻��
					nCollision = BlockInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].LastPos, &g_aEnemy[nCount].move, 40.0f, 40.0f);

				if (nCollision == 1 || nCollision == 4)
				{//���n�̏ꍇ
					g_aEnemy[nCount].MoveState = MOVESTATE_LANDED;
				}

				else if (nCollision == 2 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT)
				{//�����瓖����ꍇ
					g_aEnemy[nCount].MoveState = MOVESTATE_FALLING;
				}

				else if (nCollision == 3 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT)
				{
					g_aEnemy[nCount].MoveState = MOVESTATE_FALLING;
				}

				//�R�E�����X���C���̏ꍇ�A�u���b�N�ɓ�����Ə�ɍs��
				if (g_aEnemy[nCount].move.y != 0.0f && g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
				{
					g_aEnemy[nCount].move.y = 0.0f;
				}
				if (g_aEnemy[nCount].pos.x == g_aEnemy[nCount].LastPos.x && g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT && g_aEnemy[nCount].EncounterState != ENEMYSTATE_ENCOUNTER_LOST)
				{
					g_aEnemy[nCount].move.y = -2.0f;
				}

				nCollision = BlockInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].LastPos, &g_aEnemy[nCount].move, -40.0f, 40.0f);

				if (nCollision == 3 && g_aEnemy[nCount].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE ||
					g_aEnemy[nCount].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCount].nPatternAnim == 0 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT)
				{//�u���b�N���痎���Ȃ��悤��
					g_aEnemy[nCount].move.x *= -1;
				}

				nCollision = WaterInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].move, (45.0f + (g_aEnemy[nCount].move.x * g_aEnemy[nCount].nDirection)), 40.0f);

				if (nCollision == 1 && g_aEnemy[nCount].nType != ENEMYTYPE_SLIMEBAT && g_aEnemy[nCount].EncounterState != ENEMYSTATE_ENCOUNTER_TRUE ||
					nCollision == 1 && g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
				{//���ɓ���Ȃ��悤��
					g_aEnemy[nCount].pos.x -= g_aEnemy[nCount].move.x * g_aEnemy[nCount].nDirection;		//�̔����ȉ����ɂ�������A�����o��
					g_aEnemy[nCount].move.x *= -1;															//�������t�ɂ���

					if (g_aMemoryInteraction[nCount] == 0)
					{
						g_aMemoryInteraction[nCount] = 1;
					}
					else
					{
						g_aEnemy[nCount].pos.x += 5.0f * g_aEnemy[nCount].nDirection;
						g_aEnemy[nCount].move.x *= -1;
					}
					
				}
				else
				{
					g_aMemoryInteraction[nCount] = 0;
				}

				nCollision = WaterInteraction(&g_aEnemy[nCount].pos, &g_aEnemy[nCount].move, 0.0f, 40.0f);

				if (nCollision == 1)
				{//�̔����ȏ㐅�ɂ���ꍇ
					if (g_aEnemy[nCount].nType != ENEMYTYPE_CARD_DIAMOND && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_HEART &&
						g_aEnemy[nCount].nType != ENEMYTYPE_CARD_CLUB && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_SPADE)
					{
						PlaySound(SOUND_LABEL_SE_WATER);							//���̉����Đ�
						g_aEnemy[nCount].state = ENEMYSTATE_DEATH;					//���񂾏�Ԃɂ���
						//g_aEnemy[nCount].move.x *= -1;
					}
					
				}
			}
			
			if (g_aEnemy[nCount].nType != ENEMYTYPE_CARD_DIAMOND && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_HEART &&
				g_aEnemy[nCount].nType != ENEMYTYPE_CARD_CLUB && g_aEnemy[nCount].nType != ENEMYTYPE_CARD_SPADE)
			{
				//���[�v����
				WarpEnemy(nCount);
			}

			//���_���W�̍X�V
			if (g_aEnemy[nCount].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCount].nType == ENEMYTYPE_GREENSLIME || g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
			{//�X���C���̏ꍇ
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_MIMIC)
			{//�~�~�b�N�̏ꍇ
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y - 40.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 20.0f, g_aEnemy[nCount].pos.y, 0.0f);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART ||
				g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
			{//�J�[�h�̏ꍇ
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 25.0f, g_aEnemy[nCount].pos.y - 50.0f, 0.0f);
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 25.0f, g_aEnemy[nCount].pos.y - 50.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x + 25.0f, g_aEnemy[nCount].pos.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCount].pos.x - 25.0f, g_aEnemy[nCount].pos.y, 0.0f);
			}

			//�����̍X�V
			if (g_aEnemy[nCount].move.x < 0 && g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{//������
				g_aEnemy[nCount].nDirection = -1;
			}
			else if (g_aEnemy[nCount].move.x > 0 && g_aEnemy[nCount].state != ENEMYSTATE_DEATH)
			{//�E����
				g_aEnemy[nCount].nDirection = 1;
			}

			//�A�j���[�V��������
			if (g_aEnemy[nCount].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCount].nType == ENEMYTYPE_GREENSLIME || g_aEnemy[nCount].nType == ENEMYTYPE_SLIMEBAT)
			{
				SlimeAnimation(nCount);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_MIMIC)
			{
				MimicAnimation(nCount);
			}
			else if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND ||
				g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
			{
				CardAnimation(nCount);
			}

			if (g_aDamage[nCount] > 0)
			{
				g_aDamage[nCount]--;
			}

			if (pPlayer->pos.x - (PLAYER_WIDTH * 0.5f)< g_aEnemy[nCount].pos.x && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x&&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y ||
				pPlayer->pos.x - (PLAYER_WIDTH * 0.5f) < g_aEnemy[nCount].pos.x && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x&&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight ||
				pPlayer->pos.x - (PLAYER_WIDTH * 0.5f)< g_aEnemy[nCount].pos.x && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x &&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y ||
				pPlayer->pos.x - (PLAYER_WIDTH * 0.5f) < g_aEnemy[nCount].pos.x  && pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) > g_aEnemy[nCount].pos.x&&
				pPlayer->pos.y > g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCount].pos.y - g_aEnemy[nCount].fHeight)
			{//�v���C���[�ɓ���������
				if (pPlayer->state != PLAYERSTATE_DAMAGE && g_aEnemy[nCount].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && pPlayer->state != PLAYERSTATE_DEATH)
				{//�v���C���[��Ԃ̊m�F
					AddScore(-250);								//�X�R�A��������
					pPlayer->nCounterState = 180;				//��ԃJ�E���^�[�̐ݒ�
					pPlayer->state = PLAYERSTATE_DAMAGE;		//�v���C���[�̏�Ԃ��_���[�W��Ԃɂ���
					SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_MINUS250);

					if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND ||
						g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
					{//�_���[�W�T�E���h���Đ�����
						PlaySound(SOUND_LABEL_SE_SLASH);
					}
					else
					{
						PlaySound(SOUND_LABEL_SE_NORMALDAMAGE);
					}

					if (g_aEnemy[nCount].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_DIAMOND ||
						g_aEnemy[nCount].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCount].nType == ENEMYTYPE_CARD_SPADE)
					{//�m�b�N�o�b�N�̏���
						pPlayer->move.x = 15.0f * g_aEnemy[nCount].nDirection;
					}
				}
			}
			

			//�O��̈ʒu�̍X�V
			g_aEnemy[nCount].LastPos = g_aEnemy[nCount].pos;

		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();	

}

//�G�̕`�揈��
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̏��ւ̃|�C���^
	int nCntEnemy;				//�����J�E���g����ϐ���錾����

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_MIMIC)
			{
				pDevice->SetTexture(0, g_apTextureMimic);
			}
			else if(g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_DIAMOND || 
				g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_SPADE)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureCard);
			}
			else
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_apTextureSlime[0]);
			}
			

			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
	
}

//�G�̐ݒ�
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE nType)
{
	int nCntEnemy;		//�����J�E���g����ϐ���錾����

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̊e�X�e�[�^�X��ݒ肷��
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�G�̈ʒu
			g_aEnemy[nCntEnemy].pos = pos;
			//�G�̑O��̈ʒu�̐ݒ�
			g_aEnemy[nCntEnemy].LastPos = pos;
			//�G�̈ړ���
			g_aEnemy[nCntEnemy].move = move;
			//�G�̏��
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			//���
			g_aEnemy[nCntEnemy].nType = nType;
			//��ԃJ�E���^�[
			g_aEnemy[nCntEnemy].nCounterState = 0;
			//��
			if (g_aEnemy[nCntEnemy].nType < 3)
			{
				g_aEnemy[nCntEnemy].fWidth = 20.0f;
			}
			else if (g_aEnemy[nCntEnemy].nType == 3)
			{
				g_aEnemy[nCntEnemy].fWidth = 15.0f;
			}

			//�g�p����Ă���ɂ���
			g_aEnemy[nCntEnemy].bUse = true;

			//���_�̐ݒ�
			pVtx[1].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y - 40.0f, pos.z);
			pVtx[0].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y - 40.0f, pos.z);
			pVtx[3].pos = D3DXVECTOR3(pos.x + 20.0f, pos.y, pos.z);
			pVtx[2].pos = D3DXVECTOR3(pos.x - 20.0f, pos.y, pos.z);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.125f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.125f, 0.125f);
			pVtx[0].tex = D3DXVECTOR2(0.125f, 0.0f);

			if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_SLIMEBAT || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_BLUESLIME || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_GREENSLIME)
			{
				g_aEnemy[nCntEnemy].MoveState = MOVESTATE_LANDED;

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			}
			else if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_MIMIC)
			{
				pVtx[1].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y - 50.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y - 50.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 25.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 25.0f, pos.y, pos.z);

				pVtx[3].tex = D3DXVECTOR2(0.0f, 0.25f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f, 0.25f);
				pVtx[0].tex = D3DXVECTOR2(0.25f, 0.0f);
			}
			else if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_DIAMOND ||
				g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_SPADE)
			{
				pVtx[1].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y - 80.0f, pos.z);
				pVtx[0].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y - 80.0f, pos.z);
				pVtx[3].pos = D3DXVECTOR3(pos.x + 30.0f, pos.y, pos.z);
				pVtx[2].pos = D3DXVECTOR3(pos.x - 30.0f, pos.y, pos.z);

				g_aEnemy[nCntEnemy].MoveState = MOVESTATE_LANDED;

				//�J�[�h�G�̃e�N�X�`�����W�̐ݒ�
				switch (g_aEnemy[nCntEnemy].nType)
				{
				case ENEMYTYPE_CARD_HEART:
					pVtx[3].tex = D3DXVECTOR2(0.043f, 0.59f);
					pVtx[1].tex = D3DXVECTOR2(0.043f, 0.53f);
					pVtx[2].tex = D3DXVECTOR2(0.083f, 0.59f);
					pVtx[0].tex = D3DXVECTOR2(0.083f, 0.53f);
					break;

				case ENEMYTYPE_CARD_DIAMOND:
					pVtx[3].tex = D3DXVECTOR2(0.5f, 0.625f);
					pVtx[1].tex = D3DXVECTOR2(0.5f, 0.5f);
					pVtx[2].tex = D3DXVECTOR2(0.625f, 0.625f);
					pVtx[0].tex = D3DXVECTOR2(0.625f, 0.5f);
					break;

				case ENEMYTYPE_CARD_CLUB:
					pVtx[3].tex = D3DXVECTOR2(0.0f, 0.75f);
					pVtx[1].tex = D3DXVECTOR2(0.0f, 0.625f);
					pVtx[2].tex = D3DXVECTOR2(0.125f, 0.75f);
					pVtx[0].tex = D3DXVECTOR2(0.125f, 0.625f);
					break;

				case ENEMYTYPE_CARD_SPADE:
					pVtx[3].tex = D3DXVECTOR2(0.5f, 0.75f);
					pVtx[1].tex = D3DXVECTOR2(0.5f, 0.625f);
					pVtx[2].tex = D3DXVECTOR2(0.625f, 0.75f);
					pVtx[0].tex = D3DXVECTOR2(0.625f, 0.625f);
					break;
				}
				
			}

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//���[�v����
void WarpEnemy(int nCntEnemy)
{
	Player*pPlayer;					//�v���X���ւ̃|�C���^

	pPlayer = GetPlayer();			//�v���X���̎擾

	if (g_aEnemy[nCntEnemy].pos.x >= SCREEN_WIDTH - 30.0f && g_aEnemy[nCntEnemy].move.x > 0)
	{//��ʂ̉E������o���ꍇ
		
		if (g_aEnemy[nCntEnemy].MoveState == MOVESTATE_LANDED)
		{
			g_aEnemy[nCntEnemy].move.x *= -1.0f;
		}
		else
		{
			g_aEnemy[nCntEnemy].pos.x = -20.0f;
		}
	}
	if (g_aEnemy[nCntEnemy].pos.x <= 30.0f && g_aEnemy[nCntEnemy].move.x < 0)
	{//��ʂ̍�������o���ꍇ
		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fWidth <= 0.0f)
		{//�G�����ɗ������ꍇ
			AddScore(500);								//�X�R�A�����Z����
			g_aEnemy[nCntEnemy].bUse = false;			//�G���g�p����Ă��Ȃ���Ԃɂ���
			SetSChange(D3DXVECTOR3(pPlayer->pos.x - (50.0f * pPlayer->nDirectionMove), pPlayer->pos.y - PLAYER_HEIGHT, 0.0f), D3DXVECTOR3(pPlayer->move.x, pPlayer->move.y, 0.0f), 0, CHANGEVALUE_PLUS500);
		}

		if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_DEATH)
		{//���̏�Ԃ̏ꍇ
			if (g_aEnemy[nCntEnemy].MoveState == MOVESTATE_LANDED)
			{
				g_aEnemy[nCntEnemy].move.x *= -1.0f;
			}
			else
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH + 20.0f;
			}
		}
		
	}
	/*if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT - 25.0f)
	{
		g_aEnemy[nCntEnemy].pos.y = SCREEN_HEIGHT - 25.0f;
		g_aEnemy[nCntEnemy].MoveState = MOVESTATE_LANDED;
	}*/
}

//�G�̃A�j���[�V��������
void SlimeAnimation(int nCntEnemy)
{
	Player*pPlayer;							//�v���X���ւ̃|�C���^

	pPlayer = GetPlayer();					//�v���C���[���̎擾

	g_aEnemy[nCntEnemy].nCountAnim++;		//�A�j���[�V�����J�E���^�[�̍X�V

	switch (g_aEnemy[nCntEnemy].nType)
	{
		//==================================================================================================================================================================
		//															�X���C��
	case ENEMYTYPE_BLUESLIME:

		switch (g_aEnemy[nCntEnemy].EncounterState)
		{
		case ENEMYSTATE_ENCOUNTER_FALSE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:

				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nPatternAnim++;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				break;

			case 1:

				g_aEnemy[nCntEnemy].move.x = 2.0f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 10)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}


			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_TRUE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 1:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].move.x = 6.0f * g_aEnemy[nCntEnemy].nDirection;
					g_aEnemy[nCntEnemy].move.y = -8.0f;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 2:
				
				if (g_aEnemy[nCntEnemy].nCountAnim >= 12)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 3:
				g_aEnemy[nCntEnemy].move.x -= 0.19f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 4:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 5:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}
			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 4, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_LOST:

			g_aEnemy[nCntEnemy].move.x = 0.0f;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;

			if (g_aEnemy[nCntEnemy].nCountAnim % 30 == 29)
			{//���ʂ̈ړ�
				g_aEnemy[nCntEnemy].nDirection *= -1;
			}
			if (g_aEnemy[nCntEnemy].nCountAnim >= 120)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
			}

			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.126f);

			break;
		}
		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH)
		{
			g_aEnemy[nCntEnemy].nDirection = 1;

			if (g_aEnemy[nCntEnemy].nCountAnim % 15 == 14)
			{//���ʂ̈ړ�
				if (g_aEnemy[nCntEnemy].nPatternAnim == 1)
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 2;
				}
				else
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 1;
				}
			}
			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 4, 0.125f, 0.126f);
		}

		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															�΃X���C��
	case ENEMYTYPE_GREENSLIME:

		switch (g_aEnemy[nCntEnemy].EncounterState)
		{
		case ENEMYSTATE_ENCOUNTER_FALSE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:

				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nPatternAnim++;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				break;

			case 1:

				g_aEnemy[nCntEnemy].move.x = 2.0f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 10)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}


			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_TRUE:

			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 0:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 1:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].move.x = 4.0f * g_aEnemy[nCntEnemy].nDirection;
					g_aEnemy[nCntEnemy].move.y = -6.0f;
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 2:

				if (g_aEnemy[nCntEnemy].nCountAnim >= 12)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 3:
				g_aEnemy[nCntEnemy].move.x -= 0.19f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 20)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 4:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 60)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 5:
				g_aEnemy[nCntEnemy].move.x = 0.0f;

				if (g_aEnemy[nCntEnemy].nCountAnim == 1)
				{
					SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y - (SLIME_HEIGHT * 0.5f), 0.0f),
						D3DXVECTOR3(4.0f * g_aEnemy[nCntEnemy].nDirection, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
					PlaySound(SOUND_LABEL_SE_NORMALBULLET);
				}
				else if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
				break;
			}
			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.126f);

			break;

		case ENEMYSTATE_ENCOUNTER_LOST:

			g_aEnemy[nCntEnemy].move.x = 0.0f;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;

			if (g_aEnemy[nCntEnemy].nCountAnim % 30 == 29)
			{//���ʂ̈ړ�
				g_aEnemy[nCntEnemy].nDirection *= -1;
			}
			if (g_aEnemy[nCntEnemy].nCountAnim >= 120)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
			}

			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.126f);

			break;
		}
		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH)
		{
			g_aEnemy[nCntEnemy].nDirection = 1;

			if (g_aEnemy[nCntEnemy].nCountAnim % 15 == 14)
			{//���ʂ̈ړ�
				if (g_aEnemy[nCntEnemy].nPatternAnim == 1)
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 2;
				}
				else
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 1;
				}
			}
			//�e�N�X�`�����W�̍X�V
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.126f);
		}

		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															�R�E�����X���C��
		case ENEMYTYPE_SLIMEBAT:

			switch (g_aEnemy[nCntEnemy].EncounterState)
			{
			case ENEMYSTATE_ENCOUNTER_FALSE:

				g_aEnemy[nCntEnemy].move.x = 2.0f * g_aEnemy[nCntEnemy].nDirection;

				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nPatternAnim++;

					if (g_aEnemy[nCntEnemy].nPatternAnim >= 2)
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 0;
					}

					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				//�e�N�X�`�����W�̍X�V
				UpdateEnemyTex(nCntEnemy, 6, 0.125f, 0.126f);

				break;
			case ENEMYSTATE_ENCOUNTER_TRUE:

				if ((g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x) * g_aEnemy[nCntEnemy].nDirection < 0)
				{
					g_aEnemy[nCntEnemy].move.x = 4.0f * g_aEnemy[nCntEnemy].nDirection;
				}
				else
				{
					g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
				}
				
				if (g_aEnemy[nCntEnemy].nCountAnim >= 10)
				{//���ʂ̈ړ�
					g_aEnemy[nCntEnemy].nPatternAnim++;

					if (g_aEnemy[nCntEnemy].nPatternAnim >= 2)
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 0;
					}

					g_aEnemy[nCntEnemy].nCountAnim = 0;
				}
				//�e�N�X�`�����W�̍X�V
				UpdateEnemyTex(nCntEnemy, 6, 0.125f, 0.126f);
				break;

			case ENEMYSTATE_ENCOUNTER_LOST:

				g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;

				break;
			}
			if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_DEATH)
			{
				g_aEnemy[nCntEnemy].nDirection = 1;

				if (g_aEnemy[nCntEnemy].nCountAnim % 15 == 14)
				{//���ʂ̈ړ�
					if (g_aEnemy[nCntEnemy].nPatternAnim == 1)
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 2;
					}
					else
					{
						g_aEnemy[nCntEnemy].nPatternAnim = 1;
					}
				}
				//�e�N�X�`�����W�̍X�V
				UpdateEnemyTex(nCntEnemy, 6, 0.125f, 0.126f);
			}

			break;
			//==================================================================================================================================================================
	}
}

//�~�~�b�N�̃A�j���[�V�����ƍU������
void MimicAnimation(int nCntEnemy)
{
	Player*pPlayer;		//�v���C���[�ւ̃|�C���^
	int nInteraction;	
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	MODE mode;			//���[�h

	mode = GetMode();			//���[�h�̎擾
	pPlayer = GetPlayer();		//�v���C���[���̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�~�~�b�N�̋߂��ɃG���^�[�L�[����������
	if (pPlayer->pos.x - (PLAYER_WIDTH * 0.5f) <= g_aEnemy[nCntEnemy].pos.x + 30.0f && pPlayer->pos.y > g_aEnemy[nCntEnemy].pos.y - 30.0f && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCntEnemy].pos.y - 30.0f ||
		pPlayer->pos.x + (PLAYER_WIDTH * 0.5f) >= g_aEnemy[nCntEnemy].pos.x + 30.0f && pPlayer->pos.y > g_aEnemy[nCntEnemy].pos.y - 30.0f && pPlayer->pos.y - PLAYER_HEIGHT < g_aEnemy[nCntEnemy].pos.y - 30.0f)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_TRUE;			//�U����Ԃɂ���
			g_aEnemy[nCntEnemy].nPatternAnim++;										//�p�^�[���̍X�V
			g_aEnemy[nCntEnemy].nCounterState = 60;									//��ԃJ�E���^�[�̐ݒ�
			g_aEnemy[nCntEnemy].nChaseCounter = 500;								//�U���J�E���^�[�̐ݒ�
		}
	}

	//���ʂ̏�Ԃɖ߂�
	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_LOST)
	{
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
	}

	//�A�j���[�V�����J�E���^�[��0�ɖ߂�
	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE)
	{
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].nCountAnim = 0;
	}

	//==================================================================================================================================================================
	//															�U����Ԃ̃A�j���[�V����
	else if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE)
	{
		if (g_aEnemy[nCntEnemy].nCounterState > 0)
		{
			g_aEnemy[nCntEnemy].nCounterState--;

			if (g_aEnemy[nCntEnemy].nCounterState == 30)
			{
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			else if (g_aEnemy[nCntEnemy].nCounterState == 0)
			{
				g_aEnemy[nCntEnemy].nPatternAnim = 0;
			}
		}
		if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x)
		{
			g_aEnemy[nCntEnemy].nDirection = 1;
		}
		else
		{
			g_aEnemy[nCntEnemy].nDirection = -1;
		}

		if (g_aEnemy[nCntEnemy].nCounterState <= 0)
		{
			g_aEnemy[nCntEnemy].move.x = 2.5f * g_aEnemy[nCntEnemy].nDirection;
			g_aEnemy[nCntEnemy].nCountAnim++;

			if (g_aEnemy[nCntEnemy].nCountAnim % 5 == 4)
			{
				g_aEnemy[nCntEnemy].nPatternAnim++;

				if (g_aEnemy[nCntEnemy].nPatternAnim >= 4)
				{
					g_aEnemy[nCntEnemy].nPatternAnim = 0;
				}
			}
		}

	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//																�u���b�N�̓����蔻��
	nInteraction = BlockInteraction(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].LastPos, &g_aEnemy[nCntEnemy].move, -45.0f, 60.0f);

	//�u���b�N���痎���Ȃ��悤��
	if (nInteraction == 3)
	{
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
		g_aEnemy[nCntEnemy].move.x = 0;
	}

	//==================================================================================================================================================================
	//															�U���J�E���^�[��0�ɂȂ�ƕ��ʂ̏�Ԃɖ߂�
	if (g_aEnemy[nCntEnemy].nChaseCounter <= 0)
	{
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
		g_aEnemy[nCntEnemy].move.x = 0;
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//																	�e�N�X�`�����W�̍X�V
	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nCounterState != 0 || g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE)
	{
		UpdateEnemyTex(nCntEnemy, 0, 0.25, 0.22);
	}
	else if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nCounterState == 0)
	{
		UpdateEnemyTex(nCntEnemy, 1, 0.25, 0.22);
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//														���_�J���[�̍X�V
	if (mode == MODE_GAME_BONUSSTAGE)
	{//�{�[�i�X�X�e�[�W�̏ꍇ

	 //==================================================================================================================================================================
	 //										�v���C���[������������A�^�����ɂ��āA�߂Â��ƕ��ʂɕ\������
		if (g_aEnemy[nCntEnemy].pos.y < pPlayer->pos.y + 10.0f && g_aEnemy[nCntEnemy].pos.y > pPlayer->pos.y - 100.0f &&
			g_aEnemy[nCntEnemy].pos.x < pPlayer->pos.x + 150.0f && g_aEnemy[nCntEnemy].pos.x > pPlayer->pos.x - 150.0f)
		{
			pVtx[(nCntEnemy * 4) + 0].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[(nCntEnemy * 4) + 1].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[(nCntEnemy * 4) + 2].col = D3DCOLOR_RGBA(150, 150, 150, 255);
			pVtx[(nCntEnemy * 4) + 3].col = D3DCOLOR_RGBA(150, 150, 150, 255);
		}
		else
		{
			pVtx[(nCntEnemy * 4) + 0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
			pVtx[(nCntEnemy * 4) + 1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
			pVtx[(nCntEnemy * 4) + 2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
			pVtx[(nCntEnemy * 4) + 3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		}
	}
	//==================================================================================================================================================================
	else
	{//���̏ꍇ
		pVtx[(nCntEnemy * 4) + 0].col = D3DCOLOR_RGBA(200, 200, 200, 255);
		pVtx[(nCntEnemy * 4) + 1].col = D3DCOLOR_RGBA(200, 200, 200, 255);
		pVtx[(nCntEnemy * 4) + 2].col = D3DCOLOR_RGBA(200, 200, 200, 255);
		pVtx[(nCntEnemy * 4) + 3].col = D3DCOLOR_RGBA(200, 200, 200, 255);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//�J�[�h�G�̍X�V����
void CardAnimation(int nCntEnemy)
{
	Player*pPlayer;		//�v���C���[���ւ̃|�C���^
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^
	int nSuit;			//�J�[�h�̎�ނ��i�[����ϐ�
	MODE mode;			//���[�h

	mode = GetMode();			//���[�h�̎擾
	pPlayer = GetPlayer();		//�v���C���[���̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//==================================================================================================================================================================
	//													�X�v���C�g�̍ŏ��̗�̐ݒ�
	switch (g_aEnemy[nCntEnemy].nType)
	{
	case ENEMYTYPE_CARD_HEART:
		nSuit = 0;
		break;
	case ENEMYTYPE_CARD_DIAMOND:
		nSuit = 1;
		break;
	case ENEMYTYPE_CARD_CLUB:
		nSuit = 0;
		break;
	case ENEMYTYPE_CARD_SPADE:
		nSuit = 1;
		break;
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//													���_�J���[�̍X�V
	if (mode == MODE_GAME_BONUSSTAGE)
	{//�{�[�i�X�X�e�[�W�̏ꍇ
		if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE)
		{
			pVtx[(nCntEnemy * 4) + 0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			pVtx[(nCntEnemy * 4) + 1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			pVtx[(nCntEnemy * 4) + 2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			pVtx[(nCntEnemy * 4) + 3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		}
		else
		{//���̏ꍇ
			pVtx[(nCntEnemy * 4) + 0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[(nCntEnemy * 4) + 1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[(nCntEnemy * 4) + 2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			pVtx[(nCntEnemy * 4) + 3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	//==================================================================================================================================================================
	//												�G�̓v���C���[�������邩�ǂ����𔻒肷�鏈��
	if ((pPlayer->pos.y >= g_aEnemy[nCntEnemy].pos.y - 50.0f && pPlayer->pos.y <= g_aEnemy[nCntEnemy].pos.y) ||
		(pPlayer->pos.y - PLAYER_HEIGHT >= g_aEnemy[nCntEnemy].pos.y - 50.0f && pPlayer->pos.y - PLAYER_HEIGHT <= g_aEnemy[nCntEnemy].pos.y))
	{
		if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_FALSE)
		{
			g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_TRUE;
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
			if (g_aEnemy[nCntEnemy].nDirection * (g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x) > 0)
			{
				g_aEnemy[nCntEnemy].nDirection *= -1;
			}
		}
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//												�v���C���[�������Ȃ��Ȃ�����A���ʂ̏�Ԃɖ߂�
	if (g_aEnemy[nCntEnemy].pos.x < 25.0f)
	{
		g_aEnemy[nCntEnemy].pos.x = 25.0f;
		g_aEnemy[nCntEnemy].move.x = 0.0f;
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
	}
	else if (g_aEnemy[nCntEnemy].pos.x > 1255.0f)
	{
		g_aEnemy[nCntEnemy].pos.x = 1255.0f;
		g_aEnemy[nCntEnemy].move.x = 0.0f;
		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
	}
	//==================================================================================================================================================================
	//==================================================================================================================================================================
	//																�A�j���V��������
	g_aEnemy[nCntEnemy].nCountAnim++;

	switch (g_aEnemy[nCntEnemy].EncounterState)
	{
		//==================================================================================================================================================================
		//															���ʂ̏�Ԃ̏�Ԃ̏ꍇ
	case ENEMYSTATE_ENCOUNTER_FALSE:

		if (nSuit == 1 && g_aEnemy[nCntEnemy].nPatternAnim < 4)
		{
			g_aEnemy[nCntEnemy].nPatternAnim = 4;
		}

		g_aEnemy[nCntEnemy].move.y = 0.0f;
		
		if (g_aEnemy[nCntEnemy].nCountAnim >= 45)
		{
			g_aEnemy[nCntEnemy].nCountAnim = 0;
			g_aEnemy[nCntEnemy].nPatternAnim++;

			if (g_aEnemy[nCntEnemy].nPatternAnim >= 3 + (nSuit * 4))
			{
				g_aEnemy[nCntEnemy].nPatternAnim = 0 + (nSuit * 4);
			}
		}
		//�G�̎�ނɂ���āA�G�̃e�N�X�`�����W�̍X�V
		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_HEART || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_DIAMOND)
		{
			UpdateEnemyTex(nCntEnemy, 4, 0.125f, 0.125f);
		}
		else if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_CLUB || g_aEnemy[nCntEnemy].nType == ENEMYTYPE_CARD_SPADE)
		{
			UpdateEnemyTex(nCntEnemy, 5, 0.125f, 0.125f);
		}
		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															�U����Ԃ̏ꍇ
	case ENEMYSTATE_ENCOUNTER_TRUE:

		switch (g_aEnemy[nCntEnemy].nPatternAnim)
		{
		case 0:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 45)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 1:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 2:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 3:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 30)
			{
				g_aEnemy[nCntEnemy].move.x = 5.0f * g_aEnemy[nCntEnemy].nDirection;
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 4:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				PlaySound(SOUND_LABEL_SE_CARDSWING);
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 5:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 6:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				PlaySound(SOUND_LABEL_SE_CARDSWING);
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim++;
			}
			break;

		case 7:
			if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
			{
				g_aEnemy[nCntEnemy].nCountAnim = 0;
				g_aEnemy[nCntEnemy].nPatternAnim = 4;

				if (g_aEnemy[nCntEnemy].pos == g_aEnemy[nCntEnemy].LastPos)
				{//�u���b�N�ɓ�����ƁA���ʂ̏�Ԃɖ߂�
					g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_LOST;
				}
			}
			break;
			//==================================================================================================================================================================
		}
		//==================================================================================================================================================================
		//															�e�N�X�`�����W�̍X�V
		switch (g_aEnemy[nCntEnemy].nType)
		{
		case ENEMYTYPE_CARD_HEART:
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_DIAMOND:
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_CLUB:
			UpdateEnemyTex(nCntEnemy, 2, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_SPADE:
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.125f);
			break;
		}
		break;
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															�U����̃A�j���[�V����
	case ENEMYSTATE_ENCOUNTER_LOST:

		if (g_aEnemy[nCntEnemy].nPatternAnim != 7 && g_aEnemy[nCntEnemy].nPatternAnim > 3)
		{
			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 4:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 5:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;

			case 6:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 7)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim++;
				}
				break;
			}
		}
		else
		{
			switch (g_aEnemy[nCntEnemy].nPatternAnim)
			{
			case 7:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim = 2;
				}
				break;
			case 2:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim--;
				}
				break;
			case 1:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].nCountAnim = 0;
					g_aEnemy[nCntEnemy].nPatternAnim--;
				}
				break;
			case 0:
				if (g_aEnemy[nCntEnemy].nCountAnim >= 15)
				{
					g_aEnemy[nCntEnemy].move.x = 0.0f;
					g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_FALSE;
				}
				break;

			}
		}
		//==================================================================================================================================================================
		//==================================================================================================================================================================
		//															�e�N�X�`�����W�̍X�V

		switch (g_aEnemy[nCntEnemy].nType)
		{
		case ENEMYTYPE_CARD_HEART:
			UpdateEnemyTex(nCntEnemy, 0, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_DIAMOND:
			UpdateEnemyTex(nCntEnemy, 1, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_CLUB:
			UpdateEnemyTex(nCntEnemy, 2, 0.125f, 0.125f);
			break;
		case ENEMYTYPE_CARD_SPADE:
			UpdateEnemyTex(nCntEnemy, 3, 0.125f, 0.125f);
			break;
		}
		break;
		//==================================================================================================================================================================
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//�G�̃e�N�X�`�����W�̍X�V
void UpdateEnemyTex(int nCntEnemy, int nSheetLine, float nU, float nV)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	
	if (g_aEnemy[nCntEnemy].nDirection <= 0)
	{//�������̏ꍇ
		//�e�N�X�`�����W�̐ݒ�
		pVtx[(nCntEnemy * 4) + 0].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 1].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 2].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 3].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
	}
	else if (g_aEnemy[nCntEnemy].nDirection > 0)
	{//�E�����̏ꍇ
		//�e�N�X�`�����W�̐ݒ�
		pVtx[(nCntEnemy * 4) + 1].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 0].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), 0.0f + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 3].tex = D3DXVECTOR2(nU + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
		pVtx[(nCntEnemy * 4) + 2].tex = D3DXVECTOR2(0.0f + (g_aEnemy[nCntEnemy].nPatternAnim * nU), nV + (nV * nSheetLine));
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//�v���C���[�������邩�ǂ���
void EnemyEncounter(int nCntEnemy, float Height)
{
	Player*pPlayer;					//�v���C���[�̏��ւ̃|�C���^

	//�v���C���[�̏��̎擾
	pPlayer = GetPlayer();

	if (pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - (0.9f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + (0.2f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.y - PLAYER_HEIGHT - 10.0f <= g_aEnemy[nCntEnemy].pos.y &&
		pPlayer->pos.y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight - 25.0f &&
		g_aEnemy[nCntEnemy].nDirection < 0 &&
		g_aEnemy[nCntEnemy].EncounterState != ENEMYSTATE_ENCOUNTER_TRUE ||
		pPlayer->pos.x <= g_aEnemy[nCntEnemy].pos.x + (0.9f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.x >= g_aEnemy[nCntEnemy].pos.x - (0.2f * g_aEnemy[nCntEnemy].fSight) &&
		pPlayer->pos.y - PLAYER_HEIGHT - 10.0f <= g_aEnemy[nCntEnemy].pos.y &&
		pPlayer->pos.y >= g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fHeight - 25.0f &&
		g_aEnemy[nCntEnemy].nDirection >= 0 &&
		g_aEnemy[nCntEnemy].EncounterState != ENEMYSTATE_ENCOUNTER_TRUE)
	{//�v���C���[�������邩�ǂ������肷��
		if (g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT &&
			g_aEnemy[nCntEnemy].nDirection > 0 &&
			pPlayer->pos.x < g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0 ||
			g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT &&
			g_aEnemy[nCntEnemy].nDirection < 0 &&
			pPlayer->pos.x > g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0)
		{//�J�E���^�[���O�łȂ�������A�A�j���[�V�������I�������A�v���C���[��ǂ�������
			g_aEnemy[nCntEnemy].nDirection *= -1;
			g_aEnemy[nCntEnemy].move.x *= -1;
		}

		g_aEnemy[nCntEnemy].EncounterState = ENEMYSTATE_ENCOUNTER_TRUE;				//�v���C���[��������Ԃɂ���
		g_aEnemy[nCntEnemy].nChaseCounter = 180;									//�ǂ�������J�E���^�[�̐ݒ�

		//�R�E�����X���C���̏ꍇ
		if (g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT)
		{
			g_aEnemy[nCntEnemy].nCountAnim = 0;											//�A�j���[�V�����J�E���^�[�̐ݒ�
			g_aEnemy[nCntEnemy].nPatternAnim = 0;
		}
	}

	if (g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nDirection > 0 &&
		pPlayer->pos.x < g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0 &&
		g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT ||
		g_aEnemy[nCntEnemy].EncounterState == ENEMYSTATE_ENCOUNTER_TRUE && g_aEnemy[nCntEnemy].nDirection < 0 &&
		pPlayer->pos.x > g_aEnemy[nCntEnemy].pos.x && g_aEnemy[nCntEnemy].nPatternAnim == 0 &&
		g_aEnemy[nCntEnemy].nType != ENEMYTYPE_SLIMEBAT)
	{
		g_aEnemy[nCntEnemy].nDirection *= -1;
		g_aEnemy[nCntEnemy].move.x *= -1;
	}
}

//�G�̏��̎擾
Enemy*GetEnemy(void)
{
	return &g_aEnemy[0];
}

//�G���o������
void SpawnEnemy(void)
{
	MODE mode;					//���[�h

	mode = GetMode();			//���[�h�̎擾

	if (mode == MODE_GAME_FIRSTSTAGE_1)
	{//�X�e�[�W�@1
		SetEnemy(D3DXVECTOR3(100.0f, 120.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.5f, 0.0f), ENEMYTYPE_BLUESLIME);
		SetEnemy(D3DXVECTOR3(400.0f, 125.0f, 0.0f), D3DXVECTOR3(1.0f, 0.5f, 0.0f), ENEMYTYPE_GREENSLIME);
		SetEnemy(D3DXVECTOR3(300.0f, 325.0f, 0.0f), D3DXVECTOR3(1.0f, 0.5f, 0.0f), ENEMYTYPE_GREENSLIME);
		SetEnemy(D3DXVECTOR3(850.0f, 325.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.5f, 0.0f), ENEMYTYPE_BLUESLIME);
		SetEnemy(D3DXVECTOR3(1000.0f, 555.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), ENEMYTYPE_SLIMEBAT);
		/*SetEnemy(D3DXVECTOR3(50.0f, 507.5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);
		SetEnemy(D3DXVECTOR3(500.0f, 167.5, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);*/
	}
	else if (mode == MODE_GAME_FIRSTSTAGE_2)
	{//�X�e�[�W�@2
		SetEnemy(D3DXVECTOR3(50.0f, 445.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);
		SetEnemy(D3DXVECTOR3(400.0f, 250.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), ENEMYTYPE_SLIMEBAT);
		SetEnemy(D3DXVECTOR3(850.0f, 260.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), ENEMYTYPE_SLIMEBAT);
		SetEnemy(D3DXVECTOR3(750.0f, 595.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), ENEMYTYPE_BLUESLIME);
		SetEnemy(D3DXVECTOR3(950.0f, 595.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), ENEMYTYPE_GREENSLIME);
		SetEnemy(D3DXVECTOR3(320.0f, 295.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), ENEMYTYPE_GREENSLIME);

	}
	else if (mode == MODE_GAME_FIRSTSTAGE_BOSS)
	{//�{�X�@1
		SetBoss(D3DXVECTOR3(640, 700.0f, 0.0f), 1);
	}
	else if (mode == MODE_GAME_BONUSSTAGE)
	{//�{�[�i�X�X�e�[�W
		SetEnemy(D3DXVECTOR3(50.0f, 507.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_MIMIC);
		SetEnemy(D3DXVECTOR3(30.0f, 125.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_HEART);
		SetEnemy(D3DXVECTOR3(1250.0f, 125.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_CLUB);
		SetEnemy(D3DXVECTOR3(30.0f, 290.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_SPADE);
		SetEnemy(D3DXVECTOR3(1250.0f, 480.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ENEMYTYPE_CARD_DIAMOND);

	}
	else if (mode == MODE_GAME_SECONDSTAGE_BOSS)
	{//�{�[�i�@2
		SetBoss(D3DXVECTOR3(640.0f, 670.0f, 0.0f), 2);
	}
}