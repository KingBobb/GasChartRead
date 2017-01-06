#include "DealImage.h"
#include <iomanip>
#include <math.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

bool DealImage::rgb2gray(Bitmap rgb, Bitmap &gray){
	if (rgb.data == 0){
		cout << "Null pointer rgb @DealImage::rgb2gray" << endl;
		return false;
	}
	if (rgb.channels != 3){
		cout << "Not a 3 channel image @DealImage::rgb2gray" << endl;
		return false;
	}
	if (gray.data != 0){
		cout << "Do not allocate gray @DealImage::rgb2gray" << endl;
		return false;
	}
	gray.width = rgb.width;
	gray.height = rgb.height;
	gray.channels = 1;
	gray.bitcount = 8;
	gray.step = (gray.width + 3) / 4 * 4;
	gray.data = (unsigned char*)malloc(gray.step*gray.height);
	for (int i = 0; i < gray.height; i++){
		for (int j = 0; j < gray.width; j++){
			unsigned char r = *(rgb.data + i*rgb.step + 3 * j + 2);
			unsigned char g = *(rgb.data + i*rgb.step + 3 * j + 1);
			unsigned char b = *(rgb.data + i*rgb.step + 3 * j);
			unsigned char grayvalue = (unsigned char)(0.299*r + 0.587*g + 0.114*b);
			*(gray.data + i*gray.step + j) = grayvalue;
		}
	}
	return true;
}

int* DealImage::sums(Bitmap bmp, int mode){
	if (bmp.data == 0){
		cout<<"Null pointer bmp @DealImage::sums" << endl;
		return NULL;
	}
	int *proj = NULL;
	if (mode == 1){
		proj = (int*)malloc(bmp.width*sizeof(int));
		/*if (proj == NULL)	throw exception("Allocate failed @DealImage::sums()");*/
		for (int i = 0; i < bmp.width; i++){
			int sumOfCol = 0;
			for (int j = 0; j < bmp.height; j++){
				sumOfCol += *(bmp.data + j*bmp.step + i);
			}
			*(proj + i) = sumOfCol;
		}
	}
	else{
		proj = (int*)malloc(bmp.height*sizeof(int));
		/*if (proj == NULL)	throw exception("Allocate failed @DealImage::sums()");*/
		for (int i = 0; i < bmp.height; i++){
			int sumOfRow = 0;
			for (int j = 0; j < bmp.width; j++){
				sumOfRow += *(bmp.data + i*bmp.step + j);
			}
			*(proj + i) = sumOfRow;
		}
		int tmp;
		for (int i = 0; i < bmp.height; i++){
			if (i >= bmp.height - i - 1) break;
			tmp = proj[bmp.height - i - 1];
			proj[bmp.height - i - 1] = proj[i];
			proj[i] = tmp;
		}
	}
	return proj;
}

bool DealImage::im2bws(Bitmap gray, Bitmap &bw,int thresh){
	if (gray.data == 0){
		cout << "Null pointer gray @DealImage::im2bws" << endl;
		return false;
	}
	if (bw.data != 0){
		cout << "Do not Allocate bw @DealImage::im2bws" << endl;
		return false;
	}
	bw.width = gray.width;
	bw.height = gray.height;
	bw.channels = 1;
	bw.bitcount = 8;
	bw.step = (bw.width + 3) / 4 * 4;
	bw.data = (unsigned char*)malloc(bw.step*bw.height);
	for (int i = 0; i < bw.height; i++){
		for (int j = 0; j < bw.width; j++){
			if (gray.data[i*gray.step + j] <= thresh){
				bw.data[i*bw.step + j] = 1;
			}
			else{
				bw.data[i*bw.step + j] = 0;
			}
		}
	}
	return true;
}

