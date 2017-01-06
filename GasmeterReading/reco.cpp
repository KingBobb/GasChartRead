#include "reco.h"
//#include "Widgets.h"
#include <string>
#include <iostream>


using namespace std;

string MyReco::reco(Bitmap bmp, int type){
	if (bmp.data == nullptr){
		throw exception("Null pointer @MyReco::reco");
	}
	ChitSDK msdk;
	msdk.SetType(type);
	BYTE *tmp = (BYTE*)malloc(bmp.width*bmp.height);
	//识别图像时先把它倒过来
	for (int i = 0; i < bmp.height; i++){
		for (int j = 0; j < bmp.width; j++){
			if (bmp.channels == 3)
				*(tmp + i*bmp.width + j) = *(bmp.data + (bmp.height-1-i)*bmp.step + 3 * j);
			else if (bmp.channels == 1)
				*(tmp + i*bmp.width + j) = *(bmp.data + (bmp.height-1-i)*bmp.step + j);
			else{
				free(tmp);
				throw exception("It is not a 1 or 3 channel Image @MyReco::reco");
			}
			
		}
	}
	BmpDataInfo tbmp;
	tbmp.bmpBuf = tmp;
	tbmp.height = bmp.height;
	tbmp.width = bmp.width;
	tbmp.top = 0;
	tbmp.left = 0;
	msdk.OffRecog(tbmp);
	string res(msdk.m_result);
	//msdk.~ChitSDK();
	free(tmp);
	return res;
}


bool MyReco::recoAll(Bitmap bmp, ChitSDK & msdk, int type){
	if (bmp.data == nullptr){
		throw exception("Null pointer @MyReco::reco");
		return false;
	}
	//ChitSDK msdk;
	msdk.SetType(type);
	BYTE *tmp = (BYTE*)malloc(bmp.width*bmp.height);
	//识别图像时先把它倒过来
	for (int i = 0; i < bmp.height; i++){
		for (int j = 0; j < bmp.width; j++){
			if (bmp.channels == 3)
				*(tmp + i*bmp.width + j) = *(bmp.data + (bmp.height - 1 - i)*bmp.step + 3 * j);
			else if (bmp.channels == 1)
				*(tmp + i*bmp.width + j) = *(bmp.data + (bmp.height - 1 - i)*bmp.step + j);
			else{
				free(tmp);
				throw exception("It is not a 1 or 3 channel Image @MyReco::reco");
			}

		}
	}
	BmpDataInfo tbmp;
	tbmp.bmpBuf = tmp;
	tbmp.height = bmp.height;
	tbmp.width = bmp.width;
	tbmp.top = 0;
	tbmp.left = 0;
	msdk.OffRecog(tbmp);
	//string res(msdk.m_result);
	//msdk.~ChitSDK();
	free(tmp);
	return true;
}
//-----------------------------------------------------------opencv---------------------------------------------------------------------
/*string MyReco::reco(IplImage* word,int type){
	if (!word){
		throw exception("Null pointer error @MyReco::reco");
	}
	ChitSDK msdk;
	msdk.SetType(type);
	BYTE *tmp = (BYTE*)malloc(word->width*word->height);
	for (int i = 0; i < word->height; i++){
		for (int j = 0; j < word->width; j++){
			if (word->nChannels == 3)
				*(tmp + i*word->width + j) = *((BYTE*)word->imageData + i*word->widthStep + 3 * j);//3 channels
			else if (word->nChannels == 1)
				*(tmp + i*word->width + j) = *((BYTE*)word->imageData + i*word->widthStep + j);//1 channel
			else
				throw exception("It is not a 1 or 3 channel Image @MyReco::reco");
		}
	}
	BmpDataInfo tbmp;
	tbmp.bmpBuf = tmp;
	tbmp.height = word->height;
	tbmp.width = word->width;
	tbmp.top = 0;
	tbmp.left = 0;
	msdk.OffRecog(tbmp);
	string res(msdk.m_result);
	free(tmp);
	return res;
}*/