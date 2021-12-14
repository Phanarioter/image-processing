#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include "hdr.h"

void BMP_hdr()
{
	bmphdr header;
	// 打开文件
	FILE* fp;
	fp = fopen("D:/test.bmp", "r");
	// 如果报错
	if (!fp) {
		printf("File open error or such file does not exist!\n");
		exit(1);
	}
	fread(header.signature, 2, 1, fp);
	if (header.signature[0] != 'B' || header.signature[1] != 'M') {
		printf("Not a bmp file!\n");
		exit(1);
	}
	// 读取参数到结构体header中
	fread(&header.size, 4, 1, fp);
	fread(header.reserved, 4, 1, fp);
	fread(&header.offset, 4, 1, fp);
	fread(&header.hdr_size, 4, 1, fp);
	fread(&header.width, 4, 1, fp);
	fread(&header.height, 4, 1, fp);
	fread(&header.nr_planes, 2, 1, fp);
	fread(&header.bits_per_pixel, 2, 1, fp);
	fread(&header.compress_type, 4, 1, fp);
	fread(&header.data_size, 4, 1, fp);
	fread(&header.resol_hori, 4, 1, fp);
	fread(&header.resol_vert, 4, 1, fp);
	fread(&header.nr_colors, 4, 1, fp);
	fread(&header.important_color, 4, 1, fp);
	// 关闭文件
	fclose(fp);
	//打印参数
	printf("signature		%c%c\n", header.signature[0], header.signature[1]);
	printf("size			%d\n", header.size);
	printf("offset			%d\n", header.offset);
	printf("hdr_size		%d\n", header.hdr_size);
	printf("width			%d\n", header.width);
	printf("height			%d\n", header.height);
	printf("nr_planes		%d\n", header.nr_planes);
	printf("bits_per_pixel	%d\n", header.bits_per_pixel);
	printf("compress_type	%d\n", header.compress_type);
	printf("data_size		%d\n", header.data_size);
	printf("resol_hori		%d\n", header.resol_hori);
	printf("resol_vert		%d\n", header.resol_vert);
	printf("nr_colors		%d\n", header.nr_colors);
	printf("/n");
}
