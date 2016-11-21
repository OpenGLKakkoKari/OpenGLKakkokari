#pragma once
/******************************************************************************
/*!
@file   Model.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\DrawObject.h"
#include "Mesh.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Model : public DrawObject
    {
    public:
        Model();
        virtual ~Model();

        virtual void Draw();
        virtual void SetTexture(int index, const char* fileName){ pMesh->SetTexture(index, fileName); }

        static Model* Load(const char *FileName);
        static Model* CreateBox(const Vector3& scale);

        Mesh* pMesh;
    };
}


/****************************** ヘッダここまで *******************************/
