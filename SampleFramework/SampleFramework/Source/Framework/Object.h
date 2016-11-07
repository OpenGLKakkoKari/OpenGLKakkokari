#pragma once
/******************************************************************************
/*!
@file   Object.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Texture\Texture.h"
#include "Math\Vector3.h"
#include "Math\Matrix.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Object
    {
    public:
        Object();
        virtual ~Object();

        void            SetPosition(const Vector3& pos) { pos_ = pos; }
        void            SetRotation(const Vector3& rad) { rot_ = rad; }
        void            SetScale(const Vector3& scale)  { scale_ = scale; }
        void            SetParent(Object* parent)       { parent_ = parent; }

        const Vector3&  GetPosition()                   { return pos_; }
        const Vector3&  GetRotation()                   { return rot_; }
        const Vector3&  GetScale()                      { return scale_; }
        void            GetMatrix(Matrix* pOut);

        void            SetUse(bool isUsed)             { isUsed_ = isUsed; }
        bool            IsUsed()                        { return isUsed_; }

        Vector3         pos_;
        Vector3         rot_;
        Vector3         scale_;

        Object*         parent_;

    protected:
        bool            isUsed_;
    };
}


/****************************** ヘッダここまで *******************************/
