#pragma once
/******************************************************************************
/*!
@file   Player.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "../../Framework/GameObject.h"
#include "../../Framework/Mesh/Model.h"
#include "../../Framework/Collision/OBB.h"
#include "CharacterController.h"


/*  �N���X��`
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
		//�W�����v�Ŏg���ϐ�
		int t_ ;		//����
		bool bJump_ ;	//�W�����v���Ă邩�ǂ���
    };
}


/******************************* �w�b�_�����܂� ******************************/
