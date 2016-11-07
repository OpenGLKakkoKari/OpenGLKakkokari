#pragma once
/******************************************************************************
/*!
@file   Camera.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Math\Matrix.h"
#include "GameObject.h"
#include "Viewport.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Camera : public GameObject
    {
    public:
        Camera();
        ~Camera();

        virtual void Init() = 0;
        virtual void Uninit() = 0;
        virtual void Update() = 0;

        void SetViewport(Viewport vp){ this->vp = vp; }

        Viewport vp;

        Vector3 Eye;
        Vector3 At;
        Vector3 Up;
    };

}


/******************************* ヘッダここまで ******************************/
