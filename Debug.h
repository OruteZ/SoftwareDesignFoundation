#pragma once

#ifdef DEBUG
// 프로그램 초기화 단계에 이 함수가 불려야 한다.
void DebugInit();
// 화면에 출력한다. <stdio.h> 의 printf 와 사용 방법은 동일하다.
void DebugPrint(const char* format, ...);
#endif

