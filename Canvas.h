//#pragma once
//
//// Èò»ö (Non-intensive)
//#define ATTRIBUTE_DEFAULT 0b111;
//
//typedef struct _CanvasCell {
//	unsigned short unicode;
//	unsigned short attribute;
//} CanvasCell;
//
//void InitCanvas();
//
//void ClearCanvas();
//
//// print to console
//void PrintCanvas();
//
//// cell position. x = x * 2, y = y
//void SetCanvasCell(const int x, const int y, const unsigned short unicode, const unsigned short attribute) ;
//
//void CanvasPrintString(const int x, const int y, const char* str, const unsigned short attribute);
//
//// cell position. x = x * 2, y = y
//void CanvasPrintStringAtCell(const int x, const int y, const char* str, const unsigned short attribute) ;
//
//#ifdef DEBUG
//#include <Windows.h>
//HANDLE GetCanvasHANDLE();
////void FillCanvasWithRandomCells();
////void FillCanvasWithTestString();
//#endif // DEBUG
//
