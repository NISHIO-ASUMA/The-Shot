//---------------------------
//
//�G�̏���
//Author:NISHIO ASUMA
//
//---------------------------

#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "player.h"
#include "main.h"
#include "score.h"
#include "item.h"
#include "particle.h"
#include "effect.h"
#include "sound.h"

//�O���[�o��
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//���_�o�b�t�@�̃|�C���^
Enemy  g_aEnemy[MAX_ENEMY];								//�G�̏��
ENEMYTYPE g_pEnemy;										//�G�̃^�C�v�̗񋓌^���
int g_nNumEnemy;										//�J�E���g
int g_nEnemyTimer;										//�^�C�}�[


//=========================
//�G�̏���������
//=========================
void InitEnemy(void)
{
	int nCntEnemy;		//���[�J���ϐ�

	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�O���[�o���ϐ��̏�����
	g_nNumEnemy = 0;
	g_nEnemyTimer = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D* pVtx;//���_���̃|�C���^

	for (int nCnt = 0; nCnt < ENEMYTYPE_MAX; nCnt++)
	{
		//�G�̃e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			ENEMY_TEXTURE[nCnt],
			&g_apTextureEnemy[nCnt]);
	}

	//�\���̂̏�����
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//���W
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		g_aEnemy[nCntEnemy].nCounterState = 0;						//��ԃJ�E���^�[
		g_aEnemy[nCntEnemy].nLife = 0;								//�̗�
		g_aEnemy[nCntEnemy].state = {};								//���
		g_aEnemy[nCntEnemy].fAngle = 0.0f;							//�p�x
		g_aEnemy[nCntEnemy].fLength = 0.0f;							//�Ίp��
		g_aEnemy[nCntEnemy].nType = 0;								//���
		g_aEnemy[nCntEnemy].bUse = false;							//�g�p���Ă��邩�ǂ���
		g_aEnemy[nCntEnemy].nBulletCounter = 0;						//�G�̒e�̐��̏�����
		g_aEnemy[nCntEnemy].bRight = false;							//�G�̈ړ�����
		g_aEnemy[nCntEnemy].bTop = false;							//�G�̈ړ�����
		g_aEnemy[nCntEnemy].Threestate = {};						//�G��3��ނ̈ړ����
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();

}
//========================
//�G�̏I������
//========================
void UninitEnemy(void)
{
	StopSound();

	int nCntEnemy;		//���[�J���ϐ�

	//�e�N�X�`���̔j��
	for (nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (g_aEnemy[nCnt].bUse == true)
		{
			continue;
		}

		g_aEnemy[nCnt].bUse = false;							//�g�p���Ă��邩�ǂ���

	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

}
//=============================
//�G�̍X�V����
//=============================
void UpdateEnemy(void)
{
	int nCntEn = 0;		//���[�J���ϐ�

	VERTEX_2D* pVtx = {};	//���_���̃|�C���^

	//�v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEn = 0; nCntEn < MAX_ENEMY; nCntEn++)
	{
		if (g_aEnemy[nCntEn].bUse == true)
		{
			//�G���g�p����Ă�����
			switch (g_aEnemy[nCntEn].state)
			{
			case ENEMYSTATE_NORMAL:

				g_aEnemy[nCntEn].nBulletCounter++;		//�J�E���^�[�����Z

				//�v���C���[�̎g�p
				if (
					g_aEnemy[nCntEn].pos.x <= pPlayer->pos.x + MAX_ENEMY_SIZE &&
					g_aEnemy[nCntEn].pos.x >= pPlayer->pos.x - MAX_ENEMY_SIZE &&
					g_aEnemy[nCntEn].pos.y <= pPlayer->pos.y + MAX_ENEMY_SIZE &&
					g_aEnemy[nCntEn].pos.y >= pPlayer->pos.y - MAX_ENEMY_SIZE &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					PlaySound(SOUND_LABEL_HIT);

					HitPlayer(1);
					SetParticle(g_aEnemy[nCntEn].pos,D3DXCOLOR (1.0f,1.0f,1.0f,1.0f));
				}
	//===========================
	//1��ޖڂ̓G���g���Ă��鎞
	//===========================
				else if (g_aEnemy[nCntEn].nType == ENEMYTYPE_OWN)
				{
					g_aEnemy[nCntEn].move.y = 0.0f;

					if (g_aEnemy[nCntEn].bRight == true)
					{
						g_aEnemy[nCntEn].move.x = 5.0f;

						if (g_aEnemy[nCntEn].pos.x >= SCREEN_WIDTH - MAX_ENEMY_SIZE)
						{
							g_aEnemy[nCntEn].bRight = false;
						}
					}
					else
					{
						g_aEnemy[nCntEn].move.x = -5.0f;

						if (g_aEnemy[nCntEn].pos.x <= MAX_ENEMY_SIZE)
						{
							g_aEnemy[nCntEn].bRight = true;
						}

					}

					//�G�̒e�̐ݒ�
					if (g_aEnemy[nCntEn].nBulletCounter >= MAX_ANIMATION_TIME + 70)		//��莞�Ԃ��o�߂���
					{
						if (g_aEnemy[nCntEn].pos.y <= SCREEN_HEIGHT * 0.5f)
						{
							//pos���㔼��
							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 50, BULLETTYPE_ENEMY);

						}
						else if (g_aEnemy[nCntEn].pos.y >= SCREEN_HEIGHT * 0.5f)
						{
							//pos��������
							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, cosf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 50, BULLETTYPE_ENEMY);


						}
						g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
					}

				}

	//===========================
	//2��ޖڂ̓G���g���Ă��鎞
	//===========================
				else if (g_aEnemy[nCntEn].nType == ENEMYTYPE_TWO)
				{
					g_aEnemy[nCntEn].move.x = 0.0f;

					if (g_aEnemy[nCntEn].bTop == true)
					{
						g_aEnemy[nCntEn].move.y = -3.0f;

						if (g_aEnemy[nCntEn].pos.y <= 80.0f)
						{
							g_aEnemy[nCntEn].bTop = false;
						}
					}
					else
					{
						g_aEnemy[nCntEn].move.y = 3.0f;

						if (g_aEnemy[nCntEn].pos.y >= 650.0f)
						{
							g_aEnemy[nCntEn].bTop = true;
						}

					}

					//�G�̒e�̐ݒ�
					if (g_aEnemy[nCntEn].pos.x >= SCREEN_WIDTH * 0.5f)
					{
						if (g_aEnemy[nCntEn].nBulletCounter >= 50)		//��莞�Ԃ��o�߂���
						{
							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI * 0.5f) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI * 0.5f) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 65, BULLETTYPE_ENEMY);
							g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
						}

					}
					else
					{
						if (g_aEnemy[nCntEn].nBulletCounter >= 50)		//��莞�Ԃ��o�߂���
						{

							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + (-D3DX_PI * 0.5f)) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z + (D3DX_PI * 0.5f)) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 65, BULLETTYPE_ENEMY);
							g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
						}
					}

				}
	//===========================
	//3��ޖڂ̓G���g���Ă��鎞
	//===========================
				else if (g_aEnemy[nCntEn].nType == ENEMYTYPE_THREE)
				{
					switch (g_aEnemy[nCntEn].Threestate)
					{
					case 	ENEMY_TO_RIGHT:
						g_aEnemy[nCntEn].move.x = 5.0f;
						g_aEnemy[nCntEn].move.y = 0.0f;
						if (g_aEnemy[nCntEn].pos.x >= SCREEN_WIDTH - MAX_ENEMY_SIZE)
						{
							g_aEnemy[nCntEn].Threestate = ENEMY_TO_UNDER;
						}

						if (g_aEnemy[nCntEn].nBulletCounter >= 150)		//��莞�Ԃ��o�߂���
						{
							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 100, BULLETTYPE_ENEMY);
							g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
						}

						break;

					case 	ENEMY_TO_UNDER:
						g_aEnemy[nCntEn].move.x = 0.0f;
						g_aEnemy[nCntEn].move.y = 3.0f;
						if (g_aEnemy[nCntEn].pos.y >= 535.0f)
						{
							g_aEnemy[nCntEn].Threestate = ENEMY_TO_LEFT;
						}

						if (g_aEnemy[nCntEn].nBulletCounter >= 150)		//��莞�Ԃ��o�߂���
						{
							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI * 0.5f) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI * 0.5f) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 30, BULLETTYPE_ENEMY);
							g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
						}

						break;

					case 	ENEMY_TO_LEFT:
						g_aEnemy[nCntEn].move.x = -5.0f;
						g_aEnemy[nCntEn].move.y = 0.0f;
						if (g_aEnemy[nCntEn].pos.x <= MAX_ENEMY_SIZE)
						{
							g_aEnemy[nCntEn].Threestate = ENEMY_TO_TOP;
						}

						if (g_aEnemy[nCntEn].nBulletCounter >= 150)		//��莞�Ԃ��o�߂���
						{
							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 100, BULLETTYPE_ENEMY);
							g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
						}

						break;

					case 	ENEMY_TO_TOP:
						g_aEnemy[nCntEn].move.x = 0.0f;
						g_aEnemy[nCntEn].move.y = -3.0f;
						if (g_aEnemy[nCntEn].pos.y <= 130.0f)
						{
							g_aEnemy[nCntEn].Threestate = ENEMY_TO_RIGHT;
						}

						if (g_aEnemy[nCntEn].nBulletCounter >= 150)		//��莞�Ԃ��o�߂���
						{

							SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + (-D3DX_PI * 0.5f)) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z + (D3DX_PI * 0.5f)) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 30, BULLETTYPE_ENEMY);
							g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
						}

						break;

					default:
						break;
					}

				}
	//===========================
	//4��ޖڂ̓G���g���Ă��鎞
	//===========================
				else if (g_aEnemy[nCntEn].nType == ENEMYTYPE_FOUR)
				{
					g_aEnemy[nCntEn].move.x = 0.0f;
					g_aEnemy[nCntEn].move.y = 0.0f;

					if (g_aEnemy[nCntEn].pos.x >= SCREEN_WIDTH * 0.5f)
					{
						//�ʒu���E��̎�
						if (g_aEnemy[nCntEn].pos.y <= SCREEN_HEIGHT * 0.5f)
						{
							//�G�̒e�̐ݒ�
							if (g_aEnemy[nCntEn].nBulletCounter >= 100)		//��莞�Ԃ��o�߂���
							{
								SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI * (0.75f)) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI * (0.75f)) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 80, BULLETTYPE_ENEMY);
								g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
							}

						}
						else
						{
							//�E��
							//�G�̒e�̐ݒ�
							if (g_aEnemy[nCntEn].nBulletCounter >= 150)		//��莞�Ԃ��o�߂���
							{
								SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI * (0.25f)) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI * (0.25f)) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 80, BULLETTYPE_ENEMY);
								g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
							}

						}
					}
					else
					{
						//�ʒu���E��̎�
						if (g_aEnemy[nCntEn].pos.y <= SCREEN_HEIGHT * 0.5f)
						{
							//�G�̒e�̐ݒ�
							if (g_aEnemy[nCntEn].nBulletCounter >= 50)		//��莞�Ԃ��o�߂���
							{
								SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI * (-0.75f)) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI * (-0.75f)) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 80, BULLETTYPE_ENEMY);
								g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
							}

						}
						else
						{
							//�E��
							//�G�̒e�̐ݒ�
							if (g_aEnemy[nCntEn].nBulletCounter >= 200)		//��莞�Ԃ��o�߂���
							{
								SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI * (-0.25f)) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI * (-0.25f)) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 80, BULLETTYPE_ENEMY);
								g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
							}

						}

					}

				}

	//===========================
	//5��ޖڂ̓G���g���Ă��鎞
	//===========================
				else if (g_aEnemy[nCntEn].nType == ENEMYTYPE_FIVE)
				{
					float fspeed = (float)(rand() % 5) + 0.3f;

					//�v���C���[�̈ʒu���擾
					D3DXVECTOR3 playerPos = GetPlayer()->pos;

					//�v���C���[�Ƃ̋����̍������߂�
					D3DXVECTOR3 diff = playerPos - g_aEnemy[nCntEn].pos;

					//�p�x�̎Z�o
					float fAngle = atan2f(diff.x, diff.y);

					//�ړ��ʂ̍X�V
					g_aEnemy[nCntEn].move.x = sinf(fAngle) * fspeed;
					g_aEnemy[nCntEn].move.y = cosf(fAngle) * fspeed;

					//�ʒu���X�V
					g_aEnemy[nCntEn].pos.x += g_aEnemy[nCntEn].move.x;
					g_aEnemy[nCntEn].pos.y += g_aEnemy[nCntEn].move.y;


					//�G�̒e�̐ݒ�
					if (g_aEnemy[nCntEn].nBulletCounter >= 120)		//��莞�Ԃ��o�߂���
					{
						SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 70, BULLETTYPE_ENEMY);
						g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
					}

				}
				
	//===========================
	//6��ޖڂ̓G���g���Ă��鎞
	//===========================
				else if (g_aEnemy[nCntEn].nType == ENEMYTYPE_SIX)
				{
					g_aEnemy[nCntEn].move.y = 0.0f;
					//�^�C�}�[�����Z
					g_nEnemyTimer++;

					if (g_nEnemyTimer == 60)
					{
						g_aEnemy[nCntEn].pos.x = 1260.0f;
					}
					else if (g_nEnemyTimer == 120)
					{
						g_aEnemy[nCntEn].pos.x = 640.0f;

					}
					else if (g_nEnemyTimer == 180)
					{
						g_aEnemy[nCntEn].pos.x = 20.0f;

						g_nEnemyTimer = 0;	//�����l�ɖ߂�

					}

					//�G�̒e�̐ݒ�
					if (g_aEnemy[nCntEn].nBulletCounter >= 50)		//��莞�Ԃ��o�߂���
					{
						SetBullet(g_aEnemy[nCntEn].pos, D3DXVECTOR3(-sinf(g_aEnemy[nCntEn].rot.z + D3DX_PI) * 10.0f, -cosf(g_aEnemy[nCntEn].rot.z - D3DX_PI) * 10.0f, 0.0f), g_aEnemy[nCntEn].rot, 50.0f, 50.0f, 50, BULLETTYPE_ENEMY);
						g_aEnemy[nCntEn].nBulletCounter = 0;		//�J�E���^�[�����Z�b�g
					}

				}

				g_aEnemy[nCntEn].pos += g_aEnemy[nCntEn].move;		//�ʒu�̍X�V

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEn].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEn].pos.y - MAX_ENEMY_SIZE, 0.0f);//1�ڂ̒��_���
				pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEn].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEn].pos.y - MAX_ENEMY_SIZE, 0.0f);//2�ڂ̒��_���
				pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEn].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEn].pos.y + MAX_ENEMY_SIZE, 0.0f);//3�ڂ̒��_���
				pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEn].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEn].pos.y + MAX_ENEMY_SIZE, 0.0f);//4�ڂ̒��_���

				//���_�J���[�̐ݒ�(���ɖ߂�)
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEn].nCounterState--;
				if (g_aEnemy[nCntEn].nCounterState <= 0)
				{
					//�ʏ��Ԃɖ߂�
					g_aEnemy[nCntEn].state = ENEMYSTATE_NORMAL;
				}
				break;
			}
		}
		pVtx += 4;
	}

	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//===========================
