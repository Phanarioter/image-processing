#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <memory.h> 
#include "hdr.h"
// getheader函数的实现
struct bmphdr* get_header(char filename[])
{
	FILE* fp;	
	struct bmphdr* hdr;
	// 打开文件
	fp = fopen(filename, "rb");
	// 如果报错
	if (!fp) {
		printf("File open error or such file does not exist!\n");
		return NULL;
	}
	//给结构体指针分配空间
	hdr = (struct bmphdr*)malloc(sizeof(struct bmphdr));
	fread(hdr->signature, 2, 1, fp);
	if (hdr->signature[0] != 'B' || hdr->signature[1] != 'M') {
		printf("Not a bmp file!\n");
		return NULL;
	}
	//读取参数
	fread(&hdr->size, 4, 1, fp);
	fread(hdr->reserved, 4, 1, fp);
	fread(&hdr->offset, 4, 1, fp);
	fread(&hdr->hdr_size, 4, 1, fp);
	fread(&hdr->width, 4, 1, fp);
	fread(&hdr->height, 4, 1, fp);
	fread(&hdr->nr_planes, 2, 1, fp);
	fread(&hdr->bits_per_pixel, 2, 1, fp);
	fread(&hdr->compress_type, 4, 1, fp);
	fread(&hdr->data_size, 4, 1, fp);
	fread(&hdr->resol_hori, 4, 1, fp);
	fread(&hdr->resol_vert, 4, 1, fp);
	fread(&hdr->nr_colors, 4, 1, fp);
	fread(&hdr->important_color, 4, 1, fp);
	if (hdr->offset > 54)
		fread(&hdr->info, 1024, 1, fp);
	//关闭文件
	fclose(fp);
	//返回结构体
	return hdr;
}