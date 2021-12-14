#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <algorithm>
#include "Equalization.h"
#include "hdr.h"
#include "bmphdr.h"
#include "ez.h"
using namespace std;
//这里有个问题，unsigned char 这么取平均之后大部分都是0，图像黑暗，但是最后使用int类型就正常了
int getAverage(unsigned char* a, int size) {
	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += a[i];
	}
	sum = sum / 9;
	return sum;
}

void MeanFilter()
{
	//变量
	struct bmphdr* hdr;//位图
	unsigned char* bitmap, * to;//原始数据，处理之后数据
	char buf[2048];
	unsigned char tmp[9];//排序数组
	int nr_pixels;//像素个数


	//读文件
	FILE* fp, * fpnew;
	unsigned pj, px;
	hdr = get_header("D:/testnoise.bmp");
	if (!hdr) exit(1);
	fp = fopen("D:/testnoise.bmp", "rb");
	if (!fp) exit(1);
	fseek(fp, hdr->offset, SEEK_SET);
	nr_pixels = hdr->width * hdr->height;
	bitmap = new unsigned char[nr_pixels];
	fread(bitmap, nr_pixels, 1, fp);
	fclose(fp);


	//一维数组存储，公式i * width + j，第i行的第j个
	to = new unsigned char[nr_pixels];
	for (int i = 1; i < hdr->height - 1; ++i) {
		for (int j = 1; j < hdr->width - 1; ++j) {
			//提取模板中的数字
			int cnt = 0;
			for (int m = -1; m <= 1; ++m) {
				//m行号位移量，n列号位移量
				for (int n = -1; n <= 1; ++n) {
					//将框中的九个数字放入tmp数组
					tmp[cnt++] = bitmap[(i + m) * hdr->width + j + n];
				}
			}
			//求取均值
			to[i * hdr->width + j] = getAverage(tmp, 9);
		}
	}
	//处理边界
	for (int j = 1; j <= hdr->width - 2; ++j) {
		to[j] = to[hdr->width + j];
		to[(hdr->height - 1) * hdr->width + j] = to[(hdr->height - 2) * hdr->width + j];
	}
	for (int i = 1; i <= hdr->height - 2; ++i) {
		to[i * hdr->width] = to[i * hdr->width + 1];
		to[i * hdr->width + hdr->width - 1] = to[i * hdr->width + hdr->width - 2];
	}
	//四个拐角
	to[0] = to[hdr->width + 1];
	to[hdr->width - 1] = to[1 * hdr->width + hdr->width - 2];
	to[(hdr->height - 1) * hdr->width] = to[(hdr->height - 2) * hdr->width + 1];
	to[(hdr->height - 1) * hdr->width + hdr->width - 1] =
		to[(hdr->height - 1) * hdr->width + hdr->width - 2];






	//写入
	fpnew = fopen("D:/res.bmp", "wb+");

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

	fwrite(to, nr_pixels, 1, fpnew);
	//关闭
	fclose(fpnew);
	//释放
	free(hdr);
	delete bitmap;


}

