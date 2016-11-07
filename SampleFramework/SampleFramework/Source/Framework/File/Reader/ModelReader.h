#pragma once
/******************************************************************************
/*!
@file   ModelReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �}�N����`
******************************************************************************/


#pragma warning(disable : 4996)


/*  �C���N���[�h
******************************************************************************/


#include "Reader.h"
#include "..\..\Mesh\Mesh.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class ModelReader : public Reader
        {
        public:

            static Mesh* Load(const char *FileName);
        private:
            static Mesh* LoadX(const char *FileName);
            static Mesh* LoadOBJ(const char *FileName);

            static void LoadMTL(const char *FileName, int *pMatNum, Material** pMatList);

            // OBJ��p
            static int  GetMaterialIndex(const char* MaterialName);
            static char materialNameList[64][64];
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/