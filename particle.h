//---------------------------
//
//�p�[�e�B�N������
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//�v���g
void InitParticle(void);						//�p�[�e�B�N���̏�����
void UninitParticle(void);						//�p�[�e�B�N���̏I��
void UpdateParticle(void);						//�p�[�e�B�N���̍X�V
void DrawParticle(void);						//�p�[�e�B�N���̕`��
void SetParticle(D3DXVECTOR3 pos,D3DXCOLOR col);//�p�[�e�B�N���̐ݒ�

#endif
