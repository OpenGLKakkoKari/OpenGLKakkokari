#pragma once
/******************************************************************************
/*!
@file   Tweaker.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Text.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace Tweaker
    {
        enum {OBJECT_MAX = 512};

        enum Type
        {
            TYPE_FOLDER,

            TYPE_INT,
            TYPE_FLOAT,
            TYPE_BOOL,
            TYPE_VECTOR2,
            TYPE_VECTOR3,
            TYPE_COLOR,

            TYPE_MAX,
        };

        class DirectoryObject
        {
        public:
            enum { NAME_MAX = 128 };

            DirectoryObject() :
                pData(NULL),
                type_(TYPE_FOLDER),
                isUsed_(false),
                child_(NULL),
                sibling_(NULL){}

            DirectoryObject(Type type) :
                pData(NULL),
                type_(type),
                isUsed_(false),
                child_(NULL),
                sibling_(NULL){}
            

            bool IsUsed()                   { return isUsed_; }
            bool IsSameType(Type type)      { return type_ == type; }

            void Set(int* value)            { pData = value; type_ = TYPE_INT; }
            void Set(float* value)          { pData = value; type_ = TYPE_FLOAT; }
            void Set(bool* value)           { pData = value; type_ = TYPE_BOOL; }
            void Set(Vector2* value)        { pData = value; type_ = TYPE_VECTOR2; }
            void Set(Vector3* value)        { pData = value; type_ = TYPE_VECTOR3; }
            void Set(Color* value)          { pData = value; type_ = TYPE_COLOR; }
            void SetName(const char* name)  { strcpy_s(name_, NAME_MAX, name); }
            void SetUse(bool isUsed)        { isUsed_ = isUsed; }

            Type GetType()                  { return type_; }
            const char* GetName()           { return name_; }

            DirectoryObject*    child_;
            DirectoryObject*    sibling_;

            void*               pData;
            char                name_[NAME_MAX];
            Type                type_;
            bool                isUsed_;
        };

        class Tweaker
        {
        public:
            Tweaker();
            virtual ~Tweaker();

            void Update();
            void SetUse(bool isUsed){ pText->SetUse(isUsed); }

            // トゥイーカ登録、解除
            void Add(char* DirName);
            void Add(const char* Text, bool* value);
            void Add(const char* Text, int*  value);
            void Add(const char* Text, float* value);
            void Add(const char* Text, Vector2* value);
            void Add(const char* Text, Vector3* value);
            void Add(const char* Text, Color* value);
            void Delete(const char* Text);
            void Reset();

            void SetDirectory(char* DirName);

            // 操作
            void CursorUp();
            void CursorDown();
            void Decrease();
            void Increase();
            void UpX();
            void UpY();
            void UpZ();
            void DownX();
            void DownY();
            void DownZ();
            void Select();

        private:
            void Init();
            bool IsRoot(DirectoryObject* p){ return &dirObjectList[0] == p; }
            DirectoryObject* GetRoot()     { return &dirObjectList[0]; }
            DirectoryObject* GetDirectoryEnd(DirectoryObject* dir);
            DirectoryObject* GetAboveDirectory(DirectoryObject* dir);
            void AddObject(DirectoryObject* p);
            bool IsCursorPosition(int pos) { return cursorPos == pos; }
            void DeleteObject(DirectoryObject* p);
            void DeleteFolder(DirectoryObject* pFolder, const char* filePath);

            void PrintVersion();
            void PrintBreadcrumb();
            void PrintLine();
            void PrintCursor();

            Text*               pText;
            DirectoryObject*    dirObjectList;          // オブジェクトリスト
            DirectoryObject*    currentDirectory;       // 現在のディレクトリ
            int                 cursorPos;              // ディレクトリ内のカーソル位置
        };
    }
}


/******************************* ヘッダここまで ******************************/
