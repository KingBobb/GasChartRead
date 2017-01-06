#include  "pretreatment.h"
#include <math.h>
#include "jpeg2bmp.h"
void  Pretreatment::pretreat(const char* file)
{

	//LPCWSTR file;
	const char* tempfile = "gmtemp.bmp";
	read_jpeg_file(file, tempfile);
	long widthBytes, widthBytes1, width, height;
	//读入图像
	Bitmap trgb;
	trgb.read(tempfile);
	xBYTE *rgb = trgb.data;
	widthBytes = trgb.step;
	width = trgb.width;
	height = trgb.height;
	widthBytes1 = (width + 3) / 4 * 4;

	int i, j, k;

	xBYTE *red = (xBYTE*)malloc(sizeof(xBYTE)*width*height);
	xBYTE *blue = (xBYTE*)malloc(sizeof(xBYTE)*width*height);
	xBYTE *green = (xBYTE*)malloc(sizeof(xBYTE)*width*height);
	double *Y = (double*)malloc(sizeof(double)*width*height);
	double *U = (double*)malloc(sizeof(double)*width*height);
	double *V = (double*)malloc(sizeof(double)*width*height);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			*(blue + i*width + j) = *(rgb + i*widthBytes + j * 3 + 0);
			*(green + i*width + j) = *(rgb + i*widthBytes + j * 3 + 1);
			*(red + i*width + j) = *(rgb + i*widthBytes + j * 3 + 2);
		}
	}
	
	//将RGB空间转换到YUV空间
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			//转换公式：
			*(Y + i*width + j) = 0.257*(*(red + i*width + j)) + 0.504*(*(green + i*width + j)) + 0.098*(*(blue + i*width + j)) + 16;
			*(U + i*width + j) = -0.148*(*(red + i*width + j)) - 0.291*(*(green + i*width + j)) + 0.439*(*(blue + i*width + j)) + 128;
			*(V + i*width + j) = 0.439*(*(red + i*width + j)) - 0.368*(*(green + i*width + j)) - 0.071*(*(blue + i*width + j)) + 128;
	
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			//亮度归一化
			*(Y + i*width + j) = double(*(Y + i*width + j)) / 255;
			if (*(Y + i*width + j) > 0.66 && *(Y + i*width + j) < 0.9215)
			{
				*(Y + i*width + j) = 2.6136*powl(*(Y + i*width + j), 4) - 4.034*powl(*(Y + i*width + j), 3) + 1.1065*powl(*(Y + i*width + j),2) + 1.10105**(Y + i*width + j) - 0.0053706;
			}

			*(Y + i*width + j) =int((*(Y + i*width + j)) * 255);
			int  m = *(Y + i*width + j);
		}
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			
			*(rgb + i*widthBytes + j * 3 + 2) = 1.164*(*(Y + i*width + j) - 16) + 1.596*(*(V + i*width + j) - 128);
			*(rgb + i*widthBytes + j * 3 + 1) = 1.164*(*(Y + i*width + j) - 16) - 0.813*(*(V + i*width + j) - 128) - 0.392*(*(U + i*width + j) - 128);
			*(rgb + i*widthBytes + j * 3 + 0) = 1.164*(*(Y + i*width + j) - 16) + 2.017*(*(U + i*width + j) - 128);		
		}
	}

	trgb.save(tempfile);
	free(red);
	free(green);
	free(blue);
	free(Y);
	free(U);
	free(V);
	trgb.clear();
}