#include "stdafx.h"
#include "UtilDataStruct.h"
#include <ximage.h>


RECT GetImagePos(RECT rcWnd, const int imageWidth, const int imageHeight, const BOOL bCenter, const BOOL bStretch)
{
    RECT rect;

    int wndWidth = rcWnd.right - rcWnd.left;
    int wndHeight = rcWnd.bottom - rcWnd.top;
    double dRatio = 1.0;

    double dHRatio = wndWidth * 1.0 / imageWidth;
    double dVRatio = wndHeight * 1.0 / imageHeight;

    /// image is too small and need not stretch 
    if (!bStretch && dHRatio > 1.0 && dVRatio > 1.0)
    {
        if (dHRatio > dVRatio)
        {
            dRatio = dVRatio;
        }
        else
        {
            dRatio = dHRatio;
        }
    }
    else if ((dHRatio >= dVRatio) &&
        (wndWidth - imageWidth * dHRatio >= 0) &&
        (wndHeight - imageHeight * dHRatio >= 0))
    {
        dRatio = dHRatio;
    }
    else if ((dHRatio >= dVRatio) &&
        (wndWidth - imageWidth * dVRatio >= 0) &&
        (wndHeight - imageHeight * dVRatio >= 0))
    {
        dRatio = dVRatio;
    }
    else if ((wndWidth - imageWidth * dVRatio >= 0) &&
        (wndHeight - imageHeight * dVRatio >= 0))
    {
        dRatio = dVRatio;
    }
    else if ((wndWidth - imageWidth * dHRatio >= 0) &&
        (wndHeight - imageHeight * dHRatio >= 0))
    {
        dRatio = dHRatio;
    }

    if (bCenter)
    {
        rect.left = static_cast<Gdiplus::REAL>(wndWidth * 1.0 / 2 -
            (imageWidth * 1.0 / 2) * dRatio);

        rect.top = static_cast<Gdiplus::REAL>(wndHeight * 1.0 / 2 -
            (imageHeight * 1.0 / 2) * dRatio);
    }
    else
    {
        rect.left = rect.top = 0;
    }

    rect.right = rect.left + static_cast<LONG>(imageWidth * dRatio);
    rect.bottom = rect.top + static_cast<LONG>(imageHeight * dRatio);

    return rect;
}

HBITMAP ChangeCxImageToBMP(HDC hDC, CxImage* cximage)
{
    //创建HBITMAP
    HBITMAP BMP = CreateCompatibleBitmap(hDC, cximage->GetWidth(), cximage->GetHeight());
    BITMAP bm;
    GetObject(BMP, sizeof(BITMAP), &bm);
    int pb = bm.bmBitsPixel / 8;	//获取位图位数
    int BytesPerLineOut = (bm.bmWidth*pb + 3) / 4 * 4;	//计算每行像素的数据长度
    BYTE *pxd = new unsigned char[bm.bmHeight*BytesPerLineOut]; //声明暂存数组

    if (cximage->GetBpp() >= 16)
    {
        //直接获取像素数据
        int pbx = cximage->GetBpp() / 8;	//获取CxImage图片的位数
        int BytesPerLine = (bm.bmWidth*pbx + 3) / 4 * 4;	//计算CxImage每行像素的数据长度
        BYTE *pDib = cximage->GetBits();	//获取CxImage图片的像素数据

        for (int i = 0; i < bm.bmHeight; i++)
        {
            for (int j = 0; j < bm.bmWidth; j++)
            {
                int srcRGB_B = (bm.bmHeight - 1 - i)*BytesPerLine + j*pbx;
                int desRGB_B = i*bm.bmWidthBytes + j*pb;

                pxd[desRGB_B] = pDib[srcRGB_B];
                pxd[desRGB_B + 1] = pDib[srcRGB_B + 1];
                pxd[desRGB_B + 2] = pDib[srcRGB_B + 2];
            }
        }
    }
    else
    {
        //通过调色板获取像素数据
        for (int i = 0; i < bm.bmHeight; i++)
        {
            for (int j = 0; j < bm.bmWidth; j++)
            {
                RGBQUAD srcRGB_B = cximage->GetPixelColor(j, bm.bmHeight - 1 - i);
                int desRGB_B = i*bm.bmWidthBytes + j*pb;

                pxd[desRGB_B] = srcRGB_B.rgbBlue;
                pxd[desRGB_B + 1] = srcRGB_B.rgbGreen;
                pxd[desRGB_B + 2] = srcRGB_B.rgbRed;
            }
        }
    }

    SetBitmapBits(BMP, bm.bmHeight*bm.bmWidthBytes, pxd);
    delete[] pxd;

    return BMP;
}