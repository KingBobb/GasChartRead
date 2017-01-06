#include "DecimalPoint.h"

const double pi = 3.1415926f;
const double PI = 3.1415926;

int graythresh(Bitmap gray);
int* projection(xBYTE* data, int height, int width, long left, long right, long top, long bottom, bool horizontal);
int normalize(Bitmap src, double* &dst, double alpha, double beta);
int normalize(double *src, Bitmap &dst, xBYTE alpha, xBYTE beta);
double* filter(double* src, int width, int height, double* kernel, int ksize, bool padtype = true);
vector<double> create_sigma(double start, double step, double end);

//功能：
double* create_LOG(int size, double sigma, double ratio = 0, bool reverse = true);
double* create_cos(int size, double T);
int localBinarization(Bitmap gray, Bitmap &bw, int rectH, int rectW);
int reverse(Bitmap &gray);
void setNumber(int *connect, int w, int x, int y, int min);
int connectedRegion(Bitmap bw, Bitmap &connected);
void findPoint(Bitmap bw, Bitmap &result, int checksize);
int checkPoint(Bitmap &result, Bitmap gray, int thresh);


int graythresh(Bitmap gray){
	if (gray.data == 0){
		cout << "Null pointer @DealImage::graythresh" << endl;
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
int* projection(xBYTE* data, int height, int width, long left, long right, long top, long bottom, bool horizontal){
	//int *proHori,*proVerti;
	int subHeight = bottom - top + 1;
	int subWidth = right - left + 1;
	int tempt = height - 1 - top;
	int tempb = height - 1 - bottom;
	if (horizontal){
		//int *proHori = (int*)malloc(subWidth*sizeof(int));
		int *proHori = new int[subWidth];
		//proHori = new int[subWidth];
		if (proHori == NULL) throw exception("Allocation failed @DealImage::projection");
		for (int i = 0; i < subWidth; i++){
			proHori[i] = 0;
		}
		int temp;
		for (int i = tempb; i <= tempt; i++){
			temp = i*((width + 3) / 4 * 4) + left;
			for (int j = 0; j < subWidth; j++){
				if (int(*(data + temp + j)) > 0){
					proHori[j]++;
				}
			}
		}
		return proHori;
	}
	else{
		//int* proVerti = (int*)malloc(subHeight*sizeof(int));
		int *proVerti = new int[subHeight];
		//proVerti = new int[subHeight];
		if (proVerti == NULL) throw exception("Allocation failed @DealImage::projection");
		for (int i = 0; i < subHeight; i++){
			proVerti[i] = 0;
		}
		int temp;
		for (int i = 0; i < subHeight; i++){
			temp = (tempt - i)*((width + 3) / 4 * 4);
			for (int j = left; j < right; j++){
				if (int(*(data + temp + j)) > 0){
					proVerti[i]++;
				}
			}
		}
		return proVerti;
	}
}
int normalize(Bitmap src, double* &dst, double alpha, double beta){
	if (src.bitcount != 8){
		return 1;
	}
	dst = new double[src.height*src.width];
	int max = 0, min = 255;
	for (int i = 0; i < src.height; i++){
		for (int j = 0; j < src.width; j++){
			if (src.data[i*src.step + j]>max)
				max = src.data[i*src.step + j];
			if (src.data[i*src.step + j] < min)
				min = src.data[i*src.step + j];
		}
	}
	int ss = max - min;
	double sd = beta - alpha;
	for (int i = 0; i < src.height; i++){
		for (int j = 0; j < src.width; j++){
			dst[i*src.width + j] = (src.data[i*src.step + j] - min)*sd / double(ss) + alpha;
		}
	}
	return 0;
}
int normalize(double *src, Bitmap &dst, xBYTE alpha, xBYTE beta){
	if (dst.bitcount != 8){
		return 1;
	}
	double max = -255, min = 255;
	//double temp;//zjc
	for (int i = 0; i < dst.height; i++){
		for (int j = 0; j < dst.width; j++){
			if (src[i*dst.width + j]<0){
				src[i*dst.width + j] = 0;
			}
			if (src[i*dst.width + j] > max){
				//temp = max;//zjc
				max = src[i*dst.width + j];
			}
			if (src[i*dst.width + j] < min)
				min = src[i*dst.width + j];
		}
	}
	//cout << "max:" << max <<" "<< temp << endl;//zjc
	double ss = max - min;
	int sd = beta - alpha;
	for (int i = 0; i < dst.height; i++){
		for (int j = 0; j < dst.width; j++){
			dst.data[i*dst.step + j] = xBYTE((src[i*dst.width + j] - min)*sd / ss + alpha);
		}
	}
	return 0;
}
double* filter(double* src, int width, int height, double* kernel, int ksize, bool padtype){
	const int shift = ksize / 2;
	//make padded image
	int pheight = height + 2 * shift;
	int pwidth = width + 2 * shift;
	double* padded = new double[pheight*pwidth];
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			padded[(shift + i)*pwidth + shift + j] = src[i*width + j];
		}
	}
	if (padtype){
		for (int i = 0; i < shift; i++){
			for (int j = 0; j < width; j++){
				padded[i*pwidth + shift + j] = src[j];
				padded[(height + shift + i)*pwidth + shift + j] = src[(height - 1)*width + j];
			}
		}
		for (int i = 0; i < height; i++){
			for (int j = 0; j < shift; j++){
				padded[(shift + i)*pwidth + j] = src[i*width];
				padded[(shift + i)*pwidth + shift + width + j] = src[i*width + width - 1];
			}
		}
		for (int i = 0; i < shift; i++){
			for (int j = 0; j < shift; j++){
				padded[i*pwidth + j] = src[0];
				padded[(shift + height + i)*pwidth + j] = src[(height - 1)*width];
				padded[i*pwidth + shift + width + j] = src[width - 1];
				padded[(shift + height + i)*pwidth + shift + width + j] = src[height*width - 1];
			}
		}
	}
	else{
		for (int i = 0; i < shift; i++){
			for (int j = 0; j < pwidth; j++){
				padded[i*pwidth + j] = 0;
				padded[(height + shift + i)*pwidth + j] = 0;
			}
		}
		for (int i = 0; i < pheight; i++){
			for (int j = 0; j < shift; j++){
				padded[(i)*pwidth + j] = 0;
				padded[(i)*pwidth + shift + width + j] = 0;
			}
		}
	}
	//use padded image filter
	int i, j, k, l;
	double sum;
	double* dst = new double[width*height];
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			sum = 0;
			for (k = 0; k < ksize; k++){
				for (l = 0; l < ksize; l++){
					sum += kernel[k*ksize + l] * padded[(i + k)*pwidth + j + l];
				}
			}
			dst[i*width + j] = sum;
		}
	}

	delete[] padded;
	return dst;
}
vector<double> create_sigma(double start, double step, double end)
{
	vector<double> sigma;
	while (start <= end + 1e-8){
		double s = exp(start);
		sigma.push_back(s);
		// << s << " ";
		start += step;
	}
	return sigma;
}
double* create_LOG(int size, double sigma, double ratio, bool reverse)
{
	if (ratio>1 || ratio<0)
		return NULL;
	double* H = new double[size*size];

	int cx = (size - 1) / 2;
	int cy = (size - 1) / 2;
	double s0 = 1 / (3.1415926 * sigma*sigma);
	if (reverse)
		s0 = -s0;
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int nx = i - cx;
			int ny = j - cy;
			double t = (nx*nx + ny*ny) / (2 * sigma*sigma);
			double s = s0*(1 - t)*exp(-t);
			sum += s;
			H[i*size + j] = s;
		}
	}

	double mean = sum / (size*size);
	//cout << mean;
	double th = mean + (s0 - mean)*ratio;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			H[i*size + j] -= th;
		}
	}
	/*/
	cout << "核：";
	for (int i = 0; i < size; i++){
	for (int j = 0; j < size; j++){
	cout << H[i*size+j] << " ";
	}
	cout << endl;
	}
	cout<<endl;
	//*/
	return H;
}
double* create_cos(int size, double T){
	double* H = new double[size*size];

	int cx = (size - 1) / 2;
	int cy = (size - 1) / 2;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			double nx = i - cx;
			double ny = j - cy;
			nx = nx * 2 * PI / T;
			ny = ny * 2 * PI / T;
			double t = sqrt(nx*nx + ny*ny);
			double s = cos(t);
			H[i*size + j] = s;
		}
	}
	//
	/*/
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << H[i*size + j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	//*/
	return H;
}
int localBinarization(Bitmap gray, Bitmap &bw, int rectH, int rectW){
	if (rectH>gray.height || rectW > gray.width){
		return -1;
	}
	bw = gray;
	bw.bitcount = 2;
	memset(bw.data, 0, bw.step*bw.height*sizeof(xBYTE));
	int sh = gray.height - rectH + 1;
	int sw = gray.width - rectW + 1;
	Bitmap temp;
	temp.bitcount = 8;
	temp.channels = 1;
	temp.height = rectH;
	temp.width = rectW;
	temp.step = (rectW + 3) / 4 * 4;
	temp.data = new xBYTE[temp.step*rectH];
	memset(temp.data, 0, temp.step*rectH*sizeof(xBYTE));
	int i, j, k, l;
	int th;
	for (i = 0; i < sh; i++){
		for (j = 0; j < sw; j++){
			for (k = 0; k < rectH; k++){
				for (l = 0; l < rectW; l++){
					temp.data[(k*temp.step) + l] = gray.data[(i + k)*gray.step + j + l];
				}
			}
			//localEnhance(temp, rectH, rectW);
			th = graythresh(temp);
			for (k = 0; k < rectH; k++){
				for (l = 0; l < rectW; l++){
					if (temp.data[(k*temp.step) + l]>th){
						bw.data[(i + k)*bw.step + j + l] = 1;
					}
				}
			}
		}
	}
	temp.clear();
	return 0;
}
int reverse(Bitmap &gray){
	for (int i = 0; i < gray.height; i++){
		for (int j = 0; j < gray.width; j++){
			gray.data[i*gray.step + j] = 255 - gray.data[i*gray.step + j];
		}
	}
	return 0;
}
//2016.4.24

