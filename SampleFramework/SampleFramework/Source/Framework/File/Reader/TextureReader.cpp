/*****************************************************************************/
/*!
@file   TextureReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "TextureReader.h"
#include "../File.h"
#include "../../Error.h"

using Framework::File::File;
using Framework::File::TextureReader;
using Framework::Texture;
using Framework::Error;


/*  静的変数宣言
******************************************************************************/


bool TextureReader::reverse;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  ファイル読み込み
@param  FileName    ファイル名
@param  reverse     反転フラグ
@return Texture*    テクスチャ情報
******************************************************************************/

Texture* TextureReader::Load(const char *FileName, bool reverse)
{

    TextureReader::reverse = reverse;
    strcpy(fileName, FileName);
    GetExtension(FileName);

    if (strcmp(ext, ".bmp") == 0)
    {
        return LoadBMP(FileName);
    }
    else if (strcmp(ext, ".jpg") == 0 ||
        strcmp(ext, ".jpeg") == 0)
    {
        return LoadJPG(FileName);
    }
    else if (strcmp(ext, ".png") == 0)
    {
        return LoadPNG(FileName);
    }
    else if (strcmp(ext, ".tga") == 0)
    {
        return LoadTGA(FileName);
    }

    return NULL;
}

/******************************************************************************
@brief  BMPファイル読み込み
@param  FileName    ファイル名
@return Texture*    テクスチャ
******************************************************************************/

Texture* TextureReader::LoadBMP(const char *FileName)
{
    Texture* pTex;
    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    BITMAPCOREHEADER bmpCoreHeader;

    // ファイル読み込み
    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return NULL;
    }
    pTex = new Texture;

    // ファイルヘッダー読み込み
    file.Read(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1);

    // 情報ヘッダーのサイズを読み込む
    unsigned long biSize;
    file.Read(&biSize, sizeof(unsigned long), 1);
    // 情報ヘッダーの先頭に移動
    file.Seek(sizeof(BITMAPFILEHEADER), SEEK_SET);

    // 情報ヘッダー読み込み
    if (biSize == sizeof(BITMAPINFOHEADER))
    {
        file.Read(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1);
        // テクスチャ情報設定
        pTex->SetInfo(
            (bmpInfoHeader.biBitCount == 32) ? (Texture::RGBA8888) : (Texture::RGBX8888),
            bmpInfoHeader.biWidth,
            bmpInfoHeader.biHeight,
            32);
    }
    else if (biSize == sizeof(BITMAPCOREHEADER))
    {
        file.Read(&bmpCoreHeader, sizeof(BITMAPCOREHEADER), 1);
        // テクスチャ情報設定
        pTex->SetInfo(
            (bmpCoreHeader.bcBitCount == 32) ? (Texture::RGBA8888) : (Texture::RGBX8888),
            bmpCoreHeader.bcWidth,
            bmpCoreHeader.bcHeight,
            32);
    }
    else
        return pTex;


    // バッファ確保
    unsigned char *pNewBuf = new unsigned char[pTex->info.bufferSize];
    file.Seek(bmpFileHeader.bfOffBits, SEEK_SET);

    // データ読み込み
    switch (pTex->info.format)
    {
    case Texture::RGBA8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = file.GetByte(); // A
            }
        }
        break;

    case Texture::RGBX8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = 255;            // A
            }
        }
        break;
    }
    pTex->pData = pNewBuf;

    // 上下反転
    ReverseDataUV(pTex);

    // 色反転
    if (reverse)
        ReverseDataColor(pTex);

    file.Close();

    return pTex;
}

/******************************************************************************
@brief  TGAファイル読み込み
@param  FileName    ファイル名
@return Texture*    テクスチャ
******************************************************************************/

