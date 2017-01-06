#pragma once

struct BITMAPINFO256 {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[256];
};

struct BmpDataInfo {
	BYTE *bmpBuf;
	int width;
	int height;
	int left;
	int top;

	BmpDataInfo(BYTE *buf = 0, int w = 0, int h = 0,int l=0,int t=0): bmpBuf(buf), width(w), height(h),left(l),top(t) {}
};

/* rectangle with int values */
struct IRect {
	int left;
	int right;
	int top;
	int bottom;

	IRect(int l = 0, int t = 0, int r = 0, int b = 0): left(l), top(t), right(r), bottom(b) {}

	int GetWidth() const { return right - left + 1; }
	int GetHeight() const { return bottom - top + 1; }
};

/**
 * π§æﬂ¿‡
 
class CWidgets
{
public:
	CWidgets(void);
	~CWidgets(void);

public:
    static char* CStringToCharArray(const CString &str);
	static void InitBITMAPINFO(BITMAPINFO256 &destBmi, int width, int height);
	static void SaveBmp(BmpDataInfo bmpData, const char *fileName);

	static bool CopyBmpData(BmpDataInfo destBmp, int destLeft, int destTop,
		BmpDataInfo srcBmp, IRect srcRect,int emptyPixVal = 255, bool reverseVal = false);
};
*/