//�G�̕`�揈��
//===========================
void DrawEnemy(void)
{
	int nCntEnemy;		//���[�J���ϐ�

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

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
			//�g�p����Ă�
			int nType = g_aEnemy[nCntEnemy].nType;
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[nType]);

			//�G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);//�n�_(0�Ԗځ`3�Ԗ�)

		}
	}

#ifdef _DEBUG

	//�G�̃f�o�b�O�\��
	DrawEnemySet(g_nNumEnemy);

#endif
}
//============================
//�G�̐ݒ菈��
//============================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;		//���[�J���ϐ�

	VERTEX_2D* pVtx;		//���_���̃|�C���^


	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//�g�p����ĂȂ�
			g_aEnemy[nCntEnemy].pos = pos;					//���W
			g_aEnemy[nCntEnemy].nType = nType;				//���
			g_aEnemy[nCntEnemy].bUse = true;				//�g�p����
			g_aEnemy[nCntEnemy].nLife = 0;					//�̗�
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;  //���

			//�G�̃^�C�v����
			if (ENEMYTYPE_OWN == nType)
			{
				//�P��ޖڂ��g�p����Ă���
				g_aEnemy[nCntEnemy].nLife = 2;

			}
			else if (ENEMYTYPE_TWO == nType)
			{
				//2��ޖڂ��g�p����Ă���
				g_aEnemy[nCntEnemy].nLife = 2;
			}
			else if (ENEMYTYPE_THREE == nType)
			{
				//3��ޖڂ��g�p����Ă���
				g_aEnemy[nCntEnemy].nLife = 3;
			}
			else if (ENEMYTYPE_FOUR == nType)
			{
				//6��ޖڂ��g�p����Ă���
				g_aEnemy[nCntEnemy].nLife = 4;
			}
			else if (ENEMYTYPE_FIVE == nType)
			{
				//5��ޖڂ��g�p����Ă���
				g_aEnemy[nCntEnemy].nLife = 1;
			}
			else if (ENEMYTYPE_SIX == nType)
			{
				//6��ޖڂ��g�p����Ă���
				g_aEnemy[nCntEnemy].nLife = 5;
			}

			//���_���̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE, 0.0f);	//1�ڂ̒��_���
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - MAX_ENEMY_SIZE, 0.0f);	//2�ڂ̒��_���
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE, 0.0f);	//3�ڂ̒��_���
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + MAX_ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + MAX_ENEMY_SIZE, 0.0f);	//4�ڂ̒��_���

			g_nNumEnemy++;	//�J�E���g�����Z

			break;
		}

		pVtx += 4;
	}
	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();

}
//============================
//�G�̃q�b�g����
//============================
void HitEnemy(int nCntEnemy, int nDamage)
{
	VERTEX_2D* pVtx;//���_���̃|�C�^

			//�v���C���[�̎擾
	Player* pPlayer = GetPlayer();

	g_aEnemy[nCntEnemy].nLife -= nDamage;		//�_���[�W�󂯂���̗͌��炷

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		g_aEnemy[nCntEnemy].bUse = false;
		//�p�[�e�B�N������
		SetParticle(g_aEnemy[nCntEnemy].pos,D3DXCOLOR (1.0f,0.2f,0.5f,1.0f));

		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_OWN)
		{
			AddScore(10000);//�X�R�A�����Z

			//�A�C�e������
			SetItem(g_aEnemy[nCntEnemy].pos,0);

		}
		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_TWO)
		{
			AddScore(20000);//�X�R�A�����Z

			//�A�C�e������
			SetItem(g_aEnemy[nCntEnemy].pos, 1);

		}
		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_THREE)
		{
			AddScore(30000);//�X�R�A�����Z

			//�A�C�e������
			SetItem(g_aEnemy[nCntEnemy].pos, 2);

		}
		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_FOUR)
		{
			AddScore(40000);//�X�R�A�����Z

			//�A�C�e������
			SetItem(g_aEnemy[nCntEnemy].pos, 3);

		}
		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_FIVE)
		{
			AddScore(50000);//�X�R�A�����Z

			//�A�C�e������
			SetItem(g_aEnemy[nCntEnemy].pos, 4);

		}
		if (g_aEnemy[nCntEnemy].nType == ENEMYTYPE_SIX)
		{
			AddScore(70000);//�X�R�A�����Z

			//�A�C�e������
			SetItem(g_aEnemy[nCntEnemy].pos, 5);
		}

		g_nNumEnemy--;		//�G�̑������J�E���g(�f�N�������g)

	}
	else
	{
		//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;		//�_���[�W���
		g_aEnemy[nCntEnemy].nCounterState = 5;				//�_���[�W��Ԃ̎���

		pVtx += 4 * nCntEnemy;

		//���_�J���[�̐ݒ�(�_���[�W�F)
		pVtx[0].col = D3DXCOLOR(0.0f,0.0f,0.7f,1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f,0.0f,0.7f,1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f,0.0f,0.7f,1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f,0.0f,0.7f,1.0f);

	}

	//�A�����b�N
	g_pVtxBuffEnemy->Unlock();

}
//=========================
//�G�̃J�E���g���擾
//=========================
int GetNumEnemy(void)
{
	return g_nNumEnemy;
}
//============================
//�G�̎擾
//============================
Enemy* GetEnemy(void)
{
	return &g_aEnemy[0];
}

