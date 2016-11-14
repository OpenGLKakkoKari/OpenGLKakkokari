#pragma once
/******************************************************************************
/*!
@file   Motion.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\Math\Vector3.h"
#include "..\Math\Quaternion.h"
#include "..\Math\Matrix.h"


/*  構造体定義
******************************************************************************/


namespace Framework
{
    class Motion
    {
    public:
        enum
        {
            NEUTRAL = 0,    // ニュートラル
            WALKING,        // 歩き
            JUMPING,        // ジャンプ
            LANDING,        // 着地
            MELEE,          // 格闘
            SHOOTING,       // 射撃
            SKILL,          // スキル
            STUNNED,        // 気絶
            STANDING,       // 起き上がり

            MOTION_MAX,
        };

        struct MotionDataHeader
        {
            bool        loop;           // ループするかどうか
            int         keyframeNum;    // キーフレーム数
            int         frameMax;       // 最大フレーム
        };
        struct Key
        {
            Quaternion  rot;            // 回転
            Vector3     scale;          // 拡大
            Vector3     trans;          // 移動
        };
        struct KeyFrame
        {
            int     interval;       // キー間インターバル
            Key*    keyList;        // キー情報
        };

        Motion();
        ~Motion();

        void SetFrame(int frame) { this->frame = frame; }
        void NextFrame(int addFrameCnt);

        int         frame;          // フレーム
        bool        loop;           // ループするかどうか
        int         keyframeNum;    // 現在のキーフレーム
        int         frameMax;       // キーフレーム数
        KeyFrame*   keyframeList;   // キーフレームリスト

    };
}


/******************************* ヘッダここまで ******************************/
