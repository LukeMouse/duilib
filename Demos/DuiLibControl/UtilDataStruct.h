#pragma once

struct tagTransData
{
    std::string leftBase64;
    std::string rightBase64;
};
typedef struct tagTransData TransData;

class CxImage;

RECT GetImagePos(RECT rcWnd, const int imageWidth,
    const int imageHeight, const BOOL bCenter, const BOOL bStretch);


//将CxImage转为位图
HBITMAP ChangeCxImageToBMP(HDC hDC, CxImage* cximage);
