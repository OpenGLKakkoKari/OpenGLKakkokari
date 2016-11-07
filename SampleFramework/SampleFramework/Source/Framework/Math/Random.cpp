/*****************************************************************************/
/*!
@file   Random.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Random.h"
#include <stdlib.h>
#include <time.h>


using Framework::Math::Random;


/*  �ϐ��錾
******************************************************************************/


unsigned int Random::seed;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �V�[�h�ݒ�
@param  s           �ݒ肷��V�[�h
******************************************************************************/


void Random::Seed()
{
    seed = (unsigned)time(nullptr);
    srand(seed);
}
void Random::Seed(unsigned int s)
{
    seed = s;
    srand(s);
}

/******************************************************************************
@brief  ��������
@param  min         �������闐���͈͂̍ŏ��l
@param  max         �������闐���͈͂̍ő�l
@return T           �������ꂽ����
******************************************************************************/

template<class T>
T Random::Generate(T min, T max)
{
}
template<>
float Random::Generate<float>(float min, float max)
{
    return (rand() % 1000 / 1000.0f) * (max - min) + min;
}
template<>
int Random::Generate<int>(int min, int max)
{
    return (rand() % RAND_MAX / RAND_MAX) * (max - min) + min;
}

/******************************** ���������܂� *******************************/
