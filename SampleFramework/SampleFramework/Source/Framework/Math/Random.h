/******************************************************************************
/*!
@file   Random.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace Math
    {
        class Random
        {
        public:
            Random(){}
            ~Random(){}

            static void Seed();
            static void Seed(unsigned int s);

            template <class T>
            static T Generate(T min, T max);

            static unsigned int GetSeed(){ return seed; }

        private:
            static unsigned int seed;
        };
        
    };
}


/******************************* ヘッダここまで ******************************/
