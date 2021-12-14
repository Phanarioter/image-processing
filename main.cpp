#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <iostream>
#include "hdr.h"
#include "bmphdr.h"
#include "Equalization.h" //直方图均衡化
#include "ez.h"	//二值化
#include "DifferenceMethod.h" //差分法
#include "MeanFilter.h"	//均值滤波
#include "MidianFilter.h"	//中值滤波
#include "PepperSalt.h"	//添加椒盐噪声
using namespace std;


int main()
{
	//二值化
	EZ();
	//均衡化
	Equalization();
	//均值滤波
	MeanFilter(); 
	//差分法求边缘
	DifferenceMethod();
	//添加噪声
	PepperSalt(1000, 2);

	return 0;

}