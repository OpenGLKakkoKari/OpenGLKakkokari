/*****************************************************************************/
/*!
@file   Emitter.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Emitter.h"
#include "../Manager.h"
#include "../Math/Random.h"


using namespace Framework;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/


Emitter::Emitter() : 
pParticleList(NULL), cnt(0), particleNum(0), timer(0)
{
    // �G�t�F�N�g���ōX�V����̂�
    // 2�d�X�V������邽�ߍX�V��OFF�ɂ���
    SetUse(false);
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Emitter::~Emitter()
{
    if (pParticleList)
    {
        for (int i = 0; i < PARTICLE_MAX; i++)
        {
            if (pParticleList[i])
                SAFE_DELETE(pParticleList[i])
        }
        delete[] pParticleList;
    }
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Emitter::Update(void)
{
    if (data.draw)
    {
        // �^�C�}�[���X�V
        timer++;

        // �G�t�F�N�g�X�V����
        for (int i = 0; i < PARTICLE_MAX; i++)
        {
            if (pParticleList[i]->IsUsed())
            {
                // �����𒴂�����폜
                particle[i].life--;
                if (particle[i].life <= 0)
                {
                    pParticleList[i]->SetUse(false);
                }

                particle[i].vecTrans += particle[i].accelTrans;
                particle[i].vecRot += particle[i].accelRot;
                particle[i].vecScale += particle[i].accelScale;

                particle[i].pos += particle[i].vecTrans;
                particle[i].rot += particle[i].vecRot;
                particle[i].scale += particle[i].vecScale;
                particle[i].nowColor = Color(
                    particle[i].nowColor.r + particle[i].chgColorR,
                    particle[i].nowColor.g + particle[i].chgColorG,
                    particle[i].nowColor.b + particle[i].chgColorB,
                    particle[i].nowColor.a + particle[i].chgColorA
                    );

                // �p�[�e�B�N�����X�V
                pParticleList[i]->SetPosition(particle[i].pos);
                pParticleList[i]->SetRotation(particle[i].rot);
                pParticleList[i]->SetScale(particle[i].scale);
                pParticleList[i]->SetColor(particle[i].nowColor);
            }
        }

        // �G�t�F�N�g��������
        // �����Ԋu�A�����J�n�ł���t���[�����ǂ����A�p�[�e�B�N���͂܂����邩�ǂ���
        if (cnt > Random::Generate<int>(data.createIntervalMin, data.createIntervalMax) &&
            timer > Random::Generate<int>(data.createStartMin, data.createStartMax) &&
            particleNum < data.createNum)
        {
            for (int i = 0; i < PARTICLE_MAX; i++)
            {
                // ��������p�[�e�B�N����������
                if (!particle[i].isCreated &&
                    !pParticleList[i]->IsUsed())
                {
                    cnt = 0;

                    particle[i].isCreated = true;
                    particle[i].life = Random::Generate<int>(data.lifeMin, data.lifeMax);

                    pParticleList[i]->SetUse(true);


                    particle[i].pos = Vector3(
                        Random::Generate<float>(data.posMin.x, data.posMax.x),
                        Random::Generate<float>(data.posMin.y, data.posMax.y),
                        Random::Generate<float>(data.posMin.z, data.posMax.z)
                        );
                    particle[i].rot = Vector3(
                        Random::Generate<float>(data.rotMin.x, data.rotMax.x),
                        Random::Generate<float>(data.rotMin.y, data.rotMax.y),
                        Random::Generate<float>(data.rotMin.z, data.rotMax.z)
                        );
                    particle[i].scale = Vector2(
                        Random::Generate<float>(data.sclMin.x, data.sclMax.x),
                        Random::Generate<float>(data.sclMin.z, data.sclMax.z)
                        );

                    particle[i].vecTrans = Vector3(
                        Random::Generate<float>(data.posVelMin.x, data.posVelMax.x),
                        Random::Generate<float>(data.posVelMin.y, data.posVelMax.y),
                        Random::Generate<float>(data.posVelMin.z, data.posVelMax.z)
                        );
                    particle[i].vecRot = Vector3(
                        Random::Generate<float>(data.rotVelMin.x, data.rotVelMax.x),
                        Random::Generate<float>(data.rotVelMin.y, data.rotVelMax.y),
                        Random::Generate<float>(data.rotVelMin.z, data.rotVelMax.z)
                        );
                    particle[i].vecScale = Vector2(
                        Random::Generate<float>(data.sclVelMin.x, data.sclVelMax.x),
                        Random::Generate<float>(data.sclVelMin.z, data.sclVelMax.z)
                        );

                    particle[i].accelTrans = Vector3(
                        Random::Generate<float>(data.posAccelMin.x, data.posAccelMax.x),
                        Random::Generate<float>(data.posAccelMin.y, data.posAccelMax.y),
                        Random::Generate<float>(data.posAccelMin.z, data.posAccelMax.z)
                        );
                    particle[i].accelRot = Vector3(
                        Random::Generate<float>(data.rotAccelMin.x, data.rotAccelMax.x),
                        Random::Generate<float>(data.rotAccelMin.y, data.rotAccelMax.y),
                        Random::Generate<float>(data.rotAccelMin.z, data.rotAccelMax.z)
                        );
                    particle[i].accelScale = Vector2(
                        Random::Generate<float>(data.sclAccelMin.x, data.sclAccelMax.x),
                        Random::Generate<float>(data.sclAccelMin.z, data.sclAccelMax.z)
                        );

                    Color startColor = Color(
                        Random::Generate<int>(data.startColorMin.r, data.startColorMax.r),
                        Random::Generate<int>(data.startColorMin.g, data.startColorMax.g),
                        Random::Generate<int>(data.startColorMin.b, data.startColorMax.b),
                        Random::Generate<int>(data.startColorMin.a, data.startColorMax.a)
                        );
                    Color endColor = Color(
                        Random::Generate<int>(data.endColorMin.r, data.endColorMax.r),
                        Random::Generate<int>(data.endColorMin.g, data.endColorMax.g),
                        Random::Generate<int>(data.endColorMin.b, data.endColorMax.b),
                        Random::Generate<int>(data.endColorMin.a, data.endColorMax.a)
                        );

                    particle[i].chgColorR = (int)((float)(endColor.r - startColor.r) / particle[i].life);
                    particle[i].chgColorG = (int)((float)(endColor.g - startColor.g) / particle[i].life);
                    particle[i].chgColorB = (int)((float)(endColor.b - startColor.b) / particle[i].life);
                    particle[i].chgColorA = (int)((float)(endColor.a - startColor.a) / particle[i].life);

                    particle[i].nowColor = startColor;

                    pParticleList[i]->SetColor(startColor);
                    pParticleList[i]->SetPosition(particle[i].pos);
                    pParticleList[i]->SetRotation(particle[i].rot);
                    pParticleList[i]->SetScale(particle[i].scale);

                    // ��������͈̂��
                    break;
                }
            }
        }
        // �G�t�F�N�g��������Ȃ��Ƃ��̓J�E���^��1���₷
        else
        {
            cnt++;
        }
    }
}

/******************************************************************************
@brief  ���Z�b�g����
******************************************************************************/

void Emitter::Reset(void)
{
    // �^�C�}�[��0��
    timer = 0;

    // �p�[�e�B�N�������ׂč폜
    for (int i = 0; i < PARTICLE_MAX; i++)
    {
        pParticleList[i]->SetUse(false);
        particle[i].isCreated = false;
    }
}

/******************************** ���������܂� *******************************/
