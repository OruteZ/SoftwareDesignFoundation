#pragma once

#include <Windows.h>

// 프로그램 초기화 단계에 이 함수를 불러야 한다.
void InitializeKeyboard();

// 매 프레임 시작 단계에 이 함수를 불러야 한다.
void UpdateKeyboard();

// 키가 이 프레임에 눌렀는지 여부를 반환한다.
// 키의 목록은 https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes 참고
// 로마자는 대문자를 사용해야 한다.
BOOLEAN GetKeyDown(unsigned char key);

// 키가 눌린 상태인지 여부를 반환한다. 이 프레임에 눌렸어도 눌린 상태인 것으로 간주한다.
// 키의 목록은 https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes 참고
// 로마자는 대문자를 사용해야 한다.
BOOLEAN GetKey(unsigned char key);

// 키가 이 프레임에 풀렸는지 여부를 반환한다.
// 키의 목록은 https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes 참고
// 로마자는 대문자를 사용해야 한다.
BOOLEAN GetKeyUp(unsigned char key);