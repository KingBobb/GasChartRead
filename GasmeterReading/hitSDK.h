////////////////////////////////////////
//������Һ������ʶ��SDKͷ�ļ�         //
// by Tonghua Su                      //
// ��������ҵ��ѧ���ѧԺ             //
//                                    //
// @2016: �����ڲ����A1              //
////////////////////////////////////////

#ifndef hitSDK_H
#define hitSDK_H
#include "Widgets.h"
class CModelA2;//ʶ�������

#ifndef STRUCTURE
typedef struct {
	short x;
	short y;
} SPoint;//�켣�������ṹ������Ŀ��֧��// Modified by Su at 2016.4.27
#endif /* STRUCTURE */

#define CANDIDATENUM 10//��ֵ��ʶSDK�ṩʶ���ǰʮ��ѡ�����Ĵ�ֵ���³����쳣

class ChitSDK //������Һ������ʶ��SDK��
{
public:
	char m_result[CANDIDATENUM*2+1];//ʶ��ĺ�ѡ�����ÿ�ַ�ռ2�ֽ�
	float m_dists[CANDIDATENUM];//ʶ�������
	int actNum;	//ʶ���ѡʵ����Ŀ
	SPoint m_trajec[1000];		// ����켣	������Ŀ��֧��// Modified by Su at 2016.4.27
	int m_ptnum0;	// ����켣�ĵ���������Ŀ��֧��// Modified by Su at 2016.4.27	
	
	ChitSDK();
	virtual ~ChitSDK();
	void Recog();//ʶ��ӿڣ�����Ŀ��֧��// Modified by Su at 2016.4.27
	void OffRecog(BmpDataInfo&);//ʶ��ӿ�
	void SetType(unsigned char);//����ʶ��Χ������Ŀ��֧��// Modified by Su at 2016.4.27
private:
	CModelA2 * m_hitSRV;//ʶ�������ʵ��
};

#endif
