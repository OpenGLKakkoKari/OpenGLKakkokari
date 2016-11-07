#pragma once
/******************************************************************************
/*!
@file   Bone.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Math\Matrix.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Bone
    {
    public:
        int    sibling;         // �Z��
        int    child;           // �q��
        int    parent;          // �e

        Matrix offset;          // �I�t�Z�b�g�s��
        Matrix advOffset;       // �{�[���I�t�Z�b�g�s��
        char   name[256];
    };
}


/****************************** �w�b�_�����܂� *******************************/