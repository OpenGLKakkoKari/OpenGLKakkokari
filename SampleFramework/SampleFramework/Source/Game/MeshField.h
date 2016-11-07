#pragma once
/******************************************************************************
/*!
@file   MeshField.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Framework\Texture\Texture.h"
#include "..\Framework\Mesh\Model.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
    class MeshField : public Framework::Model
    {
    public:
        MeshField(
            const char* fileName,
            int widthDiv,
            int heightDiv,
            const Framework::Vector2& size,
            float* pHeightMap);
        virtual ~MeshField();

        void Update();
        void Draw();

    private:
        int                 widthDiv;
        int                 heightDiv;

        int                 indexNum;
        Framework::Texture* pTexture;
    };
}


/******************************* �w�b�_�����܂� ******************************/
