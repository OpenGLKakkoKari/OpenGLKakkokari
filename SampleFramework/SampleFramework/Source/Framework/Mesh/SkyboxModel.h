#pragma once
/******************************************************************************
/*!
@file   SkyboxModel.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Model.h"


/*  �N���X��`
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


/****************************** �w�b�_�����܂� *******************************/
