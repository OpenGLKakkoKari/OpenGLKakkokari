#pragma once
/******************************************************************************
/*!
@file   Character.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "../../Framework/GameObject.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class OBB;
    class SkinMeshModel;
    class StateManager;
}
namespace Game
{
    class Character : public Framework::GameObject
    {
    public:
        Character();
        ~Character();

        void Init();
        void Uninit();
        void Update();

        Framework::Vector3 traVec;
        Framework::Vector3 rotVec;
        Framework::Vector3 rotAim;
        Framework::Vector3 traUnit;
        Framework::Vector3 rotUnit;
        Framework::Vector3 traIner;
        Framework::Vector3 rotIner;

    protected:
        Framework::OBB*             pOBB;
        Framework::SkinMeshModel*   pSkinMeshModel;
        Framework::StateManager*    pState;
    };
}


/******************************* ヘッダここまで ******************************/
