#include <iostream>
//#include <opencv.hpp>
#include "Bitmap.h"


using namespace std;

#ifndef _DEALIMAGE_
#define _DEALIMAGE_
struct Rect{
	long x;		//start point (x,y)
	long y;
	long w;		//width
	long h;		//height

	Rect(long startx = 0, long starty = 0, long width = 0, long height = 0) :x(startx), y(starty), w(width), h(height){}
};
class DealImage{
public:
	bool rgb2gray(Bitmap rgb, Bitmap &gray);

	int* sums(Bitmap bmp, int mode);

	bool im2bws(Bitmap gray, Bitmap &bw,int thresh);

	int graythresh(Bitmap gray);

	bool cutBmp(Bitmap img, Bitmap &part, Rect rc);
};
#endif