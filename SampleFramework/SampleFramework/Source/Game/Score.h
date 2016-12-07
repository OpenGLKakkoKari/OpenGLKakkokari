#pragma once
/******************************************************************************
/*!
@file   Score.h
@author Yuki Kogawara
@editor Daisuke Yokoyama -> 2016/12/5
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "../Framework/GameObject.h"
#include "../Framework/NumberSprite.h"


/*  クラス定義
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

		float m_score;		//現在のスコア
	};
}


/******************************* ヘッダここまで ******************************/
