#pragma once
/******************************************************************************
/*!
@file   EffectBillboard.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "../AnimationBillboard.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class EffectBillboard : public AnimationBillboard
    {
    public:
        EffectBillboard();
        virtual ~EffectBillboard();

        void Draw();

        static EffectBillboard* Create(const Vector3& pos, const Vector2& size, Color col, TYPE type, AnimationData animData, const char *FileName);

        void SetBlendType(int blendType){ this->blendType = blendType; }
        void SetDepthWriteEnable(bool canDepthWrite){ this->canDepthWrite = canDepthWrite; }
        void SetDepthTestEnable(bool canDepthTest){ this->canDepthTest = canDepthTest; }

    protected:
        int     blendType;
        bool    canDepthWrite;
        bool    canDepthTest;


    };
}


/****************************** �w�b�_�����܂� *******************************/
