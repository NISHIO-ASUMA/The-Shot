//======================
//
//�G�t�F�N�g����
//Author:ASUMA NISHIO
//
//======================

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

void InitEffect(void);				//�G�t�F�N�g�̏�����
void UninitEffect(void);			//�G�t�F�N�g�̏I��
void UpdateEffect(void);			//�G�t�F�N�g�̍X�V
void DrawEffect(void);				//�G�t�F�N�g�̕`��

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,float fRadius,int nLife,int nType);//�G�t�F�N�g�̐ݒ菈��

#endif
