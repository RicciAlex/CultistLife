//===================================================//
//                                                   //
//     �@  �A�N�V�����Q�[���A���[��ʃt�@�C��    �@  //  
//                Author: Ricci Alex				 //
//                                                   //
//===================================================//

//�C���N���[�h�t�@�C��
#include "arrow.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureArrow = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffArrow = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Arrow g_Arrow[MAX_ARROW];								//�A���[�^�̃O���[�o���ϐ���錾����
int g_nCntAnim;											//�A�j���[�V�����J�E���^�[
int g_nPAnim;											//�A�j���[�V�����p�^�[��

//�A���[�̏���������
void InitArrow(void)
{
	VERTEX_2D*pVtx;					//���_���ւ̃|�C���^
	int nCntArrow;					//�����J�E���g����ϐ���錾����
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//�O���[�o���ϐ��̏�����
	g_nCntAnim = 0;
	g_nPAnim = 1;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Arrow.png",
		&g_pTextureArrow);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ARROW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffArrow,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		//�A���[�^�̊e�p�����[�^�̏�����
		g_Arrow[nCntArrow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		g_Arrow[nCntArrow].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		g_Arrow[nCntArrow].nType = 0;								//���
		g_Arrow[nCntArrow].bUse = false;							//�g�p����Ă��邩�ǂ���

		//�e���W�̐ݒ�
		pVtx[1].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 25.0f, g_Arrow[nCntArrow].pos.y - 25.0f, 0.0f);
		pVtx[0].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 25.0f, g_Arrow[nCntArrow].pos.y - 25.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 25.0f, g_Arrow[nCntArrow].pos.y + 25.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 25.0f, g_Arrow[nCntArrow].pos.y + 25.0f, 0.0f);

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
	g_pVtxBuffArrow->Unlock();
}

//�A���[�̏I������
void UninitArrow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureArrow != NULL)
	{
		g_pTextureArrow->Release();
		g_pTextureArrow = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffArrow != NULL)
	{
		g_pVtxBuffArrow->Release();
		g_pVtxBuffArrow = NULL;
	}
}

//�A���[�X�V����
void UpdateArrow(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	g_nCntAnim++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == true)
		{//�e���g�p����Ă��Ȃ��ꍇ

			//�A�j���[�V��������
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
				//���W�̍X�V
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
				//���W�̍X�V
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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffArrow->Unlock();
}

//�A���[�̕`�揈��
void DrawArrow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntArrow;						//�J�E���g����ϐ���錾����

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffArrow, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureArrow);

	for (nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == true)
		{//�g�p����Ă���ꍇ
			//�l�p�`��`�悷��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntArrow * 4, 2);
		}
	}
}

//�A���[�̐ݒ菈��
void SetArrow(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type)
{
	int nCntArrow;		//�J�E���g����ϐ���錾����
	MODE mode;			//���[�h�^�̕ϐ�
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	mode = GetMode();	//���[�h�̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffArrow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntArrow = 0; nCntArrow < MAX_ARROW; nCntArrow++)
	{
		if (g_Arrow[nCntArrow].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ

			g_Arrow[nCntArrow].pos = pos;		//�ʒu

			g_Arrow[nCntArrow].move = move;		//�ړ���

			//���_���W�̐ݒ�
			pVtx[1].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
			pVtx[0].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y - 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x + 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Arrow[nCntArrow].pos.x - 20.0f, g_Arrow[nCntArrow].pos.y + 20.0f, 0.0f);

			//�A�C�e���̎�ނ̐ݒ�
			g_Arrow[nCntArrow].nType = type;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

			//�g�p����Ă���ɂ���
			g_Arrow[nCntArrow].bUse = true;

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffArrow->Unlock();
}