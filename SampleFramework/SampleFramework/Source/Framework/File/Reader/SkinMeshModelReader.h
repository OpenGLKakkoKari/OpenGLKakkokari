#pragma once
/******************************************************************************
/*!
@file   SkinMeshModelReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �}�N����`
******************************************************************************/


#pragma warning(disable : 4996)


/*  �C���N���[�h
******************************************************************************/


#include "Reader.h"
#include "..\..\Mesh\SkinMeshModel.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class SkinMeshModelReader : public Reader
        {
        public:
            static SkinMeshModel* Load(const char *FileName);
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/