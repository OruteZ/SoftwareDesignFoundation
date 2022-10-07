#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <process.h>
#include <malloc.h>

#define FramePerSecond 60

HANDLE console; // HANDLE: resource control용 자료형

double deltaTime;

double _timeCountForCheckBPM = 0;

int BPM = 120;

clock_t FPSCurTime, FPSOldTime;
int FrameCnt;
int FPSForPrint;

void setBlock(COORD point) {
	SetConsoleCursorPosition(console, point);
	printf("■");
}

void deleteBlock(COORD point) {
    SetConsoleCursorPosition(console, point);
    printf("  ");
}

void printNum(COORD point, int number) {
    SetConsoleCursorPosition(console, point);
    printf_s("%d", number);
}

unsigned _stdcall Thread_PlaySound(void* arg) {
    Beep(3000, 100);
}

int a = 1;
void BPMCall() {
    COORD point = { 3, 3 };

    _beginthreadex(NULL, 0, Thread_PlaySound, 0, 0, NULL);

    if (a == 1) setBlock(point);
    else deleteBlock(point);

    a = 1 - a;
}

void UpdateBPM() {
    //COORD position = { 0,0 };
    //printNum(position, _timeCountForCheckBPM);

    _timeCountForCheckBPM += deltaTime;

    if (_timeCountForCheckBPM >=  ((float)60 * 1000) / BPM) {
        BPMCall();
        _timeCountForCheckBPM -= ((float)60 * 1000) / BPM;
    }
}




void Init()
{
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    FrameCnt = 0;
    FPSForPrint = 0;
    FPSOldTime = clock();
}

void Update()
{
    UpdateBPM();
}

void Render()
{
    FrameCnt++;
    FPSCurTime = clock();
    if (FPSCurTime - FPSOldTime >= 1000)
    {
        FPSOldTime = clock();
        FPSForPrint = FrameCnt;
        FrameCnt = 0;
    }

    COORD point = { 1,1 };
    printNum(point, FPSForPrint);
}

void Release()
{
}

int main()
{
    clock_t  CurTime, OldTime;
    Init();

    while (1)
    {
        OldTime = clock();
        Update();
        Render();

        while (1)
        {
            CurTime = clock();
            deltaTime = CurTime - OldTime;
            if (deltaTime > 1000 / FramePerSecond) {
                break;
            }
        }
    }
    Release();
    return 0;
}
