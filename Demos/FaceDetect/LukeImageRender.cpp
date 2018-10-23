// LukeImageRender.cpp : implementation file
//

#include "stdafx.h"
#include "LukeImageRender.h"


// CLukeImageRender

//gdiInit g_initGDIPlus;

IMPLEMENT_DYNAMIC(CLukeImageRender, CStatic)

CLukeImageRender::CLukeImageRender(const CString& promptINfo,const BOOL bAutoZoom)
: m_pByImageData(0)
, m_nDibSize(0)
, m_bFirst(TRUE)
, m_nullPromptInfo(promptINfo)
, m_bAutoZoomImage(bAutoZoom)
, m_fZoomRatio(1.0f)
{
    m_pBrBackground =
        new Gdiplus::SolidBrush(Gdiplus::Color(255, 128, 128, 128));
}

CLukeImageRender::~CLukeImageRender()
{
    delete []m_pByImageData;
    m_pByImageData = 0;

    delete m_pBrBackground;
}

BEGIN_MESSAGE_MAP(CLukeImageRender, CStatic)
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()



// CLukeImageRender message handlers
Gdiplus::RectF CLukeImageRender::GetImagePos( CRect* rcWnd,
                                            const int imageWidth,
                                            const int imageHeight,
                                            const BOOL bCenter,
                                            const BOOL bStretch)
{
    Gdiplus::RectF rect;

    int wndWidth = rcWnd->Width();
    int wndHeight = rcWnd->Height();
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
        (wndWidth - imageWidth * dHRatio >=0 ) &&
        (wndHeight - imageHeight * dHRatio >= 0))
    {
        dRatio = dHRatio;
    }
    else if ((dHRatio >= dVRatio) &&
        (wndWidth - imageWidth * dVRatio >=0 ) &&
        (wndHeight - imageHeight * dVRatio >= 0))
    {
        dRatio = dVRatio;
    }
    else if ((wndWidth - imageWidth * dVRatio >=0 ) &&
        (wndHeight - imageHeight * dVRatio >= 0))
    {
        dRatio = dVRatio;
    }
    else if ((wndWidth - imageWidth * dHRatio >=0 ) &&
        (wndHeight - imageHeight * dHRatio >= 0))
    {
        dRatio = dHRatio;
    }

    if (bCenter)
    {
        rect.X = static_cast<Gdiplus::REAL>(wndWidth * 1.0 / 2 -
            (imageWidth * 1.0 / 2) * dRatio);

        rect.Y = static_cast<Gdiplus::REAL>(wndHeight * 1.0 / 2 -
            (imageHeight * 1.0 / 2) * dRatio);
    }
    else
    {
        rect.X = rect.Y = 0;
    }

    rect.Width = static_cast<Gdiplus::REAL>(imageWidth * dRatio);
    rect.Height = static_cast<Gdiplus::REAL>(imageHeight * dRatio);

    return rect;
}

