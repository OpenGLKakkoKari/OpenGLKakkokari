/*****************************************************************************/
/*!
@file   EffectReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "EffectReader.h"
#include "../File.h"
#include "../../Error.h"

using Framework::File::File;
using Framework::File::EffectReader;
using Framework::Effect;
using Framework::Emitter;
using Framework::Error;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �G�t�F�N�g�ǂݍ���
@param  FileName    �t�@�C����
@return MotionModel �G�t�F�N�g���
******************************************************************************/

Effect* EffectReader::LoadEffect(const char *FileName)
{
    Effect* pEffect = NULL;
    EffectDataHeader    header;
    EffectData*         pEffectData;

    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return pEffect;
    }
    fileSize = file.GetSize();

    file.Read(&header, sizeof(EffectDataHeader), 1);
    pEffectData = new EffectData[header.nodeNum];
    file.Read(pEffectData, sizeof(EffectData)*Effect::EMITTER_MAX, 1);

    pEffect = new Effect;
    pEffect->isPlaying = true;
    pEffect->timer = 0;
    pEffect->startTime = header.frameStart;
    pEffect->endTime = header.frameEnd;

    pEffect->pEmitterList = new Emitter*[Effect::EMITTER_MAX];
    for (int i = 0; i < Effect::EMITTER_MAX; i++)
    {
        pEffect->pEmitterList[i] = new Emitter;
        pEffect->pEmitterList[i]->data = pEffectData[i];

        pEffect->pEmitterList[i]->pParticleList = new EffectBillboard*[Emitter::PARTICLE_MAX];
        for (int j = 0; j < Emitter::PARTICLE_MAX; j++)
        {
            pEffect->pEmitterList[i]->pParticleList[j] = EffectBillboard::Create(
                // ���W
                Vector3(0.0f, 0.0f, 0.0f),
                // �T�C�Y
                Vector2(0.0f, 0.0f),
                // �F
                Color(255, 255, 255, 255),
                // �r���{�[�h�̎��
                (Billboard::TYPE)pEffect->pEmitterList[i]->data.optionType,
                // �e�N�X�`���t�@�C����
                pEffect->pEmitterList[i]->data.fileName
                );
            pEffect->pEmitterList[i]->pParticleList[j]->SetUse(false);
            pEffect->pEmitterList[i]->pParticleList[j]->SetParent(pEffect->pEmitterList[i]);
            pEffect->pEmitterList[i]->pParticleList[j]->SetBlendType(0);
            pEffect->pEmitterList[i]->pParticleList[j]->SetDepthWriteEnable(false);
            pEffect->pEmitterList[i]->pParticleList[j]->SetDepthTestEnable(false);
        }
    }

    delete[] pEffectData;
    file.Close();

    return pEffect;
}

/******************************* �֐������܂� ********************************/
