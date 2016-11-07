#pragma once
/******************************************************************************
/*!
@file   TitleCamera.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "../Framework/Camera.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
    class TitleCamera : public Framework::Camera
    {
    public:
        TitleCamera(){}
        ~TitleCamera(){}

        void Init(){}
        void Uninit(){}
        void Update(){}
    };

}


/******************************* ヘッダここまで ******************************/