void CLukeImageRender::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: Add your message handler code here
    // Do not call CStatic::OnPaint() for painting messages

    CRect rectClient;
    GetClientRect(rectClient);

    CDC memDC;
    memDC.CreateCompatibleDC(&dc);

    HBITMAP hOldBmp;
    CBitmap bmpMem;

    bmpMem.CreateCompatibleBitmap(
        &dc, rectClient.Width(),rectClient.Height());
    hOldBmp = (HBITMAP)memDC.SelectObject(bmpMem);

    Gdiplus::Graphics graphic(memDC.m_hDC);
    if (0 == m_pByImageData)
    {
        graphic.FillRectangle(m_pBrBackground, 0, 0,
            rectClient.Width(), rectClient.Height());

        Gdiplus::RectF showPos;
        showPos.X = 0;
        showPos.Y = static_cast<Gdiplus::REAL>(rectClient.Height() * 4 / 9);
        showPos.Width = static_cast<Gdiplus::REAL>(rectClient.Width());
        showPos.Height = static_cast<Gdiplus::REAL>(rectClient.Height() / 9);

        Gdiplus::StringFormat format;
        format.SetAlignment(Gdiplus::StringAlignmentCenter);
        Gdiplus::SolidBrush textBrush(Gdiplus::Color(255, 255, 125, 0));
        Gdiplus::Font txtFont(L"宋体",
            (min(showPos.Height, (showPos.Width * 1 / 9))) * 2 / 5);
#ifdef _UNICODE
        graphic.DrawString(m_nullPromptInfo, -1,
            &txtFont, showPos, &format, &textBrush);
#else
        graphic.DrawString(CA2W(m_nullPromptInfo), -1,
            &txtFont, showPos, &format, &textBrush);
#endif
    }
    else
    {
        BITMAPINFOHEADER *pInfoHeader = (BITMAPINFOHEADER *)m_pByImageData;
        unsigned char *pbyBits;
        if (pInfoHeader->biBitCount == 8)
            pbyBits = m_pByImageData +
            sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256;
        else
            pbyBits = m_pByImageData + sizeof(BITMAPINFOHEADER);

        Gdiplus::Bitmap bitmap(
            reinterpret_cast<const BITMAPINFO *>(pInfoHeader), pbyBits);

        graphic.FillRectangle(m_pBrBackground, 0, 0,
            rectClient.Width(), rectClient.Height());

        /// retrieve show position for first call
        if (m_bFirst && m_bAutoZoomImage)
        {
            m_destRect = GetImagePos(&rectClient, pInfoHeader->biWidth,
                pInfoHeader->biHeight);
        }

        // draw image
        if (m_bAutoZoomImage)
        {
            graphic.DrawImage(&bitmap, m_destRect, 0, 0,
                static_cast<Gdiplus::REAL>(pInfoHeader->biWidth),
                static_cast<Gdiplus::REAL>(pInfoHeader->biHeight),
                Gdiplus::UnitPixel, NULL, NULL);
        }
        else
        {
            graphic.DrawImage(&bitmap, m_destRect, 0.0f, 0.0f,
                static_cast<Gdiplus::REAL>(pInfoHeader->biWidth),
                static_cast<Gdiplus::REAL>(pInfoHeader->biHeight),
                Gdiplus::UnitPixel, NULL, NULL);
        }

        Gdiplus::StringFormat format;
        format.SetAlignment(Gdiplus::StringAlignmentCenter);
        Gdiplus::SolidBrush yellowBrush(Gdiplus::Color(255, 255, 0, 255));

        ShowPromptInfo(graphic);
    }

    dc.BitBlt(0, 0, rectClient.Width(),
        rectClient.Height(), &memDC, 0, 0, SRCCOPY);

    memDC.SelectObject(bmpMem);
    bmpMem.DeleteObject();

    memDC.DeleteDC();
}

void CLukeImageRender::RenderImage(BYTE* byDIBImage,
                                  const int dibSize)
{
    if (dibSize != m_nDibSize)
    {
        delete []m_pByImageData;
        m_pByImageData = 0;
    }

    if (0 == m_pByImageData)
    {
        m_pByImageData = new BYTE[dibSize];
        m_nDibSize = dibSize;
        m_bFirst = TRUE;
    }

    memcpy(m_pByImageData, byDIBImage, dibSize);

    if (!m_bAutoZoomImage)
    {
        m_fZoomRatio = 1.0f;
        CPoint ptTemp(-1, -1);
        CalculateDestPos(ptTemp);
    }

    Invalidate();
}


void CLukeImageRender::ClearImage()
{
    delete []m_pByImageData;
    m_pByImageData = 0;
    m_nDibSize = 0;
    Invalidate();
}


void CLukeImageRender::ResizeClient()
{
    if (m_bAutoZoomImage)
    {
        m_bFirst = TRUE;
        Invalidate();
    }
}


void CLukeImageRender::UpdatePromptString(const int propPos, 
                                         const CString& strPrompt,
                                         const Gdiplus::Color& clrPrompt)
{
    m_promptInfo[propPos].strPromptInfo = strPrompt;
    m_promptInfo[propPos].textColor = clrPrompt;
    Invalidate();
}


void CLukeImageRender::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    ResizeClient();
}


BOOL CLukeImageRender::GetRenderImageData(int &imageSize, BYTE*& imageDIBData)
{
    if (-1 == imageSize)
    {
        imageSize = m_nDibSize;
        return 0 < m_nDibSize;
    }

    if (0 < m_nDibSize)
    {
        imageSize = m_nDibSize;
        memcpy(imageDIBData, m_pByImageData, m_nDibSize);
        return TRUE;
    }
    return FALSE;
}

void CLukeImageRender::ShowPromptInfo(Gdiplus::Graphics& graphic)
{
    Gdiplus::RectF showPos;
    Gdiplus::StringFormat format;
    Gdiplus::StringAlignment aligmentType;
    for (int iCount = 0; iCount < 9; ++iCount)
    {
        if (m_promptInfo[iCount].strPromptInfo.GetLength() > 0)
        {
            showPos = GetPromptShowPos(iCount, aligmentType);
            format.SetAlignment(aligmentType);
            Gdiplus::SolidBrush textBrush(m_promptInfo[iCount].textColor);
            Gdiplus::Font txtFont(L"宋体",
                (min(showPos.Height, (showPos.Width * 1 / 9))) * 3 / 5);

#ifdef _UNICODE
            graphic.DrawString(
                m_promptInfo[iCount].strPromptInfo, -1, &txtFont,
                showPos, &format, &textBrush);
#else
            graphic.DrawString(
                CA2W(m_promptInfo[iCount].strPromptInfo), -1, &txtFont,
                showPos, &format, &textBrush);
#endif
        }
    }
}