//connectRegion要使用的一个递归函数
void setNumber(int *connect, int w, int x, int y, int min){
	for (int j = y; connect[x*w + j] != 0; j++){
		connect[x*w + j] = min;
	}
	for (int j = y; connect[x*w + j] != 0; j++){
		if (connect[(x + 1)*w + j] != 0 && connect[(x + 1)*w + j] != min){
			setNumber(connect, w, x + 1, connect[(x + 1)*w + j] % w, min);
		}
	}
	for (int j = y; connect[x*w + j] != 0; j++){
		if (connect[(x - 1)*w + j] != 0 && connect[(x - 1)*w + j] != min){
			setNumber(connect, w, x - 1, connect[(x - 1)*w + j] % w, min);
		}
	}
}

//寻找连通域（在connected中相同数字的点为一个连通域）
//返回值为连通域个数
int connectedRegion(Bitmap bw, Bitmap &connected){
	connected = bw;
	int h = bw.height, w = bw.width;
	int step = bw.step;
	int *padded = new int[(h + 2)*(w + 2)];
	memset(padded, 0, (h + 2)*(w + 2)*sizeof(int));
	//寻找每一行的线段
	int number = 0, flag = 0;
	for (int i = 0; i < h; i++)
	{
		flag = 0;
		for (int j = 0; j < w; j++){
			if (bw.data[i*step + j]){
				if (flag == 0){
					flag = 1;
					number = (i + 1) * (w + 2) + (j + 1);
				}
				padded[(i + 1)*(w + 2) + (j + 1)] = number;
			}
			else if (flag == 1){
				flag = 0;
			}
		}
	}
	//相邻线段组成连通分量
	number = 0;
	for (int i = 1; i < h + 1; i++){
		for (int j = 1; j < w + 1; j++){
			if (padded[i*(w + 2) + j]>number){
				number++;
				setNumber(padded, w + 2, i, j, number);
			}
		}
	}

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			connected.data[i*step + j] = padded[(i + 1)*(w + 2) + (j + 1)];
		}
	}

	delete[] padded;
	return number;
}

