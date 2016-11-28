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


/*  �N���X��`
******************************************************************************/


namespace Game
{
	class Player : public Framework::GameObject
    {
    public:
        Player();
        ~Player();

        void Init(){}
        void Uninit(){}
        void Update();

		Framework::Model* pModel_;
    };
}


/******************************* �w�b�_�����܂� ******************************/
