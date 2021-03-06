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

		Framework::Model* pModel_;
		Framework::OBB *pOBBPlayer_ ;
		//Framework::OBB *pOBBAttack_ ;

    };
}


/******************************* ヘッダここまで ******************************/
