#pragma once
/*****************************************************************************/
/*!
@file   DirectX.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "d3dx9.h"


/*  ���C�u���������N
******************************************************************************/


#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )


/*  �}�N����`
******************************************************************************/


#define FVF_VERTEX_3D   (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/*  �\���̒�`
******************************************************************************/


namespace DirectX
{
    typedef struct
    {
        D3DXVECTOR3 vtx;        // ���_���W
        D3DXVECTOR3 nor;        // �@���x�N�g��
        D3DCOLOR    col;        // ���_�J���[
        D3DXVECTOR2 tex;        // �e�N�X�`�����W
    }VERTEX_3D;
}


/****************************** �w�b�_�����܂� *******************************/