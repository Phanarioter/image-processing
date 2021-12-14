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

//�ṹָ��
struct bmphdr* hdr;
//ֱ��ͼ����
unsigned char* bitmap, new_color[256];
//�Ҷȷֲ����Ҷ��ۼƷֲ�����
int Count[256], acum[256];

void Equalization()
{
	
	int nr_pixels;//���ظ���
	FILE* fp, * fpnew;// ԭͼ��;��⻯���ͼ��
	//��ȡͼ��
	hdr = get_header("D:/test.bmp");
	if (!hdr) exit(1);
	//�����ƿɶ��ķ�ʽ��
	fp = fopen("D:/test.bmp", "rb");
	if (!fp) exit(1);
	//�ļ�ָ��ָ��������
	fseek(fp, hdr->offset, SEEK_SET);
	//�������ظ���
	nr_pixels = hdr->width * hdr->height;
	bitmap = new unsigned char[nr_pixels];//����ռ�
	//���ݷ���bitmap
	fread(bitmap, nr_pixels, 1, fp);
	fclose(fp);



	memset(Count, 0, sizeof(Count));
	//����ÿ���Ҷȼ������صĸ��� 
	//�������count[]������
	/*����*/
	for (int i = 0; i < nr_pixels; ++i) {
		Count[bitmap[i]] += 1;
	}

	memcpy(acum, Count, sizeof(acum));

	//����Ҷȵ��ۼƷֲ�
	for (int i = 1; i < 256; ++i)
		acum[i] += acum[i - 1];
	//�Ҷ�ֱ��ͼ�ľ��⻯�����ĳ��򲿷֣�����ϸ������
	for (int i = 0; i < 256; ++i)
	{
		//�����µĻҶȶ�Ӧ���� new_color[i]
		//���� 0<=i<=255
		int j = floor((acum[i] * 255 / nr_pixels) + 0.5);
		if (j > 255)
			j = 255;
		new_color[i] = j;
	}
	//�����е����ػҶ�ֵ���վ��⻯�õ��ĻҶȶ�Ӧ�������ת��
	//������� bitmap[]��
	for (int i = 0; i < nr_pixels; ++i) {
		bitmap[i] = new_color[bitmap[i]];
	}


	//���д���ļ�
	//��Ϊ��д�Ķ�������ʽ
	fpnew = fopen("D:/res.bmp", "wb+");
	//д���ļ�fpnew
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
	//ֱ��ͼ���⻯������(bitmap)��ֵ
	/*����*/
	fwrite(bitmap, nr_pixels, 1, fpnew);

	//�ر��ļ�
	fclose(fpnew);
	//�ͷ�
	free(hdr);
	delete bitmap;

}