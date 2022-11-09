#pragma once

#define VECTOR_INIT(vec) vector vec;\
vector_init(&vec)

typedef struct sVectorList
{
    void** items;
    int capacity;
    int total;
} sVectorList;

//포인터 함수를 포함한다
typedef struct sVector vector;
struct sVector
{
    sVectorList vectorList;
    //포인터 함수
    int (*pfVectorTotal)(vector*);
    int (*pfVectorResize)(vector*, int);
    int (*pfVectorAdd)(vector*, void*);
    int (*pfVectorSet)(vector*, int, void*);
    void* (*pfVectorGet)(vector*, int);
    int (*pfVectorDelete)(vector*, int);
    int (*pfVectorFree)(vector*);
};



