
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
	/*/��ͼ����
	for (int i = 1513; i <= 1517; i++){
		for (int j = 1; j <= 5; j++){
			char fname[100];
			sprintf(fname, "p%d-%d.jpg", i, j);
			//�������Ҫ��ת ����λ������0��0��0��0
			//�������Ҫ�з�roi��ǰ��λ������0��0��0��0 ��ͼ�������һ�����ִ���
			char* res = readmeter(fname, 0, 0, 0, 0, 0, 0, 0, 0);
			printf("ʶ���� :%s\n", res);
			system("pause");
		}
	}
	//*/
	//��ͼ����
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
		sprintf(fname, "c:\\users\\kornblume\\desktop\\��Ŀ\\ú����\\ʵ��\\��ͼ2016.05.03\\%d.jpg", i);
		char* res = readmeter(fname, 83, 104, 274, 132, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}
	*/
	/*for (int i = 1; i < 11; i++){
		char fname[100];
		sprintf(fname, "c:\\users\\kornblume\\desktop\\��Ŀ\\ú����\\ʵ��\\%d.jpg", i);
		char* res = readmeter(fname, 82, 99, 274, 128, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}*/

	//for (int i = 1; i < 22; i++){
	//	char fname[100];
	//	sprintf(fname, "c:\\users\\kornblume\\desktop\\��Ŀ\\ú����\\ʵ��\\���ֿ�λ��ͼ\\%d.jpg", i);
	//	char* res = readmeter(fname, 82, 95, 282, 125, 0, 0, 0, 0);
	//	printf("result: %s\n", res);
	//	system("pause");
	//}
	

	/*for (int i = 1; i < 7; i++){
		char fname[100];
		sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\��Ŀ\\ú����\\ʵ��\\��Դλ�õ�������ͼ\\%d.jpg", i);
		char* res = readmeter(fname, 82, 90, 284, 128, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}*/

	/*for (int i = 1; i < 12; i++){
		char fname[100];
		sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\��Ŀ\\ú����\\��Ʒ��\\����\\%d.jpg", i);
		char* res = readmeter(fname, 83, 95, 274, 128, 0, 0, 0, 0);
		printf("result: %s\n", res);
		system("pause");
	}*/

	//for (int i = 8; i < 27; i++){
	//	char fname[100];
	//	sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\��Ŀ\\ú����\\��Ʒ��\\�޵���\\%d.jpg", i);
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
	//sprintf(fname, "c:\\users\\kornblume\\desktop\\��Ŀ\\ú����\\ʵ��\\��ͼ2\\%d.jpg", i);
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
//sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\Z�ͱ�ʶ�����ͳ������\\��һλ��С����\\%d.jpg", i);
//char* res = readmeter(fname, 83, 96, 274, 127, 0, 0, 0, 0);
//printf("result: %s\n", res);
//system("pause");
//}
 

//for (int i = 1; i < 7; i++){
//	char fname[100];
//	sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\Z�ͱ�ʶ�����ͳ������\\��λ3��\\%d.jpg", i);
//	char* res = readmeter(fname, 83, 96, 274, 127, 0, 0, 0, 0);
//	printf("result: %s\n", res);
//	system("pause");
//}

//for (int i = 1; i < 9; i++){
//	char fname[100];
//	sprintf(fname, "C:\\Users\\Kornblume\\Desktop\\Z�ͱ�ʶ�����ͳ������\\%d.jpg", i);
//	char* res = readmeter(fname, 87, 96, 274, 127, 0, 0, 0, 0);
//	printf("result: %s\n", res);
//	system("pause");
//}

//string s = "C:\\Users\\Kornblume\\Desktop\\ú�����������20161123\\δʶ��ɹ� ������\\10001519_02091840.jpg";
//char* res = readmeter(s.c_str(), 86, 101, 274, 126, 0, 0, 0, 0);
//printf("result: %s\n", res);
//system("pause");

//string  path = "C:\\Users\\Kornblume\\Desktop\\ú�����������20161123\\δʶ��ɹ� ������\\1";
//vector<string> files;
//getJustCurrentFile(path, files);
//for (vector<string>::iterator i = files.begin(); i != files.end(); i++)
//{
//	char* res = readmeter((*i).c_str(), 83, 96, 274, 127, 0, 0, 0, 0);
//	cout << res << endl;
//	system("pause");
//}


//string  path = "C:\\Users\\Kornblume\\Desktop\\ú�����������20161123\\δʶ��ɹ� ������\\2";
//vector<string> files;
//getJustCurrentFile(path, files);
//for (vector<string>::iterator i = files.begin(); i != files.end(); i++)
//{
//	char* res = readmeter((*i).c_str(), 72, 112, 277, 143, 0, 0, 0, 0);
//	cout << res << endl;
//	system("pause");
//}


//string path = "C:\\Users\\Kornblume\\Desktop\\��Ŀ\\ú����\\����\\ʶ���������20161230\\�³���ʶ������ͼƬ\\3�ͱ�ʶ�����ͼƬ\\4��.1��4��";
//string path = "C:/Users/Kornblume/Desktop/��Ŀ/ú����/����/ʶ���������20161230/�³���ʶ������ͼƬ/3�ͱ�ʶ�����ͼƬ/���λ��3��";
string path = "C:\\Users\\Kornblume\\Desktop\\��Ŀ\\ú����\\����\\ʶ���������20170105\\3�ͱ�3������ͼƬ��";
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

//string path = "C:\\Users\\Kornblume\\Desktop\\��Ŀ\\ú����\\����\\ʶ���������20161230\\�³���ʶ������ͼƬ\\Z�ͱ�ʶ�����ͼƬ\\4��.1ԭʶ������ͼƬ4��";
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
	//�ļ���� 
	long hFile = 0;

	//�ļ���Ϣ
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
 