Texture* TextureReader::LoadTGA(const char *FileName)
{
    Texture* pTex;
    TGAHeader tga;

    // ファイル読み込み
    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return NULL;
    }
    pTex = new Texture;

    // ヘッダー読み込み
    file.Read(&tga, sizeof(TGAHeader), 1);

    // テクスチャ情報設定
    pTex->SetInfo(
        (tga.bbp == 32) ? (Texture::RGBA8888) : (Texture::RGBX8888),
        tga.imageWidth,
        tga.imageHeight,
        32);

    // バッファ確保
    unsigned char *pNewBuf = new unsigned char[pTex->info.bufferSize];
    file.Read(pNewBuf, sizeof(unsigned char)*pTex->info.bufferSize, 1);
    file.Seek(sizeof(TGAHeader), SEEK_SET);

    // データ読み込み
    switch (pTex->info.format)
    {
    case Texture::RGBA8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = file.GetByte(); // A
            }
        }
        break;

    case Texture::RGBX8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = 255;            // A
            }
        }
        break;
    }
    pTex->pData = pNewBuf;

    // 上下反転
    ReverseDataUV(pTex);

    // 色反転
    if (reverse)
        ReverseDataColor(pTex);

    file.Close();

    return pTex;
}

/******************************************************************************
@brief  JPGファイル読み込み
@param  FileName    ファイル名
@return Texture*    テクスチャ
******************************************************************************/

Texture* TextureReader::LoadJPG(const char *FileName)
{
    FILE *fp;
    Texture* pTex;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // ファイル読み込み
    if ((fp = fopen(FileName, "rb")) == NULL)
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return NULL;
    }
    pTex = new Texture;

    // JPEGオブジェクトの初期化
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    // JPEGファイルを開く
    jpeg_stdio_src(&cinfo, fp);
    // JPEGヘッダの読み込み
    jpeg_read_header(&cinfo, TRUE);

    // テクスチャ情報設定
    pTex->SetInfo(
        Texture::RGBX8888,
        cinfo.image_width,
        cinfo.image_height,
        32);

    jpeg_start_decompress(&cinfo);

    // イメージを保持するメモリ領域の確保と初期化
    unsigned char* pNewBuf = new unsigned char[pTex->info.bufferSize / 4 * 3];
    unsigned char * rowptr[1];
    while (cinfo.output_scanline < cinfo.output_height) // loop
    {
        // Enable jpeg_read_scanlines() to fill our jdata array
        rowptr[0] = (unsigned char *)pNewBuf +  // secret to method
            3 * cinfo.output_width * cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo, rowptr, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    
    unsigned char *pBuf = new unsigned char[pTex->info.bufferSize];
    for (unsigned int y = 0; y < pTex->info.height; y++)
    {
        for (unsigned int x = 0; x < pTex->info.width; x++)
        {
            pBuf[pTex->info.pitch*y + 4 * x + 2] = pNewBuf[pTex->info.width * 3 * y + 3 * x + 2]; // B
            pBuf[pTex->info.pitch*y + 4 * x + 1] = pNewBuf[pTex->info.width * 3 * y + 3 * x + 1]; // G
            pBuf[pTex->info.pitch*y + 4 * x + 0] = pNewBuf[pTex->info.width*3*y + 3 * x + 0]; // R
            pBuf[pTex->info.pitch*y + 4 * x + 3] = 255; // A
        }
    }

    delete[] pNewBuf;
    fclose(fp);
    pTex->pData = pBuf;

    // 色反転
    if (reverse)
        ReverseDataColor(pTex);

    return pTex;

}

/******************************************************************************
@brief  PNGファイル読み込み
@param  FileName    ファイル名
@return Texture*    テクスチャ
******************************************************************************/

