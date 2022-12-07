#include "scorechange.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureSChange = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSChange = NULL;			//���_�o�b�t�@�ւ̃|�C���^
ScoreChange g_SChange[MAX_SCHANGE];
int g_nCntAnim[MAX_SCHANGE];
int g_nPAnim[MAX_SCHANGE];

void InitSChange(void)
{
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCntSChange;					//�����J�E���g����ϐ���錾����
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ChangeValue.png",
		&g_pTextureSChange);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCHANGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSChange,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSChange->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		g_SChange[nCntSChange].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_SChange[nCntSChange].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_SChange[nCntSChange].nType = 0;
		g_SChange[nCntSChange].bUse = false;

		g_nCntAnim[nCntSChange] = 0;
		g_nPAnim[nCntSChange] = 1;

		//�e���W�̐ݒ�
		pVtx[1].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 25.0f, g_SChange[nCntSChange].pos.y - 25.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 25.0f, g_SChange[nCntSChange].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 25.0f, g_SChange[nCntSChange].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 25.0f, g_SChange[nCntSChange].pos.y + 25.0f, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);


		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSChange->Unlock();
}

//�A�C�e���̏I������
void UninitSChange(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureSChange != NULL)
	{
		g_pTextureSChange->Release();
		g_pTextureSChange = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSChange != NULL)
	{
		g_pVtxBuffSChange->Release();
		g_pVtxBuffSChange = NULL;
	}
}

void UpdateSChange(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSChange->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		if (g_SChange[nCntSChange].bUse == true)
		{//�e���g�p����Ă��Ȃ��ꍇ

			g_nCntAnim[nCntSChange]++;

			//���W�̍X�V
			pVtx[1].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);

			//���_�J���[�̐ݒ�
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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSChange->Unlock();
}

void DrawSChange(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntSChange;						//�J�E���g����ϐ���錾����

										//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSChange, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSChange);

	for (nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		if (g_SChange[nCntSChange].bUse == true)
		{
			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntSChange * 4, 2);
		}
	}
}

void SetSChange(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type, CHANGEVALUE Value)
{
	int nCntSChange;		//�J�E���g����ϐ���錾����
	MODE mode;
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	mode = GetMode();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSChange->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSChange = 0; nCntSChange < MAX_SCHANGE; nCntSChange++)
	{
		if (g_SChange[nCntSChange].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ

			g_SChange[nCntSChange].pos = D3DXVECTOR3(850.0f, 60.0f, 0.0f);

			g_SChange[nCntSChange].move = move;

			g_SChange[nCntSChange].value = Value;

			//���_���W�̐ݒ�
			pVtx[1].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y - 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x + 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_SChange[nCntSChange].pos.x - 30.0f, g_SChange[nCntSChange].pos.y + 30.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�A�C�e���̎�ނ̐ݒ�
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

			

			//�g�p����Ă���ɂ���
			g_SChange[nCntSChange].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSChange->Unlock();
}