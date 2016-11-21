#pragma once
/******************************************************************************
/*!
@file   File.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <stdio.h>


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class File
        {
        public:
            File() : fp(NULL){}
            File(const char *FilePath, const char *Mode);
            ~File();

            bool Open(const char *FilePath, const char *Mode);
            void Close();
            
            int  GetSize();
            void Seek(int offset, int origin);
            
            unsigned char   GetByte();
            void            SetByte(unsigned char c);

            void            GetLine(char* Dest, int maxSize);
            void            GetLine(char* Dest);
            void            SetLine(const char* Src);

            void            Read(void *Dest, int size, int nmemb);
            void            Write(const void *Src, int size, int nmemb);

        private:
            FILE *fp;
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/