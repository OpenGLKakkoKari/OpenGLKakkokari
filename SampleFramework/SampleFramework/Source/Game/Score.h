#pragma once
/******************************************************************************
/*!
@file   Score.h
@author Yuki Kogawara
@editor Daisuke Yokoyama -> 2016/12/5
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "../Framework/GameObject.h"
#include "../Framework/NumberSprite.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
	class Score : public Framework::GameObject
	{
	public:
		enum { DIGIT_MAX = 3 };
		enum { SCORE = 0 };
		Score();
		virtual ~Score();

		virtual void Init();
		virtual void Uninit() {}
		virtual void Update();
		void AddScore (int);
		float GetScore(void);


	private:
		Framework::NumberSprite* pSprite[DIGIT_MAX];

		float m_score;		//���݂̃X�R�A
	};
}


/******************************* �w�b�_�����܂� ******************************/
