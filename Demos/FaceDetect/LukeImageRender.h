#pragma once
//#include <gdiplus.h>


struct PromptImfo
{
    PromptImfo()
        : textColor(Gdiplus::Color(255, 255, 0, 0))
        , strPromptInfo(_T(""))
    {};

    /// prompt info to show in the render control
    CString strPromptInfo;
    /// the color used to render the text
    Gdiplus::Color textColor;
};

/**
 * \class CLukeImageRender LukeImageRender.h
 * \brief Wrapper for show DIB image in windows frame
 * \author RuralMouse
 * \date 2014-2-10 11:32
 */
class CLukeImageRender : public CWnd
{
private:
    enum PROMPT_POS
    {
        TOP_LEFT = 0,
        TOP_MIDDLE = 1,
        TOP_RIGHT = 2,
        MID_LEFT = 3,
        MID_CENTER = 4,
        MID_RIGHT = 5,
        BOTTOM_LEFT = 6,
        BOTTOM_DENTER = 7,
        BOTTOM_RIGHT = 8
    };

    DECLARE_DYNAMIC(CLukeImageRender)

public:
    CLukeImageRender(const CString& promptInfo = _T("No image to render"),
        const BOOL bAutoZoom = TRUE);
    virtual ~CLukeImageRender();

protected:
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    DECLARE_MESSAGE_MAP()

public:
    /**
     * \brief interface for input dib image for render
     * \param[in] byDIBImage DIB data pointer for render
     * \param[in] dibSize length of DIB date
     * \return NONE
     */
    void RenderImage(BYTE* byDIBImage,const int dibSize);

    /**
     * \brief calculate image render position
     * \param[in] zoomFashion zoom fashion 0 for first, 1 for enlarge, 2 for compress
     * \return 1 for horizontal cant zoom in, 2 for vertical, 3 for both
     */
    int CalculateDestPos(CPoint& pt, const int zoomFashion = 0);

    /// Clear current DIB image for blank
    void ClearImage();

    /// Clear Image and prompt info
    void ClearImagePrompt();

    /// Response parent frame resize message
    void ResizeClient();

    /// Add string to show on image
    void UpdatePromptString(const int propPos, const CString& strPrompt,
        const Gdiplus::Color& clrPrompt = Gdiplus::Color(255, 255, 0, 0) );

    /// remove prompt string by postion index
    void RemovePromptString(const int propPos);

    /**
     * \brief get current render data for some usage
     * \param[in,out] imageSize input -1 to get imagesize
     * \param[in,out] imageDIBData NULL for get size,otherwise user should manage memory himself
     * \return FALSE when there is no image
     */
    BOOL GetRenderImageData(int &imageSize, BYTE*& imageDIBData);

    /**
     * \brief zoom contained image 
     * \param[in] pt zoom center
     * \param[in] bZoomIn zoom in or out
     * \retval as following 
     -# 0 zoom success
     -# 1 horizontal can no more zoom in
     -# 2 virtical can no more zoom in
     -# 3 both direction can no more zoom in
     -# 4 pt not in image
     -# 5 horizontal can not zoom out
     -# 6 virtical can not zoom out
     */
    int ZoomImage(const CPoint& pt, const BOOL bZoomIn);

    /**
     * \brief move image position
     * \param[in] xStep move size in horizontal 
     * \param[in] yStep move size in vertical
     * \return NONE
     */
    int MoveImage(const int xStep, int yStep);

    CRect GetImageShowPos();

protected:
    /// image dib data to render
    BYTE *              m_pByImageData;
    /// size of m_pByImageData in byte
    int                 m_nDibSize;
    /// brush to fill when image is null
    Gdiplus::Brush *    m_pBrBackground;
    /// flag whether the control should re-calculate the image render pos
    BOOL                m_bFirst;
    /// where to render the input image
    Gdiplus::RectF      m_destRect;

    Gdiplus::REAL       m_fZoomRatio;
    /// prompt string to show in the string, array pos simular to PROMPT_POS definition
    PromptImfo          m_promptInfo[9];
    /// prompt string when there is no image
    CString             m_nullPromptInfo;
    /// whether zoom image auto
    BOOL                m_bAutoZoomImage;

    /**
     * \brief detect image position in CLukeImageRender object
     * \param[in] rcWnd CLukeImageRender object pointer
     * \param[in] imageWidth width of image to be rendered
     * \param[in] imageHeight height of image to be rendered
     * \param[out] dRatio press rate of image
     * \param[in] bCenter should the image put in center of rcWnd client frame
     * \param[in] bStretch should the image be stretch when it is smaller than rcWnd client frame
     * \return destination rect
     */
    Gdiplus::RectF GetImagePos( CRect* rcWnd,
        const int imageWidth,
        const int imageHeight,
        const BOOL bCenter = TRUE,
        const BOOL bStretch = TRUE);

    /// inner function to render prompt sting
    void ShowPromptInfo(Gdiplus::Graphics& graphic);

    /**
     * \brief calculate where to show promt string in the control
     * \param[in] posIndex value \see PROMPT_POS
     * \param[out] aligmentType how to alig the string
     * \return where to show prompt string
     */
    Gdiplus::RectF GetPromptShowPos( const int posIndex,
        Gdiplus::StringAlignment& aligmentType);
};

