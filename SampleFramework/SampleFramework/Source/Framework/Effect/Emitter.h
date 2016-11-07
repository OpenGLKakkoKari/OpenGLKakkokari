#pragma once
/*****************************************************************************/
/*!
@file   Emitter.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "../GameObject.h"
#include "EffectBillboard.h"
#include "EffectData.h"
#include "ParticleData.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Emitter : public GameObject
    {
    public:
        enum { PARTICLE_MAX = 32 };

        Emitter();
        virtual ~Emitter();

        void Init(){}
        void Uninit(){}
        void Update();
        void Reset();

        EffectBillboard**   pParticleList;
        EffectData          data;
        ParticleData        particle[PARTICLE_MAX];
        int                 cnt;
        int                 particleNum;
        int                 timer;
    };
}


/****************************** �w�b�_�����܂� *******************************/
