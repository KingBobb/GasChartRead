

#ifndef _LINKNODE_
#define _LINKNODE_
#include <stdio.h>
#include <malloc.h>
#include "Bitmap.h"
#include "DealImage.h"
#include "reco.h"


struct node{
	int left;
	int right;
	struct node *next;
};

//ileft 左列坐标 iright右列坐标，最大值为宽度-1
void recursioncut(struct node* curhead, Bitmap gray, int left, int right);
char* readmeter(const char* filename, int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int p4x, int p4y);
bool mixOfDecimalAndChar(Bitmap gray, int dpoint);
void imrotate(Bitmap src, Bitmap& dst, double theta);
void imtangent(Bitmap src, Bitmap& dst, double factor);

#endif
