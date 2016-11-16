#pragma once
/******************************************************************************
/*!
@file   Character.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterStateManager.h"
#include "../../Framework/GameObject.h"
#include "../../Framework/Mesh/SkinMeshModel.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class OBB;
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

        void SetMotion(int motionIndex)             { pSkinMeshModel_->SetMotion(motionIndex);      }
        void SetFrame(int frame)                    { pSkinMeshModel_->SetFrame(frame);             }
        void NextFrame(int addFrame = 1)            { pSkinMeshModel_->NextFrame(addFrame);         }
        bool IsMotionEnd(int index)                 { return pSkinMeshModel_->IsMotionEnd(index);   }
        void SetState(CharacterState* pNewState)    { pState_->SetState(pNewState);                 }
        bool IsLanding()                            { return pos_.y <= 0.0f;                        }

        Framework::Vector3 traVec;
        Framework::Vector3 rotVec;
        Framework::Vector3 rotAim;
        Framework::Vector3 traUnit;
        Framework::Vector3 rotUnit;
        Framework::Vector3 traIner;
        Framework::Vector3 rotIner;
        Framework::OBB*             pOBB_;

    protected:
        Framework::SkinMeshModel*   pSkinMeshModel_;
        CharacterStateManager*      pState_;
    };
}


/******************************* ヘッダここまで ******************************/
