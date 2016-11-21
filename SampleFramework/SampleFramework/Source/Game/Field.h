#pragma once
/******************************************************************************
/*!
@file   Field.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Framework\GameObject.h"
#include "MeshField.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
    class Field : public Framework::GameObject
    {
    public:
        Field(
            const char* fileName,
            int widthDiv,
            int heightDiv,
            const Framework::Vector2& size,
            float* pHeightMap);
        virtual ~Field();

        void Init(){}
        void Uninit(){}
        void Update();

        void SetPosition(const Framework::Vector3& pos){ pField->SetPosition(pos); }

    private:
        MeshField*          pField;
    };
}


/******************************* �w�b�_�����܂� ******************************/
