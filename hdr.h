#pragma once
#ifndef __HDR_H__ 
#define __HDR_H__ 
# include <string>
// bmpͼ��Ľṹ��
struct bmphdr {
char signature[2];// ǩ��
int size;
short reserved[2]; 
int offset; 
int hdr_size; 
int width; 
int height;
short nr_planes; 
short bits_per_pixel; 
int compress_type; 
int data_size; 
int resol_hori; 
int resol_vert; 
int nr_colors; 
int important_color; 
char info[2048];
};
// getheader���ص��ǽṹ��ָ��
struct bmphdr* get_header(char filename[]);
#endif