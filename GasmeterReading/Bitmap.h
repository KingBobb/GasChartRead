#include <iostream>

using namespace std;

#ifndef _BITMAP_
#define _BITMAP_
#define xBYTE unsigned char
#define xWORD unsigned short
#define xDWORD unsigned long
typedef struct xtagBITMAPFILEHEADER {
	xWORD    bfType;
	xDWORD   bfSize;
	xWORD    bfReserved1;
	xWORD    bfReserved2;
	xDWORD   bfOffBits;
} xBITMAPFILEHEADER;
typedef struct xtagBITMAPINFOHEADER{
	xDWORD      biSize;
	long      biWidth;
	long       biHeight;
	xWORD       biPlanes;
	xWORD       biBitCount;
	xDWORD      biCompression;
	xDWORD      biSizeImage;
	long       biXPelsPerMeter;
	long       biYPelsPerMeter;
	xDWORD      biClrUsed;
	xDWORD      biClrImportant;
} xBITMAPINFOHEADER;
typedef struct xtagRGBQUAD {
	xBYTE    rgbBlue;
	xBYTE    rgbGreen;
	xBYTE    rgbRed;
	xBYTE    rgbReserved;
} xRGBQUAD;

class Bitmap{
public:
	long width;
	long height;
	long step;
	unsigned char *data;
	int channels;
	int bitcount;
	//--------------------------------------------func-------------------------------------
	Bitmap();
	void clear();
	Bitmap& operator=(const Bitmap &rhs);

	bool save(const char* filename);
	bool read(const char* filename);
	//--------------------------------------------opencv-----------------------------------
	//Bitmap(IplImage *image);
};
#endif