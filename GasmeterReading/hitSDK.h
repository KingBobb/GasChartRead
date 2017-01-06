////////////////////////////////////////
//哈工大液晶数字识别SDK头文件         //
// by Tonghua Su                      //
// 哈尔滨工业大学软件学院             //
//                                    //
// @2016: 引擎内部编号A1              //
////////////////////////////////////////

#ifndef hitSDK_H
#define hitSDK_H
#include "Widgets.h"
class CModelA2;//识别服务类

#ifndef STRUCTURE
typedef struct {
	short x;
	short y;
} SPoint;//轨迹点的坐标结构，本项目不支持// Modified by Su at 2016.4.27
#endif /* STRUCTURE */

#define CANDIDATENUM 10//此值标识SDK提供识别的前十候选，更改此值可致程序异常

class ChitSDK //哈工大液晶数字识别SDK类
{
public:
	char m_result[CANDIDATENUM*2+1];//识别的候选结果，每字符占2字节
	float m_dists[CANDIDATENUM];//识别距离结果
	int actNum;	//识别候选实际数目
	SPoint m_trajec[1000];		// 输入轨迹	，本项目不支持// Modified by Su at 2016.4.27
	int m_ptnum0;	// 输入轨迹的点数，本项目不支持// Modified by Su at 2016.4.27	
	
	ChitSDK();
	virtual ~ChitSDK();
	void Recog();//识别接口，本项目不支持// Modified by Su at 2016.4.27
	void OffRecog(BmpDataInfo&);//识别接口
	void SetType(unsigned char);//设置识别范围，本项目不支持// Modified by Su at 2016.4.27
private:
	CModelA2 * m_hitSRV;//识别服务类实例
};

#endif
