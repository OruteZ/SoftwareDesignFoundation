#pragma once
#include "Camera.h"
#include "Game.h"
#include "Rect.h"

void InitCamera();
void RenderCamera();

//Ư�� ������ ȿ�� (�ǰ�, ���ߵ�)�� �۵��� �� ȣ���� �Լ��Դϴ�. ī�޶� ��鸮�� ������ ���ܳ��ϴ�.
//�̹� �ٸ� ȿ���� ��鸮�� ������� �Լ� ��û�� ���õ˴ϴ�.
void CameraShake();