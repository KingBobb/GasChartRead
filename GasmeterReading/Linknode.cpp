#include "Linknode.h"
#include "jpeg2bmp.h"
#include "DecimalPoint.h"
#include "pretreatment.h"
#include "DealImage.h"

void recursioncut(struct node* curhead, Bitmap gray, int ileft, int iright){
	//const char* tempfile = "blackwhite.bmp";
	DealImage del;
	const int glevel = 256;
	Bitmap roi;
	Bitmap bw;   
	int *proj = NULL;
	if (iright-ileft <= 1) return;
	roi.width = iright - ileft + 1;
	roi.height = gray.height;
	roi.bitcount = gray.bitcount;
	roi.channels = gray.channels;
	roi.step = (roi.width + 3) / 4 * 4;
	roi.data = (xBYTE*)malloc(roi.height*roi.step*sizeof(xBYTE));
	for (int i = 0; i < roi.height; i++){
		for (int j = 0; j < roi.width; j++){
			*(roi.data + i*roi.step + j) = *(gray.data + i*gray.step + ileft + j);
		}
	}
	//直方图确定阈值
	int hist[glevel];
	memset(hist, 0, glevel*sizeof(int));
	for (int i = 0; i < roi.height; i++){
		for (int j = 0; j < roi.width; j++){
			int pixval = *(roi.data + i*roi.step + j);
			hist[pixval]++;
		}
	}
	int histsum = (roi.width + 1)*(roi.height + 1);
	int tmpsum = 0;
	float rth = 0.2;
	int thresh = glevel / 2;
	for (int i = 0; i < glevel; i++){
		tmpsum += hist[i];
		if (tmpsum > rth*histsum){
			thresh = i;
			break;
		}
	}
	//生成二值图
	bw = roi;
	for (int i = 0; i < bw.height; i++){
		for (int j = 0; j < bw.width; j++){
			if (*(roi.data + i*roi.step + j) <= thresh){
				*(bw.data + i*roi.step + j) = 1;
			}
			else{
				*(bw.data + i*roi.step + j) = 0;
			}
		}
	}
	//bw.save(tempfile);
    
	//投影
	proj = del.sums(bw, 1);
	int lowthresh = 1;
	struct node *cur = curhead;
	struct node *tmp = NULL;
	//一般情况
	bool flag = false;
	int peak_thresh = 3;
	int num_count = 0;
	for (int i = 0; i < bw.width; i++){
		if (proj[i]>lowthresh && flag == false){
			flag = true;
			tmp = (struct node*)malloc(sizeof(struct node));
			tmp->left = ileft + i;
		}
		if (proj[i] <= lowthresh && flag == true){
			flag = false;
			tmp->right = ileft + i;
			//判断区间内的投影极大值，用于滤除空白区域
			int local_max = proj[tmp->left];
			for (int j = tmp->left; j <= tmp->right; j++){
				if (proj[j] > local_max){
					local_max = proj[j];
				}
			}
			num_count++;
			//printf("local max:%d @%d\n", local_max,num_count);
			//插入
			tmp->next = cur->next;
			cur->next = tmp;
			cur = tmp;
			tmp = NULL;
		}
	}
	//结尾存在
	if (flag && tmp){
		//printf("has tail\n");
		tmp->right = iright;
		tmp->next = cur->next;
		cur->next = tmp;
		cur = tmp;
		tmp = NULL;
	}
	
	//clean up
	roi.clear();
	bw.clear();
	free(proj);

	return;
}

//判定dPoint所在列上方没有字
bool mixOfDecimalAndChar(Bitmap gray, int dpoint){
	DealImage deal;
	Bitmap bw;
	int count = 0;
	deal.im2bws(gray, bw, deal.graythresh(gray));
	for (int i = bw.height / 3; i < bw.height; i++){
		if (bw.data[i*bw.step + dpoint] > 0){
			count++;
		}
	}
	cout << endl<<"count value:"<<count << endl;
	if (count < 4){
		return true;
	}
	return false;
}

