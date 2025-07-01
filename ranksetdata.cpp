//==============================
//
//�����L���O����(����)
//Author:NISHIO ASUMA
//
//==============================

#include "ranksetdata.h"
#include "input.h"
#include "fade.h"
#include <stdio.h>
#include "score.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_pTextureRank =NULL;					//�e�N�X�`���̃|�C���^(����)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;				//���_�o�b�t�@�̃|�C���^(����)

LPDIRECT3DTEXTURE9 g_pTextureRankBG = NULL;					//�e�N�X�`���̃|�C���^(����)
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankBG = NULL;			//���_�o�b�t�@�̃|�C���^(����)


//=============================
//����������
//=============================
void InitRankingData(void)
{
	LPDIRECT3DDEVICE9 pDevice;	 //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;			 //���_���̃|�C���^

	//�e�N�X�`���̓ǂݍ���(����)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking.png",
		&g_pTextureRank);

	//�e�N�X�`���̓ǂݍ���(���ʂ̔w�i)
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ranking111.png",
		&g_pTextureRankBG);

	//===================
	//���ʂ̔w�i
	//===================

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankBG,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffRankBG->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);		//2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);		//3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);	//4�ڂ̒��_���

	//rhw�̐ݒ�(1.0f�ŌŒ�)
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffRankBG->Unlock();

	//======================
	//����
	//======================

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
	D3DPOOL_MANAGED,
	&g_pVtxBuffRank,
	NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W1�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(260.0f,150.0f,0.0f);		//1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(410.0f,150.0f,0.0f);		//2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(260.0f,530.0f,0.0f);		//3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(410.0f,530.0f,0.0f);		//4�ڂ̒��_���

	//rhw�̐ݒ�(1.0f�ŌŒ�)
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
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�A�����b�N
	g_pVtxBuffRank->Unlock();

}
//=============================
//�I������
//=============================
void UninitRankingData(void)
{
	//===============
	//����
	//===============

	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//===============
	//���ʂ̔w�i
	//===============

	//�e�N�X�`���̔j��
	if (g_pTextureRankBG != NULL)
	{
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pTextureRankBG != NULL)
	{
		g_pTextureRankBG->Release();
		g_pTextureRankBG = NULL;
	}

}
//=============================
//�X�V����
//=============================
void UpdateRankingData(void)
{
	//����(�|���S���o�����炢)
}
//=============================
//�`�揈��
//=============================
void DrawRankingData(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//===============
	//���ʂ̔w�i
	//===============

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankBG);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//===============
	//����
	//===============

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRank);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
