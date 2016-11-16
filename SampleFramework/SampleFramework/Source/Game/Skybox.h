#pragma once
/******************************************************************************
/*!
@file   Skybox.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "../Framework/GameObject.h"
#include "../Framework/Mesh/SkyboxModel.h"

/*  クラス定義
******************************************************************************/


namespace Game
{
    class Skybox : public Framework::GameObject
    {
    public:
        Skybox();
        virtual ~Skybox();

        virtual void Init();
        virtual void Uninit(){}
        virtual void Update();

        virtual void SetTexture(const char* fileName){ pBox->SetTexture(0, fileName); }

        static Skybox* Create(const char* FileName);

    private:
        Framework::SkyboxModel* pBox;
    };
}


/****************************** ヘッダここまで *******************************/
