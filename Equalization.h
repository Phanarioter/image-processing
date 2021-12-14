#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <stdlib.h>
#include "hdr.h"
#include "bmphdr.h"
#include "ez.h"
#include <memory.h>
#include <math.h>
using namespace std;

//结构指针
struct bmphdr* hdr;
//直方图变量
unsigned char* bitmap, new_color[256];
//灰度分布，灰度累计分布数组
int Count[256], acum[256];

void Equalization()
{
	
	int nr_pixels;//像素个数
	FILE* fp, * fpnew;// 原图像和均衡化后的图像
	//读取图像
	hdr = get_header("D:/test.bmp");
	if (!hdr) exit(1);
	//二进制可读的方式打开
	fp = fopen("D:/test.bmp", "rb");
	if (!fp) exit(1);
	//文件指针指向数据区
	fseek(fp, hdr->offset, SEEK_SET);
	//计算像素个数
	nr_pixels = hdr->width * hdr->height;
	bitmap = new unsigned char[nr_pixels];//分配空间
	//数据放入bitmap
	fread(bitmap, nr_pixels, 1, fp);
	fclose(fp);



	memset(Count, 0, sizeof(Count));
	//计算每个灰度级上像素的个数 
	//结果存入count[]数组中
	/*代码*/
	for (int i = 0; i < nr_pixels; ++i) {
		Count[bitmap[i]] += 1;
	}

	memcpy(acum, Count, sizeof(acum));

	//计算灰度的累计分布
	for (int i = 1; i < 256; ++i)
		acum[i] += acum[i - 1];
	//灰度直方图的均衡化（核心程序部分，请仔细分析）
	for (int i = 0; i < 256; ++i)
	{
		//定义新的灰度对应规则 new_color[i]
		//其中 0<=i<=255
		int j = floor((acum[i] * 255 / nr_pixels) + 0.5);
		if (j > 255)
			j = 255;
		new_color[i] = j;
	}
	//对所有的像素灰度值按照均衡化得到的灰度对应规则进行转换
	//结果存入 bitmap[]中
	for (int i = 0; i < nr_pixels; ++i) {
		bitmap[i] = new_color[bitmap[i]];
	}


	//结果写入文件
	//设为可写的二进制形式
	fpnew = fopen("D:/res.bmp", "wb+");
	//写入文件fpnew
	fwrite(hdr->signature, 2, 1, fpnew);
	fwrite(&hdr->size, 4, 1, fpnew);
	fwrite(hdr->reserved, 4, 1, fpnew);
	fwrite(&hdr->offset, 4, 1, fpnew);
	fwrite(&hdr->hdr_size, 4, 1, fpnew);
	fwrite(&hdr->width, 4, 1, fpnew);
	fwrite(&hdr->height, 4, 1, fpnew);
	fwrite(&hdr->nr_planes, 2, 1, fpnew);
	fwrite(&hdr->bits_per_pixel, 2, 1, fpnew);
	fwrite(&hdr->compress_type, 4, 1, fpnew);
	fwrite(&hdr->data_size, 4, 1, fpnew);
	fwrite(&hdr->resol_hori, 4, 1, fpnew);
	fwrite(&hdr->resol_vert, 4, 1, fpnew);
	fwrite(&hdr->nr_colors, 4, 1, fpnew);
	fwrite(&hdr->important_color, 4, 1, fpnew);

	if (hdr->offset > 54)
		fwrite(hdr->info, hdr->offset - 54, 1, fpnew);
	//直方图均衡化的数据(bitmap)赋值
	/*代码*/
	fwrite(bitmap, nr_pixels, 1, fpnew);

	//关闭文件
	fclose(fpnew);
	//释放
	free(hdr);
	delete bitmap;

}