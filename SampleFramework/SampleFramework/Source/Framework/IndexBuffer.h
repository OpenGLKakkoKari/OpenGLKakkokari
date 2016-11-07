#pragma once
/******************************************************************************
/*!
@file   IndexBuffer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �N���X��`
******************************************************************************/


namespace Framework
{

    class IndexBuffer
    {
    public:
        IndexBuffer() : indexNum(0){}
        virtual ~IndexBuffer(){}

        virtual int* Lock() = 0;
        virtual void Unlock() = 0;
        virtual void Release() = 0;

        int indexNum;
    };
}


/******************************* �w�b�_�����܂� ******************************/