int DealImage::graythresh(Bitmap gray){
	if (gray.data == 0){
		cout<<"Null pointer @DealImage::graythresh" << endl;
		return 0;
	}
	if (gray.channels != 1){
		cout << "Not a 1 channel image @DealImage::graythresh" << endl;
		return 0;
	}
	long chart[256];
	memset(chart, 0, sizeof(chart));
	for (int i = 0; i < gray.height; i++){
		for (int j = 0; j < gray.width; j++){
			chart[(int)(gray.data[i*gray.step + j])]++;
		}
	}
		double pi[256];
		double variance[256];
		int sumNum = gray.height*gray.width;
		memset(pi, 0, sizeof(pi));
		memset(variance, 0, sizeof(variance));

		double pa = 0.0, pb = 0.0;
		double wa = 0.0, wb = 0.0, w0 = 0.0;
		double ja = 0.0, jb = 0.0;
		for (int i = 0; i < 256; i++){
			pi[i] = (double)chart[i] / (double)sumNum;
			w0 += i*pi[i];
		}
		for (int i = 0; i < 256; i++){
			pa += pi[i];
			pb = 1 - pa;
			wa += i*pi[i];
			wb = w0 - wa;
			if (pa != 0){
				ja = wa / pa;
				jb = wb / pb;
				variance[i] = pa*pb*(ja - jb)*(ja - jb);
			}
			else{
				variance[i] = 0;
			}
		}
		float max = variance[0];
		int maxIndex = 0;
		for (int i = 0; i < 256; i++){
			if (max < variance[i]){
				max = variance[i];
				maxIndex = i;
			}
		}
	return maxIndex;
}

bool DealImage::cutBmp(Bitmap img, Bitmap &part, Rect rc){
	//check border
	if (rc.x + rc.w > img.width ){
		cout << "Width index out of range @DealBmp::cutBmp" << endl;
		return false;
	}
	if (rc.y + rc.h > img.height){
		cout << "Height index out of range @DealBmp::cutBmp" << endl;
		return false;
	}
	//assign params
	long pstep = 0;
	switch (img.bitcount)
	{
	case 24:
		pstep = (3 * rc.w + 3) / 4 * 4;
		break;
	case 8:
		pstep = (rc.w + 3) / 4 * 4;
		break;
	default:
		cout << "Cannot cut bitmap because bitcount=" << img.bitcount << " @DealBmp::cutBmp" << endl;
		return false;
	}
	part.bitcount = img.bitcount;
	part.channels = img.channels;
	part.height = rc.h;
	part.width = rc.w;
	part.step = pstep;
	part.data = new xBYTE[part.step*part.height];
	memset(part.data, 0, part.step*part.height);
	if (part.bitcount == 8){
		for (int i = 0; i < rc.h; i++){
			for (int j = 0; j < rc.w; j++){
				/*if ((part.height - 1 - i < 0) || (img.height - 1 - rc.y - i < 0)){
				cout << "Access violation @DealBmp::cutBmp" << endl;
				return false;
				}*/
				part.data[(part.height - 1 - i)*part.step + j] = img.data[(img.height - 1 - rc.y - i)*img.step + (rc.x + j)];

				//part.data[i*part.step + j] = img.data[(rc.y + i)*img.step + (rc.x + j)];
			}
		}
	}
	else if (part.bitcount == 24){
		for (int i = 0; i < rc.h; i++){
			for (int j = 0; j < rc.w; j++){
				/*if ((part.height - 1 - i < 0) || (img.height - 1 - rc.y - i < 0)){
				cout << "Access violation @DealBmp::cutBmp" << endl;
				return false;
				}*/
				part.data[(part.height - 1 - i)*part.step + 3 * j] = img.data[(img.height - 1 - rc.y - i)*img.step + 3 * (rc.x + j)];
				part.data[(part.height - 1 - i)*part.step + 3 * j + 1] = img.data[(img.height - 1 - rc.y - i)*img.step + 3 * (rc.x + j) + 1];
				part.data[(part.height - 1 - i)*part.step + 3 * j + 2] = img.data[(img.height - 1 - rc.y - i)*img.step + 3 * (rc.x + j) + 2];

				//part.data[i*part.step + 3 * j] = img.data[(rc.y + i)*img.step + 3 * (rc.x + j)];
				//part.data[i*part.step + 3 * j + 1] = img.data[(rc.y + i)*img.step + 3 * (rc.x + j) + 1];
				//part.data[i*part.step + 3 * j + 2] = img.data[(rc.y + i)*img.step + 3 * (rc.x + j) + 2];
			}
		}
	}
	else{
		cout << "It cannot happen" << endl;
	}
	return true;
}

