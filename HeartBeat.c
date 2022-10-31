#include "HeartBeat.h"

void HeartBeat_init()
{
	heart_beat = (HeartBeat*)malloc(sizeof(HeartBeat));

	heart_beat->note_size = 20;
	heart_beat->BPM = 240;
	heart_beat->time_to_check_tempo = 0;

	heart_beat->note = (short*)malloc(sizeof(short) * heart_beat->note_size);
	for (int i = 0; i < heart_beat->note_size; i++) {
		heart_beat->note[0] = 0;
	}

	heart_beat->print_buffer = (char*)malloc(sizeof(char) * 2 * heart_beat->note_size);

	heart_beat->print_point = Point_new(0, 10);
}

void HeartBeat_update(double delta_time)
{
	heart_beat->time_to_check_tempo += delta_time;

	if (heart_beat->time_to_check_tempo >= ((float)60 * 1000) / heart_beat->BPM) {
		HeartBeat_move_note();
		heart_beat->time_to_check_tempo -= ((float)60 * 1000) / heart_beat->BPM;
	}

}

void HeartBeat_render()
{
	ScreenPrint(heart_beat->print_point->x, heart_beat->print_point->y, heart_beat->print_buffer);
}

void HeartBeat_release()
{
	free(heart_beat->note);
	free(heart_beat);
}

void HeartBeat_move_note()
{
	int i, size = heart_beat->note_size;
	int last_node_point = -1;
	for (i = 1; i < size; i++) {
		heart_beat->note[i - 1] = heart_beat->note[i];
		if (heart_beat->note[i - 1] == 1) last_node_point = i;
	}
	
	if(last_node_point < size - 4) 
		heart_beat->note[size - 1] = 1;
	else 
		heart_beat->note[size - 1] = 0;

	for (i = 0; i < size; i++) {
		if(heart_beat->note[i] == 1) 
			heart_beat->print_buffer[i] = '1';
		else heart_beat->print_buffer[i] = '0';
	}
}

int HeartBeat_is_note_beaten()
{
	if (heart_beat->note[0] == 1) {
		heart_beat->note[0] = 0;
		return 1;
	}
	else {
		return 0;
	}
}

void HeartBeat_set_BPM(int BPM)
{
	heart_beat -> BPM = BPM;
}

int HeartBeat_get_BPM()
{
	return heart_beat->BPM;
}

short* HeartBeat_get_note_information()
{
	short* result = (short*)malloc(sizeof(short) * heart_beat->note_size);
	memcpy(result, heart_beat->note, heart_beat->note_size);
	return result;
}
