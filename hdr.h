#pragma once
#ifndef __HDR_H__ 
#define __HDR_H__ 
# include <string>
// bmp图像的结构体
struct bmphdr {
char signature[2];// 签名
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
// getheader返回的是结构体指针
struct bmphdr* get_header(char filename[]);
#endif