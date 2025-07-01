//---------------------------
//
//�G�̏���
//Author:NISHIO ASUMA
//
//---------------------------

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//�}�N��
#define MAX_ENEMY (128)				// �G�̍ő吔
#define MAX_ENEMY_SIZE (25.0f)		// �G�̃T�C�Y

//�G�̏�Ԃ̗񋓌^
typedef enum
{
	ENEMYSTATE_NORMAL = 0,			// �ʏ���
	ENEMYSTATE_DAMAGE,				// �_���[�W���
	ENEMYSTATE_MAX
}ENEMYSTATE;

//3�^�C�v�ڂ̓G�̗񋓌^
typedef enum
{
	ENEMY_TO_RIGHT = 0,
	ENEMY_TO_UNDER,
	ENEMY_TO_LEFT,
	ENEMY_TO_TOP,
	ENEMY_TO_MAX
}ENEMYTHREESTATE;

//�G�̎�ޏ��(�񋓌^)
typedef enum
{
	ENEMYTYPE_OWN = 0,	//1�Ԗ�
	ENEMYTYPE_TWO,		//2�Ԗ�
	ENEMYTYPE_THREE,	//3�Ԗ�
	ENEMYTYPE_FOUR,		//4�Ԗ�
	ENEMYTYPE_FIVE,		//5�Ԗ�
	ENEMYTYPE_SIX,		//�{�X
	ENEMYTYPE_MAX
}ENEMYTYPE;

static const char* ENEMY_TEXTURE[ENEMYTYPE_MAX] =   //�G�̃e�N�X�`���̐ݒ�
{
	"data\\TEXTURE\\enemy100.png",
	"data\\TEXTURE\\enemy101.png",
	"data\\TEXTURE\\enemy102.png",
	"data\\TEXTURE\\enemy103.png",
	"data\\TEXTURE\\enemy104.png",
	"data\\TEXTURE\\enemy105.png",
};

//�\����
typedef struct
{
	D3DXVECTOR3 pos;						//���W
	D3DXVECTOR3 move;						//�ړ���
	D3DXVECTOR3 rot;						//��]��
	ENEMYSTATE state;						//�G�̏��
	ENEMYTHREESTATE Threestate;				//3�^�C�v�ڂ̓G�̏��
	int nCounterState;						//��ԊǗ��J�E���^�[
	float fLength;							//�Ίp��
	float fAngle;							//�p�x
	int nType;								//�G�̎��
	bool bUse;								//�g�p���Ă��邩
	int nLife;								//�G�̗̑�
	int nBulletCounter;						//�G�̒e�̐����J�E���g
	bool bRight;							//�t���O
	bool bTop;								//�t���O
}Enemy;

//�v���g
void InitEnemy(void);						//�G�̏�����
void UninitEnemy(void);						//�G�̏I��
void UpdateEnemy(void);						//�G�̍X�V
void DrawEnemy(void);						//�G�̕`��
void SetEnemy(D3DXVECTOR3 pos,int nType);	//�G�̐ݒ菈��
void HitEnemy(int nCntEnemy, int nDamage);	//�G�̓����蔻��
Enemy* GetEnemy(void);						//������擾
int GetNumEnemy(void);						//�G�̑����̎擾

#endif

