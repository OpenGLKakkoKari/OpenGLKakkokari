#pragma once
/*****************************************************************************/
/*!
@file   ParticleData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"
#include "..\Color.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    struct ParticleData
    {
        Vector3     pos;
        Vector3     rot;
        Vector2     scale;
        Vector3     vecTrans;
        Vector3     vecRot;
        Vector2     vecScale;
        Vector3     accelTrans;
        Vector3     accelRot;
        Vector2     accelScale;
        Color       nowColor;
        int       chgColorR;
        int       chgColorG;
        int       chgColorB;
        int       chgColorA;

        int         life;
        bool        isCreated;

        ParticleData() :
            pos(Vector3(0.0f, 0.0f, 0.0f)),
            rot(Vector3(0.0f, 0.0f, 0.0f)),
            scale(Vector2(0.0f, 0.0f)),
            vecTrans(Vector3(0.0f, 0.0f, 0.0f)),
            vecRot(Vector3(0.0f, 0.0f, 0.0f)),
            vecScale(Vector2(0.0f, 0.0f)),
            accelTrans(Vector3(0.0f, 0.0f, 0.0f)),
            accelRot(Vector3(0.0f, 0.0f, 0.0f)),
            accelScale(Vector2(0.0f, 0.0f)),
            nowColor(Color(0, 0, 0, 0)),
            chgColorR(0),
            chgColorG(0),
            chgColorB(0),
            chgColorA(0),
            life(0),
            isCreated(false)
        {}
    };
}


/****************************** ヘッダここまで *******************************/
