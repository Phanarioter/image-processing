#pragma once
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

void DifferenceMethod()
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
	hdr = get_header("D:/test.bmp");
	if (!hdr) exit(1);
	fp = fopen("D:/test.bmp", "rb");
	if (!fp) exit(1);
	fseek(fp, hdr->offset, SEEK_SET);
	nr_pixels = hdr->width * hdr->height;
	bitmap = new unsigned char[nr_pixels];
	fread(bitmap, nr_pixels, 1, fp);
	fclose(fp);

	//��ַ�
	//�������������һ�к�����һ��
	to = new unsigned char[nr_pixels];
	for (int i = 0; i < hdr->height - 1; ++i) {
		for (int j = 0; j < hdr->width - 1; ++j) {
			//���ø����Ĺ�ʽ
			to[i * hdr->width + j] =
				abs(bitmap[i * hdr->width + j] - bitmap[(1 + i) * hdr->width + j]) +
				abs(bitmap[i * hdr->width + j] - bitmap[i * hdr->width + j + 1]);
		}
	}

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
