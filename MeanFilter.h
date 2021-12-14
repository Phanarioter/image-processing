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
//�����и����⣬unsigned char ��ôȡƽ��֮��󲿷ֶ���0��ͼ��ڰ����������ʹ��int���;�������
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
	//����
	struct bmphdr* hdr;//λͼ
	unsigned char* bitmap, * to;//ԭʼ���ݣ�����֮������
	char buf[2048];
	unsigned char tmp[9];//��������
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
	for (int i = 1; i < hdr->height - 1; ++i) {
		for (int j = 1; j < hdr->width - 1; ++j) {
			//��ȡģ���е�����
			int cnt = 0;
			for (int m = -1; m <= 1; ++m) {
				//m�к�λ������n�к�λ����
				for (int n = -1; n <= 1; ++n) {
					//�����еľŸ����ַ���tmp����
					tmp[cnt++] = bitmap[(i + m) * hdr->width + j + n];
				}
			}
			//��ȡ��ֵ
			to[i * hdr->width + j] = getAverage(tmp, 9);
		}
	}
	//����߽�
	for (int j = 1; j <= hdr->width - 2; ++j) {
		to[j] = to[hdr->width + j];
		to[(hdr->height - 1) * hdr->width + j] = to[(hdr->height - 2) * hdr->width + j];
	}
	for (int i = 1; i <= hdr->height - 2; ++i) {
		to[i * hdr->width] = to[i * hdr->width + 1];
		to[i * hdr->width + hdr->width - 1] = to[i * hdr->width + hdr->width - 2];
	}
	//�ĸ��ս�
	to[0] = to[hdr->width + 1];
	to[hdr->width - 1] = to[1 * hdr->width + hdr->width - 2];
	to[(hdr->height - 1) * hdr->width] = to[(hdr->height - 2) * hdr->width + 1];
	to[(hdr->height - 1) * hdr->width + hdr->width - 1] =
		to[(hdr->height - 1) * hdr->width + hdr->width - 2];






	//д��
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

