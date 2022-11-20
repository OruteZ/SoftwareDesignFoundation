#pragma once

#include <Windows.h>

// ���α׷� �ʱ�ȭ �ܰ迡 �� �Լ��� �ҷ��� �Ѵ�.
void InitializeKeyboard();

// �� ������ ���� �ܰ迡 �� �Լ��� �ҷ��� �Ѵ�.
void UpdateKeyboard();

// Ű�� �� �����ӿ� �������� ���θ� ��ȯ�Ѵ�.
// Ű�� ����� https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes ����
// �θ��ڴ� �빮�ڸ� ����ؾ� �Ѵ�.
BOOLEAN GetKeyDown(unsigned char key);

// Ű�� ���� �������� ���θ� ��ȯ�Ѵ�. �� �����ӿ� ���Ⱦ ���� ������ ������ �����Ѵ�.
// Ű�� ����� https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes ����
// �θ��ڴ� �빮�ڸ� ����ؾ� �Ѵ�.
BOOLEAN GetKey(unsigned char key);

// Ű�� �� �����ӿ� Ǯ�ȴ��� ���θ� ��ȯ�Ѵ�.
// Ű�� ����� https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes ����
// �θ��ڴ� �빮�ڸ� ����ؾ� �Ѵ�.
BOOLEAN GetKeyUp(unsigned char key);