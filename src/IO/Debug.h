#pragma once

#ifdef DEBUG
// ���α׷� �ʱ�ȭ �ܰ迡 �� �Լ��� �ҷ��� �Ѵ�.
void DebugInit();
// ȭ�鿡 ����Ѵ�. <stdio.h> �� printf �� ��� ����� �����ϴ�.
void DebugPrint(const char* format, ...);
#endif

