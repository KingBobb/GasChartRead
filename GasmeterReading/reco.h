#pragma once
#include "afxwin.h"
#include "hitSDK.h"
#pragma comment(lib,"hitSDK.lib")
#include <iostream>
#include <string>
//#include <opencv.hpp>
#include "Bitmap.h"

using namespace std;

#ifndef _MYRECO_
#define _MYRECO_
class MyReco{
public:
	string reco(Bitmap bmp, int type);
	bool MyReco::recoAll(Bitmap bmp, ChitSDK & msdk, int type);
	//---------------------------opencv---------------------
	//string reco(IplImage* word,int type);
};
#endif
