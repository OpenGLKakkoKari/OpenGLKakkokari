/*****************************************************************************/
/*!
@file   Motion.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Motion.h"
#include "..\Math\Math.h"


using Framework::Motion;
using Framework::Vector3;
using Framework::Matrix;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Motion::Motion() : 
frame(0), loop(false), keyframeNum(0), keyframeList(0), frameMax(0)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Motion::~Motion()
{
}

/******************************************************************************
@brief  �t���[����i�߂�
@param  addFrameCnt         �i�߂�t���[����
******************************************************************************/

void Motion::NextFrame(int addFrameCnt)
{
    frame += addFrameCnt;

    // ���[�v���Ă���ꍇ�͏�]�Z�Ńt���[�������[�v
    if (loop)
    {
        frame %= frameMax;
    }
    // ���[�v���Ă��Ȃ��ꍇ�͍Ō�̃t���[���Ŏ~�߂�
    else
    {
        if (frame >= frameMax)
        {
            frame = frameMax - 1;
        }
    }
}

/******************************************************************************
@brief  �s��擾
@param  PartsIndex      �p�[�c�̃C���f�b�N�X
@return Matrix          �������ꂽ�s��
******************************************************************************/


//Matrix Motion::GetMatrix(int PartsIndex)
//{
//    Matrix mat;
//    return mat;
//}


/*****************************************************************************/
/*!
@fn     Framework::Motion::GetPosition
@brief  ���W�擾
@param  PartsIndex      �p�[�c�̃C���f�b�N�X
@return Vector3         �������ꂽ���W

******************************************************************************/


//Vector3 Motion::GetPosition(int PartsIndex)
//{
//    int tmpFrame = frame;
//    for (int i = 0; i < keyframeNum - 1; i++)
//    {
//        if (tmpFrame <= KeyframeList[i].interval)
//        {
//            Vector3 ret;
//            Vector3 change;
//            change = KeyframeList[i + 1].KeyList[PartsIndex].pos - KeyframeList[i].KeyList[PartsIndex].pos;
//            ret = Vector3(
//                KeyframeList[i].KeyList[PartsIndex].pos.x + change.x / KeyframeList[i].interval * tmpFrame,
//                KeyframeList[i].KeyList[PartsIndex].pos.y + change.y / KeyframeList[i].interval * tmpFrame,
//                KeyframeList[i].KeyList[PartsIndex].pos.z + change.z / KeyframeList[i].interval * tmpFrame
//                );
//            return ret;
//        }
//        else
//        {
//            tmpFrame -= KeyframeList[i].interval;
//        }
//    }
//
//    Vector3 ret;
//    Vector3 change;
//    Vector3 initPos = Vector3(0.0f, 0.0f, 0.0f);
//    change = initPos - KeyframeList[keyframeNum - 1].KeyList[PartsIndex].pos;
//    ret = Vector3(
//        KeyframeList[keyframeNum - 1].KeyList[PartsIndex].pos.x + change.x / KeyframeList[keyframeNum - 1].interval * tmpFrame,
//        KeyframeList[keyframeNum - 1].KeyList[PartsIndex].pos.y + change.y / KeyframeList[keyframeNum - 1].interval * tmpFrame,
//        KeyframeList[keyframeNum - 1].KeyList[PartsIndex].pos.z + change.z / KeyframeList[keyframeNum - 1].interval * tmpFrame
//        );
//    return ret;
//}


/*****************************************************************************/
/*!
@fn     Framework::Motion::GetRotation
@brief  �p�x�擾
@param  PartsIndex      �p�[�c�̃C���f�b�N�X
@return Vector3         �������ꂽ���W

******************************************************************************/

//
//Vector3 Motion::GetRotation(int PartsIndex)
//{
//    int tmpFrame = frame;
//    for (int i = 0; i < keyframeNum-1; i++)
//    {
//        if (tmpFrame < KeyframeList[i].interval)
//        {
//            Vector3 ret;
//            Vector3 change;
//            change = KeyframeList[i + 1].KeyList[PartsIndex].rot - KeyframeList[i].KeyList[PartsIndex].rot;
//
//            if (change.x >= _PI())
//                change.x -= _2PI();
//
//            if (change.x <= -_PI())
//                change.x += _2PI();
//
//            if (change.y >= _PI())
//                change.y -= _2PI();
//
//            if (change.y <= -_PI())
//                change.y += _2PI();
//
//            if (change.z >= _PI())
//                change.z -= _2PI();
//
//            if (change.z <= -_PI())
//                change.z += _2PI();
//
//            ret = Vector3(
//                KeyframeList[i].KeyList[PartsIndex].rot.x + change.x / KeyframeList[i].interval * tmpFrame,
//                KeyframeList[i].KeyList[PartsIndex].rot.y + change.y / KeyframeList[i].interval * tmpFrame,
//                KeyframeList[i].KeyList[PartsIndex].rot.z + change.z / KeyframeList[i].interval * tmpFrame
//                );
//            return ret;
//        }
//        else
//        {
//            tmpFrame -= KeyframeList[i].interval;
//        }
//    }
//
//    Vector3 ret;
//    Vector3 change;
//    change = KeyframeList[0].KeyList[PartsIndex].rot - KeyframeList[keyframeNum - 1].KeyList[PartsIndex].rot;
//
//    if (change.x >= _PI())
//        change.x -= _2PI();
//
//    if (change.x <= -_PI())
//        change.x += _2PI();
//
//    if (change.y >= _PI())
//        change.y -= _2PI();
//
//    if (change.y <= -_PI())
//        change.y += _2PI();
//
//    if (change.z >= _PI())
//        change.z -= _2PI();
//
//    if (change.z <= -_PI())
//        change.z += _2PI();
//
//
//    ret = Vector3(
//        KeyframeList[keyframeNum - 1].KeyList[PartsIndex].rot.x + change.x / KeyframeList[keyframeNum - 1].interval * tmpFrame,
//        KeyframeList[keyframeNum - 1].KeyList[PartsIndex].rot.y + change.y / KeyframeList[keyframeNum - 1].interval * tmpFrame,
//        KeyframeList[keyframeNum - 1].KeyList[PartsIndex].rot.z + change.z / KeyframeList[keyframeNum - 1].interval * tmpFrame
//        );
//    return ret;
//
//}


/******************************** ���������܂� *******************************/
