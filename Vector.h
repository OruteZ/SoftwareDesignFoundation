#pragma once

#define VECTOR_INIT(vec) vector vec;\
vector_init(&vec)

typedef struct sVectorList
{
    void** items;
    int capacity;
    int total;
} sVectorList;

//������ �Լ��� �����Ѵ�
typedef struct sVector vector;
struct sVector
{
    sVectorList vectorList;
    //������ �Լ�
    int (*pfVectorTotal)(vector*);
    int (*pfVectorResize)(vector*, int);
    int (*pfVectorAdd)(vector*, void*);
    int (*pfVectorSet)(vector*, int, void*);
    void* (*pfVectorGet)(vector*, int);
    int (*pfVectorDelete)(vector*, int);
    int (*pfVectorFree)(vector*);
};



