#pragma once
/******************************************************************************
/*!
@file   Model.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\DrawObject.h"
#include "Mesh.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Model : public DrawObject
    {
    public:
        Model();
        virtual ~Model();

        virtual void Draw();

        static Model* Load(const char *FileName);

        Mesh* pMesh;
    };
}


/****************************** �w�b�_�����܂� *******************************/