Texture* TextureReader::LoadPNG(const char *FileName)
{
    FILE *fp;
    Texture* pTex;
    if ((fp = fopen(FileName, "rb")) == NULL)
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
        return NULL;
    }
    pTex = new Texture;

    const unsigned int headerSize = 8;

    png_structp pPng;
    png_infop pInfo;
    png_uint_32 Width, Height;
    int nBitDepth, nColorType, nInterlaceType;

    // png_struct 構造体の初期化
    pPng = png_create_read_struct(
        PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    // png_info 構造体の初期化（画像データの前にあるチャンク用）
    pInfo = png_create_info_struct(pPng);
    png_init_io(pPng, fp);
    png_read_info(pPng, pInfo);
    png_get_IHDR(pPng, pInfo, &Width, &Height,
        &nBitDepth, &nColorType, &nInterlaceType,
        NULL, NULL);

    pTex->info.width = Width;
    pTex->info.height = Height;
    pTex->info.format = (nBitDepth == 8) ? (Texture::RGBA8888) : (Texture::RGBX8888);
    pTex->info.bufferSize = (nBitDepth == 8) ? (Width*Height * 4) : (Width*Height * 3);
    pTex->info.pitch = (nBitDepth == 8) ? (Width * 4) : (Width * 3);
    pTex->info.bit = nBitDepth * 4;

    // メモリ領域確保
    int rb = png_get_rowbytes(pPng, pInfo);
    unsigned char *pNewBuf = new unsigned char[Height * rb];
    unsigned char **recv = new unsigned char*[Height];
    for (unsigned int i = 0; i < Height; i++)
        recv[i] = &pNewBuf[i * rb];
    png_read_image(pPng, recv);
    png_read_end(pPng, pInfo);
    png_destroy_read_struct(&pPng, &pInfo, NULL);
    delete[] recv;

    fclose(fp);
    pTex->pData = pNewBuf;

    // 色反転
    if (reverse)
        ReverseDataColor(pTex);

    return pTex;
}

/******************************************************************************
@brief  データを上下反対にする
@param  tex         テクスチャ
@return Texture     上下反転したテクスチャ
******************************************************************************/

void TextureReader::ReverseDataUV(Texture *pTex)
{
    // 上下反転
    for (unsigned int y = 0; y < pTex->info.height / 2; y++)
    {
        for (unsigned int x = 0; x < pTex->info.width; x++)
        {
            unsigned char *pNewBuf = (unsigned char*)pTex->pData;

            unsigned char b = pNewBuf[pTex->info.pitch*y + 4 * x + 2];
            unsigned char g = pNewBuf[pTex->info.pitch*y + 4 * x + 1];
            unsigned char r = pNewBuf[pTex->info.pitch*y + 4 * x + 0];
            unsigned char a = pNewBuf[pTex->info.pitch*y + 4 * x + 3];

            pNewBuf[pTex->info.pitch*y + 4 * x + 2] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 2];
            pNewBuf[pTex->info.pitch*y + 4 * x + 1] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 1];
            pNewBuf[pTex->info.pitch*y + 4 * x + 0] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 0];
            pNewBuf[pTex->info.pitch*y + 4 * x + 3] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 3];

            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 2] = b;
            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 1] = g;
            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 0] = r;
            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 3] = a;
        }
    }
}

/******************************************************************************
@brief  データの色のRとBを反対にする
@param  tex         テクスチャ
@return Texture     上下反転したテクスチャ
******************************************************************************/

void TextureReader::ReverseDataColor(Texture *pTex)
{
    // 色反転
    for (unsigned int y = 0; y < pTex->info.height; y++)
    {
        for (unsigned int x = 0; x < pTex->info.width; x++)
        {
            unsigned char *pNewBuf = (unsigned char*)pTex->pData;

            unsigned char b = pNewBuf[pTex->info.pitch*y + 4 * x + 2];
            unsigned char r = pNewBuf[pTex->info.pitch*y + 4 * x + 0];

            pNewBuf[pTex->info.pitch*y + 4 * x + 2] = r;
            pNewBuf[pTex->info.pitch*y + 4 * x + 0] = b;
        }
    }
}

/******************************* 関数ここまで ********************************/
