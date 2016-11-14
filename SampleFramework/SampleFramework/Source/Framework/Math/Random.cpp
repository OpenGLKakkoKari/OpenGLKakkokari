/*****************************************************************************/
/*!
@file   Random.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Random.h"
#include <stdlib.h>
#include <time.h>


using Framework::Math::Random;


/*  変数宣言
******************************************************************************/


unsigned int Random::seed;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  シード設定
@param  s           設定するシード
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
@brief  乱数生成
@param  min         生成する乱数範囲の最小値
@param  max         生成する乱数範囲の最大値
@return T           生成された乱数
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

/******************************** 実装ここまで *******************************/
