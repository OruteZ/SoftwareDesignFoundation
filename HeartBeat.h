#pragma once
void HeartBeat_init();
void HeartBeat_update(double delta_time);
void HeartBeat_render();
void HeartBeat_release();

void HeartBeat_set_BPM(int BPM);
int HeartBeat_get_BPM();

short* HeartBeat_get_note_information();

int HeartBeat_get_combo();