//
void findPoint(Bitmap bw, Bitmap &result, int checksize){
	result = bw;
	Bitmap connect;
	connectedRegion(bw, connect);
	int  height = bw.height, width = bw.width;
	int step = bw.step;
	int shift = checksize / 2;
	int ksize = 2 * shift + 1;
	int pheight = height + 2 * shift;
	int pwidth = width + 2 * shift;
	int* padded = new int[pheight*pwidth];
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			padded[(shift + i)*pwidth + shift + j] = connect.data[i*step + j];
		}
	}
	for (int i = 0; i < pheight; i++){
		for (int j = 0; j < shift; j++){
			padded[i*pwidth + j] = 0;
			padded[i*pwidth + shift + width + j] = 0;
		}
	}
	for (int i = 0; i < shift; i++){
		for (int j = 0; j < pwidth; j++){
			padded[i*pwidth + j] = 0;
			padded[(shift + height + i)*pwidth + j] = 0;
		}
	}
	int i, j, k, l;
	int sum;
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			if (connect.data[i*step + j]>0){
				for (k = 0; k < ksize; k++){
					if (padded[(i + k)*pwidth + j] == connect.data[i*step + j]
						|| padded[(i + k)*pwidth + j + ksize - 1] == connect.data[i*step + j]){
						result.data[i*step + j] = 0;
					}
				}
				for (l = 0; l < ksize; l++){
					if (padded[i*pwidth + j + l] == connect.data[i*step + j]
						|| padded[(i + ksize - 1)*pwidth + j + l] == connect.data[i*step + j]){
						result.data[i*step + j] = 0;
					}
				}
			}
			else{
				result.data[i*step + j] = 0;
			}
		}
	}
	connect.clear();
	delete[] padded;
}

