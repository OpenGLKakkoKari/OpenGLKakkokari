#pragma once
/******************************************************************************
/*!
@file   SkyboxModel.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Model.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class SkyboxModel : public Model
    {
    public:
        SkyboxModel();
        virtual ~SkyboxModel();

        virtual void Draw();

        static SkyboxModel* CreateSkybox(const Vector3& scale);
        static SkyboxModel* Load(const char* FileName)
        {
            SkyboxModel* model = new SkyboxModel;
            model->pMesh = Mesh::Load(FileName);
            return model;
        }
    };
}


/****************************** ヘッダここまで *******************************/
