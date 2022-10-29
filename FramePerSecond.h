#pragma once


#include<malloc.h>
#include<stdio.h>
#include<time.h>
#include"Screen.h"

typedef struct _FPSData {
	clock_t fps_cur_time, fps_old_time;
	int frame_cnt;
	char* fps_text_buffer;
} FPSData;

void FPSData_init(FPSData** fps_data);
void FPSData_Draw(FPSData** fps_data);
void FPSData_delete(FPSData** fps_data);