int checkPoint(Bitmap &result, Bitmap gray, int thresh){
	int h = result.height, w = result.width;
	int step = result.step;
	for (int i = h / 3; i < h; i++){
		for (int j = 0; j < w; j++){
			result.data[i*step + j] = 0;
		}
	}
	int *proj = projection(result.data, result.height, result.width, 0, result.width - 1, 0, result.height - 1, true);
	int start = 0, end = 0;
	int flag = 0, t = 0;
	for (int i = 0; i < w; i++){
		if (proj[i] > 0){
			if (flag == 0){
				flag = 1;
				t = i;
			}
		}
		else{
			if (flag == 1){
				flag = 0;
				if (end == 0){
					start = t;
					end = i;
				}
				else{
					int sum1 = 0, sum2 = 0;
					for (int k = 0; k < h; k++){
						for (int l = start; l <= end; l++){
							if (result.data[k*step + l]){
								sum1 += gray.data[k*gray.step + l];
							}
						}
					}
					for (int k = 0; k < h; k++){
						for (int l = t; l <= i; l++){
							if (result.data[k*step + l]){
								sum2 += gray.data[k*gray.step + l];
							}
						}
					}
					if (sum1 > sum2){
						for (int k = 0; k < h; k++){
							for (int l = t; l <= i; l++){
								result.data[k*step + l] = 0;
							}
						}
					}
					else{
						for (int k = 0; k < h; k++){
							for (int l = start; l <= end; l++){
								result.data[k*step + l] = 0;
							}
						}
						start = t;
						end = i;
					}
				}
			}
		}
	} 
	//判断是否为小数点
	int max = 0;
	for (int i = 0; i < h; i++){
		for (int j = start; j < end; j++){
			if (result.data[i*step + j] && gray.data[i*step + j]>thresh)
				max = gray.data[i*step + j];
		}
	}

	if (max < thresh){
		return 0;
	}
	else{
		return (start + end) / 2;
	}
}

