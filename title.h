//---------------------------
//
//�^�C�g������
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef  _TITLE_H_
#define  _TITLE_H_

#include "main.h"
#include "input.h"

//�񋓌^(�^�C�g���̎��)
typedef enum
{
	TITLE_FIRST = 0,					//1�ڂ̃^�C�g��
	TITLE_SECOND,						//2�ڂ̃^�C�g��
	TITLE_MAX
}TITLE;

//�񋓌^(�^�C�g���̏��)
typedef enum
{
	TITLE_NONE = 0,						//�^�C�g�����(�ʏ���)
	TITLE_FLASH,						//�_�ŏ��
	STATE_MAX
}TITLESTATE;

//�v���g�^�C�v�錾	
void InitTitle(void);					 //�^�C�g���̏�����
void UninitTitle(void);					 //�^�C�g���̏I��
void UpdateTitle(void);					 //�^�C�g���̍X�V
void DrawTitle(void);					 //�^�C�g���̕`��
void SetTitle(int nType,D3DXVECTOR3 pos);//�^�C�g���̐ݒ�
void TitleFlash(int nType);				//�^�C�g���̓_��

#endif
