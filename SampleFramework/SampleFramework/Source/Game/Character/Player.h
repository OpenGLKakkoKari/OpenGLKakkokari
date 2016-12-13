#pragma once
/******************************************************************************
/*!
@file   Player.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "../../Framework/GameObject.h"
#include "../../Framework/Mesh/Model.h"
#include "../../Framework/Collision/OBB.h"
#include "CharacterController.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
	class Player : public Framework::GameObject
    {
    public:
        Player();
        ~Player();

        void Init();
        void Uninit(){}
        void Update();
		void SetController(CharacterController* pController)
			{ pController_ = pController; }

		static Player* Create(int index);

		Framework::Model* pModel_;
		Framework::OBB *pOBBPlayer_ ;
		Framework::OBB *pOBBAttack_ ;
		CharacterController *pController_ ;

	private :
		//ジャンプで使う変数
		int t_ ;		//時間
		bool bJump_ ;	//ジャンプしてるかどうか
    };
}


/******************************* ヘッダここまで ******************************/