//int decimalPoint2(Bitmap src){
//	Bitmap gray = src;
//	int times = 3;
//	for (int j = 0; j < times; j++){
//		double* norm1;
//		normalize(gray, norm1, 0, 1);
//		double* log = create_LOG(9, 1.5);
//		double* norm2 = filter(norm1, gray.width, gray.height, log, 9);
//		normalize(norm2, gray, 0, 255);
//		reverse(gray);
//		//localEnhance(gray, gray.height, gray.height);
//		delete[] norm1;
//		delete[] norm2;
//		delete[] log;
//	}
//
//	//输出
//	reverse(gray);
//	//gray.save(savefile.data());
//	Bitmap bw;
//	localBinarization(gray, bw, gray.height, gray.height);
//	bw.bitcount = 2;
//	bw.save("bw.bmp");
//	Bitmap point;
//	findPoint(bw, point, 8);
//	point.save("point.bmp");
//
//	int decimalpoint = checkPoint(point, gray);
//	//point.save(savefile4.data());
//	return decimalpoint;
//}

int decimalPoint(Bitmap src){
	//1
	Bitmap gray;
	gray = src;
	double* norm1;
	normalize(gray, norm1, 0, 1);
	double* log = create_LOG(9, 1.5);
	double* norm2 = filter(norm1, gray.width, gray.height, log, 9);
	normalize(norm2, gray, 0, 255);


	Bitmap gray2;
	gray2 = gray;
	//加入中值滤波降噪 3*3框
	int count = 0;
	for (int i = 1; i < gray.height-1; i++)
	{
		for (int j = 1; j < gray.width-1; j++)
		{
			int k = 0;
			xBYTE window[9];
			for (int jj = i- 1; jj < i + 2; ++jj)
				for (int ii = j - 1; ii < j + 2; ++ii)
					window[k++] = *(gray.data+jj*gray.step + ii);
			//元素排序（一半即可）
			for (int m =0; m < 8; ++m)
			{
				int min = m; 
				for (int n = m + 1; n < 9; ++n)
					if (window[n] < window[min])
						min = n;
				if (min != m)
				{
					xBYTE temp = window[m];
					window[m] = window[min];
					window[min] = temp;
				}
			}
			for (int n = 0; n < 9; ++n)
			{
				if (window[n] > 0)
					count++;
			}
			if (window[8]<50)
			*(gray.data + i*gray.step + j) = 0;
		}
	}
	//将第一列像素处理
	for (int i = 0; i < gray.height; i++)
	{
		*(gray.data + i*gray.step) = 0;
		*(gray.data + i*gray.step + gray.width - 1) = 0;
	}
	

	gray.save("gray1.bmp");

	//reverse(gray);
	delete[] norm1;
	delete[] norm2;
	delete[] log;

	//2
	/*Bitmap gray2;
	gray2 = gray;*/
	normalize(gray2, norm1, 0, 1);
	log = create_cos(7, 5.6568);
	norm2 = filter(norm1, gray2.width, gray2.height, log, 7, false);
	normalize(norm2, gray2, 0, 255);
	gray.save("gray2.bmp");
	delete[] norm1;
	delete[] norm2;
	delete[] log;

	//寻找小数点
	Bitmap bw;
	localBinarization(gray2, bw, gray2.height, gray2.height);
	bw.bitcount = 2;
	bw.save("bw.bmp");
	Bitmap point;
	findPoint(bw, point, 8);
	point.save("point.bmp");

	int decimalpoint = checkPoint(point, gray, 150);

	gray.clear();
	gray2.clear();
	bw.clear();
	point.clear();
	return decimalpoint;
}
