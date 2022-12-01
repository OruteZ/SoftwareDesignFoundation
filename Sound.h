#pragma once

//해당 이름을 가진 사운드를 출력합니다. 각 이름은 define으로 저장되어 있습니다
//사운드 재생 성공 여부를 참 거짓으로 반환합니다.
bool SoundPlay(char* SoundName);

//:부터 100사이 볼륨을 조절 할 수 있습니다.
void SetVolume(int value);

// 현재 볼륨을 value만큼 증가시킵니다.
void UpVolume(int value);

//현재 볼륨을 value만큼 감소시킵니다.
void DownVolume(int value);

//현재 볼륨을 반환 합니다.
int GetVolume();