Gdiplus::RectF CLukeImageRender::GetPromptShowPos(
    const int posIndex,
    Gdiplus::StringAlignment& aligmentType)
{
    Gdiplus::RectF destRect;
    destRect.X = 0;
    destRect.Width = m_destRect.Width;
    destRect.Height = m_destRect.Height / 9;
    if (posIndex < 3)
    {
        destRect.Y = 0;
    }
    else if (posIndex < 6)
    {
        destRect.Y = m_destRect.Height * 4 /9;
    }
    else
    {
        destRect.Y = m_destRect.Height * 8 /9;
    }

    if (0 == posIndex % 3)
    {
        aligmentType = Gdiplus::StringAlignmentNear;
    }
    else if (1 == posIndex % 3)
    {
        aligmentType = Gdiplus::StringAlignmentCenter;
    }
    else
    {
        aligmentType = Gdiplus::StringAlignmentFar;
    }
    return destRect;
}


void CLukeImageRender::RemovePromptString(const int propPos)
{
    m_promptInfo[propPos].strPromptInfo.Empty();
    Invalidate();
}


void CLukeImageRender::ClearImagePrompt()
{
    for (int iCount = 0; iCount < 9; ++iCount)
    {
        m_promptInfo[iCount].strPromptInfo.Empty();
    }
    Invalidate();
}

int CLukeImageRender::MoveImage(const int xStep, int yStep)
{
    if (0 == m_pByImageData)
    {
        return -1;
    }

    CRect rectClient;
    GetClientRect(rectClient);

#if 0
    CString strDebugInfo;
    strDebugInfo.Format(_T("before l=%.3f,t=%.3f,xstp=%d,ystp=%d,zoom=%f,")
        _T("rcl=%d,rct=%d,rcr=%d,rcb=%d\n"),
        m_destRect.X,m_destRect.Y,xStep, yStep, m_fZoomRatio,
        rectClient.left, rectClient.top, rectClient.right, rectClient.bottom);
    OutputDebugString(strDebugInfo);
#endif

    int retVal = 0;
    if (m_destRect.X >= 1e-6)
    {
        retVal = 1;
    }
    else 
    {
        if (xStep > 0)
        {
            if (m_destRect.X + xStep > 1e-6)
            {
                m_destRect.X = 0.0f;
                retVal = 2;
            }
        }
        else
        {
            if (m_destRect.X + m_destRect.Width + xStep < rectClient.right)
            {
                m_destRect.X = rectClient.right
                    - m_destRect.Width;
                retVal = 3;
            }
        }

        if (0 == retVal)
        {
            m_destRect.X += xStep;
        }
    }

    if (m_destRect.Y >= 1e-6)
    {
        retVal = 4;
    }
    else 
    {
        if (yStep > 0)
        {
            if (m_destRect.Y + yStep > 1e-6)
            {
                m_destRect.Y = 0.0f;
                retVal = 5;
            }
        }
        else
        {
            if (m_destRect.Y + m_destRect.Height
            + yStep < rectClient.bottom)
            {
                m_destRect.Y = rectClient.bottom
                    - m_destRect.Height;
                retVal = 6;
            }
        }

        if(retVal < 4)
        {
            m_destRect.Y += yStep;
        }
    }

#if 0
    strDebugInfo.Format(_T("after l=%.3f,t=%.3f,xstp=%d,ystp=%d,zoom=%f,")
        _T("rcl=%d,rct=%d,rcr=%d,rcb=%d\n"),
        m_destRect.X,m_destRect.Y,xStep, yStep, m_fZoomRatio,
        rectClient.left, rectClient.top, rectClient.right, rectClient.bottom);
    OutputDebugString(strDebugInfo);
#endif
    Invalidate();

    return retVal;
}

