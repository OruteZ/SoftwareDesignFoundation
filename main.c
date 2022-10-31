#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <process.h>
#include <malloc.h>
#include "Screen.h"
#include "FramePerSecond.h"

#pragma warning(disable:4996)

HANDLE console; // HANDLE: resource control용 자료형

double deltaTime;

double _timeCountForCheckBPM = 0;
const int FramePerSecond = 60;

int BPM = 120;

FPSData* fps_data;

unsigned _stdcall Thread_PlaySound(void* arg) {
    Beep(3000, 100);
}

int a = 1;
void BPMCall() {
    COORD point = { 3, 3 };

    _beginthreadex(NULL, 0, Thread_PlaySound, 0, 0, NULL);

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

void WaitRender(clock_t old_time) {
    clock_t cur_time;
    while (1) {
        cur_time = clock();

        deltaTime = cur_time - old_time;
        if (deltaTime > FramePerSecond) break;
    }
}

//Test Code---------------------------------------------
double T_before, T_after, T;
char* T_buffer;
double D;
char* D_buffer;
char* Error_buffer;
void Test_init() {
    T_before = clock();
    T_buffer = (char*)malloc(sizeof(char) * 100);

    D = 0;
    D_buffer = (char*)malloc(sizeof(char) * 100);

    Error_buffer = (char*)malloc(sizeof(char) * 100);
}

void Test_Update() {
    T_after = clock();
    T = T_after - T_before;


    D += deltaTime;
}

void Test_Render() {
    sprintf(T_buffer, "%.4f", T/1000);
    ScreenPrint(1, 5, T_buffer);

    sprintf(D_buffer, "%.4f", D / 1000);
    ScreenPrint(1, 6, D_buffer);

    sprintf(Error_buffer, "%.10f", (T - D) / 1000);
    ScreenPrint(1, 7, Error_buffer);
}

void Test_Realese() {
    free(T_buffer);
    free(D_buffer);
    free(Error_buffer);
}

//Test End----------------------------------------------


void Init()
{
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    ScreenInit();
    FPSData_init(&fps_data);

    Test_init();
}

void Update()
{
    UpdateBPM();

    Test_Update();
}

void Render()
{
    ScreenClear();
    FPSData_Draw(&fps_data);

    if (a == 1) ScreenPrint(1, 2, "a");
    else ScreenPrint(1, 2, " ");
    Test_Render();

    ScreenFlipping();

}

void Release()
{
    Test_Realese();
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
        WaitRender(OldTime);
    }
    Release();
    return 0;
}
