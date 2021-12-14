#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include "hdr.h"
#include "bmphdr.h"
#include "ez.h"
#include <memory.h>
#include <math.h>
#include <algorithm>
#include "Equalization.h"
using namespace std;

void MedianFilter()
{

	struct bmphdr* hdr;//λͼ
	unsigned char* bitmap, * to;//ԭʼ���ݣ�����֮������
	char buf[2048];
	//3*3,�����ܰ˸�����
	int di[20] = { 1,2,3,4,5,6,7,8,9,10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10 };
	int dj[20] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	unsigned char tmp[21];//��������
	int nr_pixels;//���ظ���


	//���ļ�
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


	//һά����洢����ʽi * width + j����i�еĵ�j��
	to = new unsigned char[nr_pixels];
	for (int i = 0; i < hdr->height; ++i) {
		for (int j = 0; j < hdr->width; ++j) {
			//�����ĸ��߽磬��ģ���һ��
			if (i == 0 || i == hdr->height - 1 || j == 0 || j == hdr->width - 1) {
				to[(i * hdr->width) + j] = bitmap[(i * hdr->width) + j];
			}
			else {
				//�˲�������
				for (int k = 0; k < 20; ++k) {
					int ii = i + di[k];
					int jj = j + dj[k];
					//�µ����������������
					tmp[k] = bitmap[ii * hdr->width + jj];
				}
				//�˲��䣬����ھŸ�
				tmp[2] = bitmap[i * hdr->width + j];
				//qsort(tmp, 9, 1, cmp);
				sort(tmp, tmp + 21);
				to[i * hdr->width + j] = tmp[11];
			}
		}
	}
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
	//�ر�
	fclose(fpnew);
	//�ͷ�
	free(hdr);
	delete bitmap;


}