CRect CLukeImageRender::GetImageShowPos()
{
    CRect rectClient;
    GetClientRect(rectClient);

    CRect rectShow;
    rectShow.left = m_destRect.X > 0 ?
        0 : static_cast<int>(-m_destRect.X / m_fZoomRatio);
    rectShow.top = m_destRect.Y > 0 ?
        0 : static_cast<int>(-m_destRect.Y / m_fZoomRatio);
    rectShow.right =
        static_cast<LONG>(rectShow.left + __min(m_destRect.Width / m_fZoomRatio,
        rectClient.Width() / m_fZoomRatio) + 0.5);

    rectShow.bottom =
        static_cast<LONG>(rectShow.top + __min(m_destRect.Height / m_fZoomRatio,
        rectClient.Height() / m_fZoomRatio) + 0.5);


    return rectShow;
}

int CLukeImageRender::ZoomImage(const CPoint& pt, const BOOL bZoomIn)
{
    if (pt.x < m_destRect.X || pt.x > m_destRect.X + m_destRect.Width
        || pt.y < m_destRect.Y || pt.y > m_destRect.Y + m_destRect.Height)
    {
        return 4;
    }

    CPoint ptTemp(pt);
    int retVal = CalculateDestPos(ptTemp, bZoomIn ? 1 : 2);

    Invalidate();

    return retVal;
}

int CLukeImageRender::CalculateDestPos(CPoint& pt, const int zoomFashion)
{
    BITMAPINFOHEADER *pInfoHeader = (BITMAPINFOHEADER *)m_pByImageData;
    CRect rectClient;
    GetClientRect(rectClient);

    Gdiplus::PointF ptImimage((pt.x - m_destRect.X) / m_fZoomRatio,
        (pt.y - m_destRect.Y) / m_fZoomRatio);

    // too small image cant zoom
    if(0 != zoomFashion)
    {
        if (m_destRect.X > 0.01f)
        {
            return 1;
        }

        if (m_destRect.Y > 0.01f)
        {
            return 2;
        }
    }

    int retVal = 0;
    switch(zoomFashion)
    {
    case 0:
        //m_fZoomRatio = 1.0f;
        break;

    case 1: // zoom in
        if ((rectClient.Width() - pInfoHeader->biWidth * m_fZoomRatio) > 0)
        {
            retVal += 1;
        }

        if(rectClient.Height() - pInfoHeader->biHeight * m_fZoomRatio > 0)
        {
            retVal += 2;
        }

        if (0 == retVal)
        {
            Gdiplus::REAL tmpZoom1 = m_fZoomRatio / 1.1f;
            Gdiplus::REAL tmpZoom2 = m_fZoomRatio / 1.1f;
            if(rectClient.Width() >
                static_cast<int>(pInfoHeader->biWidth * tmpZoom1 + 0.5))
            {
                tmpZoom1 = rectClient.Width() * 1.0f / pInfoHeader->biWidth;
                retVal += 1;
            }

            if (rectClient.Height() >
                static_cast<int>(pInfoHeader->biHeight * tmpZoom2 + 0.5))
            {
                tmpZoom2 = rectClient.Height() * 1.0f / pInfoHeader->biHeight;
                retVal += 2;
            }

            switch(retVal)
            {
            case 0:
                m_fZoomRatio /= 1.1f;
                break;
            case 1:
                m_fZoomRatio = tmpZoom1;
                break;
            case 2:
                m_fZoomRatio = tmpZoom2;
                break;
            case 3:
                m_fZoomRatio = __max(tmpZoom1, tmpZoom2);
                break;
            }
        }
        break;
    case 2:  // 放大
        m_fZoomRatio *= 1.1f;
        break;
    }

    m_destRect.Width = pInfoHeader->biWidth * m_fZoomRatio;
    m_destRect.Height = pInfoHeader->biHeight * m_fZoomRatio;

    if (0 == zoomFashion) // 初始显示图像居中
    {
        m_destRect.X = 
            static_cast<Gdiplus::REAL>((rectClient.Width()
            - pInfoHeader->biWidth * m_fZoomRatio) / 2.0);
        m_destRect.Y = 
            static_cast<Gdiplus::REAL>((rectClient.Height()
            - pInfoHeader->biHeight * m_fZoomRatio) / 2.0);
    }
    else
    {
        m_destRect.X =
            static_cast<Gdiplus::REAL>(pt.x - ptImimage.X * m_fZoomRatio);
        m_destRect.Y =
            static_cast<Gdiplus::REAL>(pt.y - ptImimage.Y * m_fZoomRatio);

        if (m_destRect.X > 0 ||
            m_destRect.X + m_destRect.Width < rectClient.right)
        {
            m_destRect.X = 0.0f;
        }

        if (m_destRect.Y > 0 ||
            m_destRect.Y + m_destRect.Height < rectClient.bottom)
        {
            m_destRect.Y = 0.0f;
        }
    }

    return retVal;
}
