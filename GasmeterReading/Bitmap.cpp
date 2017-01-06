#include "Bitmap.h"

Bitmap::Bitmap(){
	width = 0;
	height = 0;
	step = 0;
	data = 0;
	channels = 0;
	bitcount = 0;
}
void Bitmap::clear(){
	if (data != 0){
		delete[] data;
		data = 0;
	}
}

Bitmap& Bitmap::operator=(const Bitmap &rhs){
	width = rhs.width;
	height = rhs.height;
	step = rhs.step;
	channels = rhs.channels;
	bitcount = rhs.bitcount;
	data = new xBYTE[step*height];
	memcpy(data, rhs.data, step*height);
	return *this;
}

bool Bitmap::read(const char *filename){
	xBITMAPINFOHEADER strInfo;
	xRGBQUAD strPla[256];
	FILE* fp;
	fopen_s(&fp, filename, "rb");
	if (fp == NULL){
		char tmp[256];
		sprintf(tmp, "%s\nRead file failed @Bitmap::read", filename);
		cout << tmp << endl;
		return false;
	}
	fseek(fp, 14, 0);	//jump head
	fread(&strInfo, 1, sizeof(xBITMAPINFOHEADER), fp);
	for (unsigned int nCounti = 0; nCounti < strInfo.biClrUsed; nCounti++){
		//存储的时候，一般去掉保留字rgbReserved  
		fread((char *)&strPla[nCounti].rgbBlue, 1, sizeof(xBYTE), fp);
		fread((char *)&strPla[nCounti].rgbGreen, 1, sizeof(xBYTE), fp);
		fread((char *)&strPla[nCounti].rgbRed, 1, sizeof(xBYTE), fp);
		fread((char *)&strPla[nCounti].rgbReserved, 1, sizeof(xBYTE), fp);
	}
	width = strInfo.biWidth;
	height = strInfo.biHeight;
	bitcount = strInfo.biBitCount;
	switch (bitcount)
	{
	case 24:
		channels = 3;
		step = (3 * width + 3) / 4 * 4;
		break;
	case 8:
		channels = 1;
		step = (width + 3) / 4 * 4;
		break;
	case 1:
		channels = 1;
		step = ((width + 7) / 8 + 3) / 4 * 4;
		break;
	default:
		cout << "Unknown bitcount value=" << bitcount << endl;
		return false;
	}
	long size = step*height;
	this->clear();
	data = new xBYTE[size];
	fread(data, 1, size, fp);
	fclose(fp);
	//cout << bitcount << endl;
	return true;
}
bool Bitmap::save(const char *filename){
	xBITMAPFILEHEADER head;
	xBITMAPINFOHEADER info;
	xRGBQUAD quad[256];
	
	FILE* fp;
	fopen_s(&fp, filename, "wb");
	if (fp == NULL) {
		//throw exception("Open file failed @Bitmap::save");
		cout << "Open file failed @Bitmap::save" << endl;
		return false;
	}
	if (data == 0){
		cout << "No data @Bitmap::save" << endl;
		return false;
	}
	long widthBytes = (3 * width + 3) / 4 * 4;
	info.biBitCount = bitcount;
	info.biClrImportant = 0;
	switch (bitcount){
	case 8:
		info.biClrUsed = 256;
		widthBytes = (width + 3) / 4 * 4;
		break;
	case 1:
		info.biClrUsed = 2;
		widthBytes = ((width + 7) / 8 + 3) / 4 * 4;
		break;
	case 2:
		info.biBitCount = 8;
		info.biClrUsed = 256;
		widthBytes = (width + 3) / 4 * 4;
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				if (*(data + i*widthBytes + j) == 1){
					*(data + i*widthBytes + j) = 255;
				}
			}
		}
		break;
	default:
		info.biClrUsed = 0;
	}
	info.biCompression = 0;
	info.biHeight = height;
	info.biPlanes = 1;
	info.biSize = sizeof(xBITMAPINFOHEADER);
	info.biSizeImage = widthBytes*height;
	info.biWidth = width;
	info.biXPelsPerMeter = 0;
	info.biYPelsPerMeter = 0;

	head.bfType = 0x4d42;
	head.bfOffBits = 54 + info.biClrUsed*sizeof(xRGBQUAD);
	head.bfReserved1 = 0;
	head.bfReserved2 = 0;
	head.bfSize = head.bfOffBits + info.biSizeImage;

	fwrite(&head.bfType, 1, sizeof(xWORD), fp);
	fwrite(&head.bfSize, 1, sizeof(xDWORD), fp);
	fwrite(&head.bfReserved1, 1, sizeof(xWORD), fp);
	fwrite(&head.bfReserved2, 1, sizeof(xWORD), fp);
	fwrite(&head.bfOffBits, 1, sizeof(xDWORD), fp);
	fwrite(&info, 1, sizeof(xBITMAPINFOHEADER), fp);
	//初始化调色板
	for (unsigned int nCounti = 0; nCounti<info.biClrUsed; nCounti++)
	{
		quad[nCounti].rgbBlue = nCounti;
		quad[nCounti].rgbGreen = nCounti;
		quad[nCounti].rgbRed = nCounti;
		quad[nCounti].rgbReserved = 0;
	}
	if (bitcount == 1){
		quad[1].rgbBlue = 255;
		quad[1].rgbGreen = 255;
		quad[1].rgbRed = 255;
	}
	//写入调色板信息
	for (unsigned int nCounti = 0; nCounti<info.biClrUsed; nCounti++)
	{
		fwrite(&quad[nCounti].rgbBlue, 1, sizeof(xBYTE), fp);
		fwrite(&quad[nCounti].rgbGreen, 1, sizeof(xBYTE), fp);
		fwrite(&quad[nCounti].rgbRed, 1, sizeof(xBYTE), fp);
		fwrite(&quad[nCounti].rgbReserved, 1, sizeof(xBYTE), fp);
	}
	fwrite(data, 1, widthBytes*height, fp);
	fclose(fp);
	return true;
}

//-----------------------------------------------------opencv---------------------------------------------------------------------------
/*Bitmap::Bitmap(IplImage *img){
	if (!img){
		width = 0;
		height = 0;
		step = 0;
		data = 0;
		channels = 0;
		printf("Constructor failed @Bitmap::Bitmap()\n");
		return;
	}
	width = img->width;
	height = img->height;
	step = img->widthStep;
	channels = img->nChannels;
	
	data = (unsigned char*)malloc(height*step*sizeof(unsigned char));
	memset(data, 0, height*step*sizeof(unsigned char));
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (channels == 1){
				*(data + i*step + j) = *((unsigned char*)img->imageData + (img->height-1-i)*img->widthStep + j);
			}
			else if (channels == 3){
				*(data + i*step + 3 * j) = *((unsigned char*)img->imageData + (img->height-1-i)*img->widthStep + 3 * j);
				*(data + i*step + 3 * j + 1) = *((unsigned char*)img->imageData + (img->height-1-i)*img->widthStep + 3 * j + 1);
				*(data + i*step + 3 * j + 2) = *((unsigned char*)img->imageData + (img->height-1-i)*img->widthStep + 3 * j + 2);
			}
		}
	}

}*/