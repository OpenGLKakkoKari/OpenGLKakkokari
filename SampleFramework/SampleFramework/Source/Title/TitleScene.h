#pragma once
/******************************************************************************
/*!
@file   TitleScene.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "../Framework/Scene.h"

#include "TitleCamera.h"
#include "../Framework/Sprite.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
    class TitleScene : public Framework::Scene
    {
    public:
        TitleScene();
        ~TitleScene();

        void Init();
        void Uninit();
        void Update();

    private:
        static TitleCamera*             pCamera;
        static Framework::Sprite*       pSprite;
    };
}


/******************************* �w�b�_�����܂� ******************************/
