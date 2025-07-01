//---------------------------
//
//�p�[�e�B�N������
//Author:NISHIO ASUMA
//
//---------------------------

#include "particle.h"
#include "effect.h"

//�}�N��
#define MAX_PARTICLE (128)//�ő吔

//�\����
typedef struct
{
	D3DXVECTOR3 pos;		//���W
	int nLife;				//����
	bool bUse;				//�g�p����
	D3DXCOLOR col;			//�J���[
}Particle;

//�O���[�o��
Particle g_aParticle[MAX_PARTICLE];		//�p�[�e�B�N�����

//==========================
//�p�[�e�B�N���̏�����
//==========================
void InitParticle(void)
{
	//�\���̂̏�����
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].bUse = false;							//���g�p���
		g_aParticle[nCnt].nLife = 10;							//�̗�
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���W
		g_aParticle[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f); //�F

	}
}
//==========================
//�p�[�e�B�N���̏I��
//==========================
void UninitParticle(void)
{
	//����
}
//==========================
//�p�[�e�B�N���̍X�V
//==========================
void UpdateParticle(void)
{
	//���[�J���ϐ�
	int nCntParticle;
	D3DXVECTOR3 move;
	D3DXVECTOR3 pos;
	D3DXCOLOR col;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{
			//�p�[�e�B�N���̐���
			for (int nCntApper = 0; nCntApper < 2; nCntApper++)
			{
				//�ʒu�̐ݒ�
				pos = g_aParticle[nCntParticle].pos;

				//�ړ��ʂ̐ݒ�
				float fAngel = (float)(rand() % 629 - 314) / 100.0f;
				float fLength = ((float)(rand() % 60) / 10.0f + 0.7f);

				move.x = sinf(fAngel) * fLength;
				move.y = cosf(fAngel) * fLength;
				move.z = 0.0f;

				//�J���[�̐ݒ�
				col = D3DXCOLOR(0.6f, 0.4f,1.0f, 0.5f);

				//���a�̐ݒ�
				float fRadius = ((float)(rand() % 450) / 10.0f + 0.7f);

				//�����̐ݒ�
				int nLife = ((float)(rand() % 2000) / 10);

				//�G�t�F�N�g�̐ݒ�
				SetEffect(pos, D3DXVECTOR3 (move.x,move.y,move.z), col, fRadius, nLife,0);

			}

			g_aParticle[nCntParticle].nLife--;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{
				//���g�p���
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}
}
//==========================
//�p�[�e�B�N���̕`��
//==========================
void DrawParticle(void)
{
	//����
}
//==========================
//�p�[�e�B�N���̐ݒ菈��
//==========================
void SetParticle(D3DXVECTOR3 pos,D3DXCOLOR col)
{
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == false)
		{
			g_aParticle[nCntParticle].pos = pos;		//���W
			g_aParticle[nCntParticle].bUse = true;		//�g�p����
			g_aParticle[nCntParticle].nLife = 15;		//�̗�
			g_aParticle[nCntParticle].col = col;		//�F

			break;
		}
	}
}
