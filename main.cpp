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
#include "Equalization.h" //ֱ��ͼ���⻯
#include "ez.h"	//��ֵ��
#include "DifferenceMethod.h" //��ַ�
#include "MeanFilter.h"	//��ֵ�˲�
#include "MidianFilter.h"	//��ֵ�˲�
#include "PepperSalt.h"	//��ӽ�������
using namespace std;


int main()
{
	//��ֵ��
	EZ();
	//���⻯
	Equalization();
	//��ֵ�˲�
	MeanFilter(); 
	//��ַ����Ե
	DifferenceMethod();
	//�������
	PepperSalt(1000, 2);

	return 0;

}