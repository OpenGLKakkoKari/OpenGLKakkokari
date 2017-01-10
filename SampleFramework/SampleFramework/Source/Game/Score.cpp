/*****************************************************************************/
/*!
@file   Score.cpp
@author Yuki Kogawara
@editor Daisuke Yokoyama -> 2016/12/5
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Score.h"
#include <math.h>
#include "GameScene.h"
#include "../Framework/Math/Math.h"
#include "../Framework/Manager.h"


using namespace Framework;
using namespace Framework::Math;
using namespace Game;


/*  ����
******************************************************************************/
#define SOCRE_LIMIT	(999)

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Score::Score()
{
	for (int nCnt = 0; nCnt < DIGIT_MAX; nCnt++)
	{
		pSprite[nCnt] = NULL;
	}

}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Score::~Score()
{
	for (int nCnt = 0; nCnt < DIGIT_MAX; nCnt++)
	{
		SAFE_DELETE(pSprite[nCnt]);
	}
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void Score::Init(void)
{
	m_score = SCORE;

	for (int nCnt = 0; nCnt < DIGIT_MAX; nCnt++)
	{
		pSprite[nCnt] = NumberSprite::Create(
			// ���W
			Vector2(1000.0f + nCnt*80.0f, 80.0f),
			// �傫��
			Vector2(80.0f, 80.0f),
			// �F
			Color(255, 255, 255, 255),
			// �e�N�X�`���t�@�C����
			"data/TEXTURE/number.png",
			// �ԍ�
			0);
	}

}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Score::Update(void)
{
	//���Z�e�X�g
	if (Manager::GetKeyboard()->Trigger('P'))
	{
		AddScore(10);
	}
}


/******************************************************************************
@brief  �X�R�A���Z����
******************************************************************************/
void Game::Score::AddScore(int add)
{
	//�X�R�A���Z
	m_score += add;
	if (m_score > SOCRE_LIMIT) {
		m_score = SOCRE_LIMIT;//���E�n����
	}

	//���̃X�R�A��ۑ�
	int score = m_score;

	//�\�����邽�߂̌v�Z
	for (int nCnt = DIGIT_MAX-1; nCnt >= 0; nCnt--)
	{
		//��ʌ�����Z�o���Ă����
		pSprite[nCnt]->SetNumber(score % 10);

		//��������炷
		score = score / 10;
	}
}


/******************************************************************************
@brief  �X�R�A���Z����
******************************************************************************/
float Game::Score::GetScore(void)
{
	return m_score;//�X�R�A�̒l��Ԃ�
}

/******************************** ���������܂� *******************************/
