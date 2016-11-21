#pragma once
/******************************************************************************
/*!
@file   SkinMeshData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �\���̒�`
******************************************************************************/


namespace Framework
{
    struct SkinMeshDataHeader
    {
        int faceNum;            // �ʐ�
        int vertexNum;          // ���_��
        int materialNum;        // �}�e���A����
        int subsetNum;          // �T�u�Z�b�g��
        int boneNum;            // �{�[����
        int motionNum;          // ���[�V������
        int indexNum;           // �C���f�b�N�X��

        SkinMeshDataHeader() : 
            faceNum(0), vertexNum(0), materialNum(0), subsetNum(0),
            boneNum(0), motionNum(0), indexNum(0)
        {}
    };
}


/******************************* �w�b�_�����܂� ******************************/
