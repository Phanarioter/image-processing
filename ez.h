#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hdr.h"
using namespace std;


void EZ()
{
	struct bmphdr* hdr; //bmp图指针
	unsigned char* bitmap, * to;//两个表示字节的指针
	char buf[2048];

	int i, j, k, nr_pixels;
	FILE* fp, * fpnew;
	unsigned g;

	//读取文件生成bmphdr的指针hdr
	hdr = get_header("D:/test.bmp");

	if (!hdr)
		exit(1);
	//打开文件
	fp = fopen("D:/test.bmp", "rb");
	//如果报错
	if (!fp) {
		printf("File open error!\n");
		exit(1);
	}

	fseek(fp, hdr->offset, SEEK_SET);
	nr_pixels = hdr->width * hdr->height;// 长×宽=总像素
	bitmap = new unsigned char[nr_pixels];//分配大小
	fread(bitmap, nr_pixels, 1, fp);
	fclose(fp);//关闭文件

	k = 108;
	to = new unsigned char[nr_pixels];
	memset(to, 0, nr_pixels);//生成了一个全零矩阵
	//二值化处理
	for (i = 0; i < nr_pixels; i++)
		to[i] = bitmap[i] > (unsigned char)k ? 255 : 0;
	//打开要写入的文件
	fpnew = fopen("D:/res.bmp", "wb+");
	//打开报错
	if (!fpnew) {
		printf("File create error!\n");
		exit(1);
	}
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
	fwrite(to, nr_pixels, 1, fpnew);

	fclose(fpnew);//关闭写入的文件
	//释放空间
	free(hdr);
	free(bitmap);

}
