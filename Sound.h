#pragma once

//�ش� �̸��� ���� ���带 ����մϴ�. �� �̸��� define���� ����Ǿ� �ֽ��ϴ�
//���� ��� ���� ���θ� �� �������� ��ȯ�մϴ�.
bool SoundPlay(char* SoundName);

//:���� 100���� ������ ���� �� �� �ֽ��ϴ�.
void SetVolume(int value);

// ���� ������ value��ŭ ������ŵ�ϴ�.
void UpVolume(int value);

//���� ������ value��ŭ ���ҽ�ŵ�ϴ�.
void DownVolume(int value);

//���� ������ ��ȯ �մϴ�.
int GetVolume();