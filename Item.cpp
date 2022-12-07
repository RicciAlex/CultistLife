#include "Item.h"
#include "sound.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;			//���_�o�b�t�@�ւ̃|�C���^
ITEM g_aItem[MAX_ITEM];									//Item�^�̔z���錾����

void InitItem(void)
{
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCntItem;					//�����J�E���g����ϐ���錾����
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Cards.png",
		&g_pTextureItem);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//Bullet�^�̊e����������
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].EqPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nCntAnim = 0;
		g_aItem[nCntItem].nType = ITEMTYPE_NULL;
		g_aItem[nCntItem].bUse = false;

		//�e���W�̐ݒ�
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 25.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 25.0f, 0.0f);

		//rth�̐ݒ�
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.5f);


		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//�A�C�e���̏I������
void UninitItem(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//�A�C�e���̍X�V����
void UpdateItem(void)
{
	VERTEX_2D*pVtx;						//���_���ւ̃|�C���^
	Player*pPlayer;						//�v���C���[�ւ̃|�C���^
	int nCntItem;						//�J�E���g����ϐ���錾����

										//�v���C���[���̎擾
	pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
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

			//���_���W�̐ݒ�
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//�A�C�e���̕`�揈��
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;						//�J�E���g����ϐ���錾����

										//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureItem);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}

	}
}

//�A�C�e���̐ݒ菈��
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type)
{
	int nCntItem;		//�J�E���g����ϐ���錾����
	MODE mode;
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	mode = GetMode();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ

			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].EqPoint = pos;
			g_aItem[nCntItem].nCntAnim = 0;

			//���_���W�̐ݒ�
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);

			//�A�C�e���̎�ނ̐ݒ�
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

			

			//�g�p����Ă���ɂ���
			g_aItem[nCntItem].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}