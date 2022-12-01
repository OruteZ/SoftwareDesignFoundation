#pragma once
void InitCanvas();
void ClearCanvas();
void PrintCanvas();
void SetCanvasCell(const int x, const int y, const unsigned short unicode, const unsigned short attribute) ;
void CanvasPrintString(const int x, const int y, const char* str, const unsigned short attribute);
void CanvasPrintStringAtCell(const int x, const int y, const char* str, const unsigned short attribute) ;

#ifdef DEBUG
void FillCanvasWithRandomCells();
void FillCanvasWithTestString();
#endif // DEBUG

