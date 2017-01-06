
#include "jpeg2bmp.h"
#include "Bitmap.h"
#include "DealImage.h"
#include "Linknode.h"
#include "reco.h"
#include "DecimalPoint.h"
#include <time.h>
#include <Windows.h>
#include <io.h>
#include<vector>
#include<fstream>
#include<string>

void getJustCurrentFile(string path, vector<string> & files);



int main(int argc, char *argv[])
{
	/*/旧图测试
	for (int i = 1513; i <= 1517; i++){
		for (int j = 1; j <= 5; j++){
			char fname[100];
			sprintf(fname, "p%d-%d.jpg", i, j);
			//如果不需要旋转 后四位参数给0，0，0，0
			//如果不需要切分roi，前四位参数给0，0，0，0 （图本身就是一个数字串）
			char* res = readmeter(fname, 0, 0, 0, 0, 0, 0, 0, 0);
			printf("识别结果 :%s\n", res);
			system("pause");
		}
	}
	//*/
	//新图测试
	/*/
	for (int i = 1; i < 11; i++){
	SYSTEMTIME t1, t2;
	GetLocalTime(&t1);
	printf("%4d/%02d/%02d %02d:%02d:%02d.%03d\n", t1.wYear,
	t1.wMonth,
	t1.wDay,
	t1.wHour,
	t1.wMinute,
	t1.wSecond,
	t1.wMilliseconds);
		char fname[100];
		sprintf(fname, "p%d.jpg", i);
		char* res = readmeter(fname, 0, 0, 0, 0, 0, 0, 0, 0);
		GetLocalTime(&t2);
		printf("%4d/%02d/%02d %02d:%02d:%02d.%03d\n", t2.wYear,
		t2.wMonth,
		t2.wDay,
		t2.wHour,
		t2.wMinute,
		t2.wSecond,
		t2.wMilliseconds);
		printf("result: %s\n", res);
		system("pause");
	}
	//*/
	//"1" 1,3,6
	
	/*for (int i = 1; i < 11; i++){
		char fname[100];
		sprintf(fname, "c:\\users\\kornblume\\desktop\\项目\\煤气表\\实验\\样图2016.05.03\\%d.jpg", i);
		char* res = readmeter(fname, 83, 104, 274, 132, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}
	*/
	/*for (int i = 1; i < 11; i++){
		char fname[100];
		sprintf(fname, "c:\\users\\kornblume\\desktop\\项目\\煤气表\\实验\\%d.jpg", i);
		char* res = readmeter(fname, 82, 99, 274, 128, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}*/

	//for (int i = 1; i < 22; i++){
	//	char fname[100];
	//	sprintf(fname, "c:\\users\\kornblume\\desktop\\项目\\煤气表\\实验\\数字空位样图\\%d.jpg", i);
	//	char* res = readmeter(fname, 82, 95, 282, 125, 0, 0, 0, 0);
	//	printf("result: %s\n", res);
	//	system("pause");
	//}
	

	/*for (int i = 1; i < 7; i++){
		char fname[100];
		sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\项目\\煤气表\\实验\\光源位置调整后样图\\%d.jpg", i);
		char* res = readmeter(fname, 82, 90, 284, 128, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}*/

	/*for (int i = 1; i < 12; i++){
		char fname[100];
		sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\项目\\煤气表\\产品版\\挡板\\%d.jpg", i);
		char* res = readmeter(fname, 83, 95, 274, 128, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}*/

	//for (int i = 8; i < 27; i++){
	//	char fname[100];
	//	sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\项目\\煤气表\\产品版\\无挡板\\%d.jpg", i);
	//	char* res = readmeter(fname, 83, 113, 280, 146, 0, 0, 0, 0);
	//	printf("result: %s\n", res);
	//	system("pause");
	//}
	//for (int i = 1; i < 11; i++){
	//	/*systemtime t1, t2;
	//	getlocaltime(&t1);
	//	printf("%4d/%02d/%02d %02d:%02d:%02d.%03d\n", t1.wyear,
	//		t1.wmonth,
	//		t1.wday,
	//		t1.whour,
	//		t1.wminute,
	//		t1.wsecond,
	//		t1.wmilliseconds);*/
	//char fname[100];
	//sprintf(fname, "c:\\users\\kornblume\\desktop\\项目\\煤气表\\实验\\样图2\\%d.jpg", i);
	//char* res = readmeter(fname, 86, 84, 271, 109, 0, 0, 0, 0);
	//printf("result: %s\n", res);
	////getlocaltime(&t2);
	////printf("%4d/%02d/%02d %02d:%02d:%02d.%03d\n", t2.wyear,
	////	t2.wmonth,
	////	t2.wday,
	////	t2.whour,
	////	t2.wminute,
	////	t2.wsecond,
	////	t2.wmilliseconds);
	//system("pause");
	//}


//for (int i = 1; i < 6; i++){
//char fname[100];
//sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\Z型表识别错误统计资料\\错一位及小数点\\%d.jpg", i);
//char* res = readmeter(fname, 83, 96, 274, 127, 0, 0, 0, 0);
//printf("result: %s\n", res);
//system("pause");
//}
 

//for (int i = 1; i < 7; i++){
//	char fname[100];
//	sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\Z型表识别错误统计资料\\差位3条\\%d.jpg", i);
//	char* res = readmeter(fname, 83, 96, 274, 127, 0, 0, 0, 0);
//	printf("result: %s\n", res);
//	system("pause");
//}

//for (int i = 1; i < 9; i++){
//	char fname[100];
//	sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\Z型表识别错误统计资料\\%d.jpg", i);
//	char* res = readmeter(fname, 87, 96, 274, 127, 0, 0, 0, 0);
//	printf("result: %s\n", res);
//	system("pause");
//}

//string s = "C:\\Users\\Kornblume\\Desktop\\煤气表错误数据20161123\\未识别成功 的数据\\10001519_02091840.jpg";
//char* res = readmeter(s.c_str(), 86, 101, 274, 126, 0, 0, 0, 0);
//printf("result: %s\n", res);
//system("pause");

//string  path = "C:\\Users\\Kornblume\\Desktop\\煤气表错误数据20161123\\未识别成功 的数据\\1";
//vector<string> files;
//getJustCurrentFile(path, files);
//for (vector<string>::iterator i = files.begin(); i != files.end(); i++)
//{
//	char* res = readmeter((*i).c_str(), 83, 96, 274, 127, 0, 0, 0, 0);
//	cout << res << endl;
//	system("pause");
//}


//string  path = "C:\\Users\\Kornblume\\Desktop\\煤气表错误数据20161123\\未识别成功 的数据\\2";
//vector<string> files;
//getJustCurrentFile(path, files);
//for (vector<string>::iterator i = files.begin(); i != files.end(); i++)
//{
//	char* res = readmeter((*i).c_str(), 72, 112, 277, 143, 0, 0, 0, 0);
//	cout << res << endl;
//	system("pause");
//}


//string path = "C:\\Users\\Kornblume\\Desktop\\项目\\煤气表\\错误\\识别问题汇总20161230\\新程序识别问题图片\\3型表识别错误图片\\4变.1共4张";
//string path = "C:/Users/Kornblume/Desktop/项目/煤气表/错误/识别问题汇总20161230/新程序识别问题图片/3型表识别错误图片/点错位共3张";
string path = "C:\\Users\\Kornblume\\Desktop\\项目\\煤气表\\错误\\识别问题汇总20170105\\3型表（3张问题图片）";
vector<string> files;
getJustCurrentFile(path, files);
for (vector<string>::iterator i = files.begin(); i != files.end(); i++)
{
   //char* res = readmeter((*i).c_str(), 73, 115, 279, 142, 0, 0, 0, 0);
	char* res = readmeter((*i).c_str(), 72, 109, 278, 146, 0, 0, 0, 0);
	//char* res = readmeter((*i).c_str(), 73, 112, 279, 145, 0, 0, 0, 0);    //success
	cout << res << endl;
	system("pause");
}

//string path = "C:\\Users\\Kornblume\\Desktop\\项目\\煤气表\\错误\\识别问题汇总20161230\\新程序识别问题图片\\Z型表识别错误图片\\4变.1原识别问题图片4张";
//vector<string> files;
//getJustCurrentFile(path, files);
//for (vector<string>::iterator i = files.begin(); i != files.end(); i++)
//{
//	//char* res = readmeter((*i).c_str(), 81, 100, 274, 125, 0, 0, 0, 0);
//	char* res = readmeter((*i).c_str(), 83, 96, 274, 127, 0, 0, 0, 0);
//	cout << res << endl;
//	system("pause");
//}



return 0;
}

void getJustCurrentFile(string path, vector<string> & files)
{
	//文件句柄 
	long hFile = 0;

	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib&_A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//	 files.push_back(fileinfo.name);
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					getJustCurrentFile(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				// files.push_back(fileinfo.name);
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
 