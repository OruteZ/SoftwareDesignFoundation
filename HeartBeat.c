#include "HeartBeat.h"

void HeartBeat_init()
{
	heart_beat = (HeartBeat*)malloc(sizeof(HeartBeat));

	heart_beat->note_size = 40;
	heart_beat->BPM = 240;
	heart_beat->time_to_check_tempo = 0;
	heart_beat->combo = 0;

	heart_beat->note = (short*)malloc(sizeof(short) * heart_beat->note_size);
	heart_beat->print_buffer = (char*)malloc(sizeof(char) * (heart_beat->note_size * 2));
	for (int i = 0; i < heart_beat->note_size; i++) {
		heart_beat->note[i] = 0;
		heart_beat->print_buffer[i * 2] = ' ';
		heart_beat->print_buffer[i * 2 + 1] = ' ';
	}


	heart_beat->print_point = Point_new(0, 20);
}

unsigned _stdcall Thread_PlaySound(void* arg) {
	Beep(3000, 100);
}

void HeartBeat_update(double delta_time)
{
	heart_beat->time_to_check_tempo += delta_time;

	if (heart_beat->time_to_check_tempo >= ((double)60 * 1000) / (double)heart_beat->BPM) {
		HeartBeat_move_note();
		heart_beat->time_to_check_tempo -= ((double)60 * 1000) / (double)heart_beat->BPM;
	}

	if (GetKeyDown('J')) {
		if (HeartBeat_is_note_beaten()) {
			isHit = TRUE;
			if (++(heart_beat->combo) >= 10) {
				HeartBeat_reset();
				heart_beat->combo = 0;
				heart_beat->BPM += 120;
			}
		}
		else
		{
			heart_beat->combo = 0;
		}
	}
}

void HeartBeat_render()
{
	for (int dy = 0; dy < 4; dy++) {
		ScreenPrint(heart_beat->print_point->x, heart_beat->print_point->y + dy, heart_beat->print_buffer);
		ScreenPrint(
			heart_beat->print_point->x + heart_beat->note_size * 2,
			heart_beat->print_point->y + dy,
			"                    "
		);
	}
}

void HeartBeat_release()
{
	free(heart_beat->note);
	free(heart_beat->print_buffer);
	Point_delete(heart_beat->print_point);
	free(heart_beat);
}

void HeartBeat_move_note()
{
	//test
	if (isHit) isHit = FALSE;


	int i, size = heart_beat->note_size;
	int last_node_point = -1;
	for (i = 1; i < size; i++) {
		heart_beat->note[i - 1] = heart_beat->note[i];
		if (heart_beat->note[i - 1] == 1) last_node_point = i;
	}

	if (last_node_point <= size - 4) {
		heart_beat->note[size - 1] = 1;
		//_beginthreadex(NULL, 0, Thread_PlaySound, 0, 0, NULL);
	}

	else heart_beat->note[size - 1] = 0;
	HeartBeat_reload_buffer();
}

void HeartBeat_reload_buffer()
{
	int i, size = heart_beat->note_size;
	for (i = 0; i < size; i++) {
		//sprintf((*fps_data)->fps_text_buffer, "FPS=%d", (*fps_data)->frame_cnt);
		if (heart_beat->note[i] == 1)
			sprintf((heart_beat->print_buffer) + (i * 2), "бс");
		else sprintf((heart_beat->print_buffer) + (i * 2), "  ");
	}
}

void HeartBeat_reset()
{
	for (int i = 0; i < heart_beat->note_size; i++) {
		heart_beat->note[i] = 0;
	}
}

int HeartBeat_is_note_beaten()
{
	double time_per_beat = (((double)60 * 1000) / (double)heart_beat->BPM);

	int note_position;
	for (int i = 0; i < heart_beat->note_size; i++) {
		if (heart_beat->note[i] == 1) {
			note_position = i;
			break;
		}
	}
	if (note_position > 1) return 0;

	heart_beat->note[note_position] = 0;

	double correct_time = time_per_beat * note_position;
	double time_differece = abs(correct_time - heart_beat->time_to_check_tempo);
	
	if (time_differece < time_per_beat / 2) return 1;
	else return 0;
}

void HeartBeat_set_BPM(int BPM)
{
	heart_beat->BPM = BPM;
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

int HeartBeat_get_combo() {
	return heart_beat->combo;
}