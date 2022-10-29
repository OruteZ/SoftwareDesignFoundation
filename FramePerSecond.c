#include "FramePerSecond.h"

#pragma warning(disable:4996)

void FPSData_init(FPSData** fps_data)
{
	(*fps_data) = (FPSData*)malloc(sizeof(fps_data));
	(*fps_data)->frame_cnt = 0;
	(*fps_data)->fps_text_buffer = (char*)malloc(sizeof(char) * 10);
	sprintf((*fps_data)->fps_text_buffer, "FPS=%d", (*fps_data)->frame_cnt);
	(*fps_data)->fps_old_time = clock();
}

void FPSData_Draw(FPSData** fps_data)
{
	(*fps_data)->frame_cnt++;
	(*fps_data)->fps_cur_time = clock();
	if ((*fps_data)->fps_cur_time - (*fps_data)->fps_old_time >= 1000) {
		sprintf((*fps_data)->fps_text_buffer, "FPS=%d", (*fps_data)->frame_cnt);
		(*fps_data)->fps_old_time = clock();
		(*fps_data)->frame_cnt = 0;
	}

	ScreenPrint(0, 0, (*fps_data)->fps_text_buffer);
}

void FPSData_delete(FPSData** fps_data)
{
	free((*fps_data)->fps_text_buffer);
	free(*fps_data);
}