char* readmeter(const char* filename, int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int p4x, int p4y){
	//转换文件格式 jpg->bmp
	const char* tmpfile = "gmtemp.bmp";
	//read_jpeg_file(filename, tmpfile);
	//预处理
	Pretreatment pt;
	pt.pretreat(filename);
	//灰度化
	DealImage del;
	Bitmap bm, gray;
	bm.read(tmpfile);
	del.rgb2gray(bm, gray);
	gray.save(tmpfile);
	bm.clear();
	gray.clear();
	//*/
	//旋转 用到p3，p4
	if ((p3x - p4x) != 0){
		double theta = ((double)(p4y - p3y)) / (p3x - p4x);
		Bitmap rt_src, rt_dst;
		rt_src.read(tmpfile);
		imrotate(rt_src, rt_dst, theta);
		rt_dst.save(tmpfile);
		rt_src.clear();
		rt_dst.clear();
		printf("rotated..%f\n",theta);
	}
	//剪切，用到p1,p2
	if (p1x && p1y){
		Bitmap cut_src, cut_dst;
		cut_src.read(tmpfile);
		del.cutBmp(cut_src, cut_dst, Rect(p1x, p1y, p2x - p1x, p2y - p1y));
		cut_dst.save(tmpfile);
		cut_src.clear();
		cut_dst.clear();
	}
	//*/

	MyReco rc;
	struct node *head = NULL;
	struct node *tail = NULL;
	head = (struct node*)malloc(sizeof(struct node));
	head->next = NULL;
	tail = head->next;	
	printf("正在处理：%s\n", filename);


	bm.read(tmpfile);
	int dPoint = 0;
	dPoint = decimalPoint(bm);
	
	gray.read(tmpfile);


	//修改部分第一次切分
	Bitmap gray1,dst;
	int sign,count1 = 0;
	gray1.read("gray1.bmp");
	int length = gray1.height;
	xBYTE fuck[100] = { 0 };
	gray1.step = (gray1.width + 3) / 4 * 4;
	for (int i = 0; i < gray1.height; i++)
	{
		for (int j = 0; j < gray1.width; j++)
		{
			*(gray1.data+ i*gray1.step + j) = 255 - *(gray1.data+i*gray1.step + j);
		}
	}
   
	for (int i = 0; i < gray1.width; i++)
	{
		count1 = 0;
		for (int j = 0; j < gray1.height; j++)
		{
			fuck[j] = *(gray1.data + j*gray1.step + i);
		}
		for (int m = 0; m < gray1.height; m++)
		{
			if (fuck[m] < 255)
				count1++;
		}
		if (count1 > 10)
		{

			sign = i;
			break;
		}
	}
	//for (int i = gray1.height - 1; i >= 0; i--)
	//{
	//	count1 = 0;
	//	for (int j = 0; j < gray1.width; j++)
	//	{
	//		if (*(gray1.data + i*gray1.step + j) < 255)
	//			count1++;
	//	}
	//}
	//del.cutBmp()
	if (sign - 5 > 0)
	{
		imtangent(gray1, dst, 0.08);
		recursioncut(head, dst, sign - 5, dst.width - 1);
	}
	else if (sign - 4 > 0)
	{
		imtangent(gray1, dst, 0.08);
		recursioncut(head, dst, sign - 4, dst.width - 1);
	}
	else if (sign - 3 > 0)
	{
		imtangent(gray1, dst, 0.08);
		recursioncut(head, dst, sign - 3, dst.width - 1);
	}
	else if (sign - 2 > 0)
	{
		imtangent(gray1, dst, 0.08);
		recursioncut(head, dst, sign - 2, dst.width - 1);
	}
	else if (sign - 1 > 0)
	{
		imtangent(gray1, dst, 0.08);
		recursioncut(head, dst, sign - 1, dst.width - 1);
	}
	else
	{
		imtangent(gray1, dst, 0.08);
		recursioncut(head, dst, sign - 1, dst.width - 1);
	}

	//过滤
	struct node *fp = head;
	struct node *cp = fp->next;
	while (cp){
		if (cp->right - cp->left <= 5){
			Bitmap part;
			del.cutBmp(gray, part, Rect(cp->left, 0, cp->right - cp->left + 1, gray.height));
			int th = del.graythresh(part);
			//-cout << th << endl;
			//删除太窄的图，或者灰度阈值过大的图
			if ((cp->right - cp->left < 3) ){
				fp->next = cp->next;
				free(cp);
				cp = fp->next;
				continue;
			}
			part.clear();
		}
		//可能包含多个数字的图
		if (cp->right - cp->left >= 30){
			printf("second cut\n");
			int ileft = cp->left;
			int iright = cp->right;
			fp->next = cp->next;
			free(cp);
			cp = fp->next;
			recursioncut(fp, gray, ileft, iright);
			continue;
		}
		//检查当前数字后面是否可能有漏掉的数字
		if (cp->next!=NULL){
			struct node* np = cp->next;
			if (np->left - cp->right >= 20){
				int ileft = cp->right;
				int iright = np->left;
				recursioncut(cp, gray, ileft, iright);
				fp = fp->next;
				cp = fp->next;
				printf("gap check:ileft=%d iright=%d\n", ileft, iright);
				np = NULL;
				continue;
			}
		}
		fp = fp->next;
		cp = cp->next;
	}
	//找到小数点的横坐标
	
	
	int half_length = bm.width / 2;
	bm.clear();
	printf("decimal point:%d\n", dPoint);
	//识别
	//*/
	char result[1024]="";
	//memset(result, '\0', 1024 * sizeof(char));
	int rescount = 0;
	struct node *p = head->next;
	int count = 1;
	char fname[1024];
	bool decimal_flag = true;
	if (dPoint == 0) decimal_flag = false;
	
	while (p){
		Bitmap part;
		sprintf(fname, "d%d.bmp", count);
		if (p->right - p->left < 8 && p->next != NULL && p->next->right - p->next->left < 8 && p->next->left - p->right<5){
			Bitmap part1, part2, part3;
			ChitSDK res1, res2, res3;
			del.cutBmp(gray, part1, Rect(p->left, 0, p->right - p->left + 1, gray.height));
			del.cutBmp(gray, part2, Rect(p->next->left, 0, p->next->right - p->next->left + 1, gray.height));
			del.cutBmp(gray, part3, Rect(p->left, 0, p->next->right - p->left + 1, gray.height));
			cout << "left:" << p->left << " " << "right:" << p->right << endl;
			rc.recoAll(part1, res1, 5);
			rc.recoAll(part2, res2, 5);
			rc.recoAll(part3, res3, 5);
			/*
			int m1 = 1, m2 = 2;
			float rm1 = res1.m_dists[0], rm2 = res2.m_dists[0];

			//选出较大的两个
			if (res3.m_dists[0] < rm1){
				m1 = 3;
				rm1 = res3.m_dists[0];
			}
			else if (res3.m_dists[0] < rm2){
				m2 = 3;
				rm2 = res3.m_dists[0];
			}
			*/
			cout << "rm " << res1.m_dists[0] << " " << res2.m_dists[0] << " " << res3.m_dists[0] << endl;
			//字符被切坏的情况 rm1 > 0.8*rm2 && rm2 > 0.8*rm1
			if (res3.m_dists[0]<1.1*res1.m_dists[0] && res3.m_dists[0]<1.1*res2.m_dists[0]){
				result[rescount] = res3.m_result[0];
				rescount++;
				part3.save(fname);
				p = p->next;
				p = p->next;
				count++;
				continue;
			}
		}
			del.cutBmp(gray, part, Rect(p->left, 0, p->right - p->left + 1, gray.height));
			string res = rc.reco(part, 5);
			char tres[100];
			strcpy(tres, res.c_str());
			if (tres[0] == '.')
			{
				p = p->next;
			}
			else
			{
				if (p->left < dPoint && dPoint < p->right)
				{
					decimal_flag = mixOfDecimalAndChar(gray1, dPoint);
				}
				/*decimal_flag = mixOfDecimalAndChar(gray1, dPoint);
				if (p->left < dPoint && dPoint< p->right)
				decimal_flag = false;*/
				
				result[rescount] = tres[0];
				rescount++;
				part.save(fname);
				p = p->next;
				count++;
			}
			if (decimal_flag){
				if (p->left > dPoint){
					decimal_flag = false;
					result[rescount] = '.';
					rescount++;
					count++;
				}
			}
	}
	for (int i = 0; i < count; i++){
		sprintf(fname, "d%d.bmp", i);
		//remove(fname);
	}
	//*/
	//clean up
	gray1.clear();
	dst.clear();
	bm.clear();
	gray.clear();
	struct node *p2 = head->next;
	struct node *p1 = head;
	while (p1){
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	return result;
}
//旋转，theta弧度
void imrotate(Bitmap src, Bitmap& dst, double theta){
	const double pi = 3.1415926;
	if (src.channels != 1){
		cout << "Not gray image @imrotate\n" << endl;
		return;
	}
	dst.clear();
	dst = src;
	memset(dst.data, 0, dst.height*dst.step);
	int cen_x = dst.width / 2;
	int cen_y = dst.height / 2;
	for (int i = 0; i < dst.height; i++){
		for (int j = 0; j < dst.width; j++){
			int x = (j - cen_x);
			int y = (i - cen_y);
			double src_x = x*cos(theta) - y*sin(theta);
			double src_y = x*sin(theta) + y*cos(theta);
			int ox = (int)src_x + cen_x;
			int oy = (int)src_y + cen_y;
			if (ox >= 0 && ox < src.width && oy >= 0 && oy < src.height){
				*(dst.data + i*dst.step + j) = *(src.data + oy*src.step + ox);
			}
		}
	}
}

void imtangent(Bitmap src, Bitmap& dst, double factor){
	if (src.channels != 1){
		cout << "Not gray image @imtangent" << endl;
		return;
	}
	dst.clear();
	dst = src;
	memset(dst.data, 0, dst.height*dst.step);
	for (int i = 0; i < dst.height; i++){
		for (int j = 0; j < dst.width; j++){
			float src_y_f = factor*i + j;
			int src_y = int(src_y_f);
			if (src_y>=0 && src_y<dst.width)
				*(dst.data + i*dst.step + j) = *(src.data + i*src.step + src_y);
		}
	}
}



