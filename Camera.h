#pragma once

void RenderCamera();

//특정 강력한 효과 (피격, 폭발등)가 작동할 때 호출할 함수입니다. 카메라가 흔들리는 연출이 생겨납니다.
//이미 다른 효과로 흔들리고 있을경우 함수 요청이 무시됩니다.
//void CameraShake();