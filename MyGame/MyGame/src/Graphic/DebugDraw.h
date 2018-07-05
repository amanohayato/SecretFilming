#pragma once
#include<DxLib.h>
#include<string>

class DebugDraw {
public:
#ifdef NDEBUG
	template<class ...T>
	//�f�o�b�O��p�̕�����`��
	static void DebugDrawFormatString(int x,int y,unsigned int color,const std::string& text, T ...args){}

	static void DebugDrawLine(int x1, int y1, int x2, int y2, unsigned int color, int thickness = 1) {}
	static void DebugDrawCircle(int x, int y, int r, unsigned int color, int FillFlag=1, int LineThickness = 1) {}
	static void DebugDrawBox(int x1, int y1, int x2, int y2, unsigned int color, int FillFlag) {}
	
	static void DebugDrawSphere3D(VECTOR   CenterPos, float  r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag) {}
	static void DebugDrawLine3D(VECTOR   Pos1, VECTOR   Pos2, unsigned int Color) {}

#else
	template<class ...T>
	//�f�o�b�O�p������`��
	static void DebugDrawFormatString(int x, int y, unsigned int color, const std::string& text, T ...args) {
		DrawFormatString(x, y, color, text.c_str(), args...);
	}
	//�f�o�b�O�p�����`��
	static void DebugDrawLine(int x1, int y1, int x2, int y2, unsigned int color, int thickness = 1) {
		DrawLine(x1, y1, x2, y2, color, thickness);
	}
	//�f�o�b�O�p�~�`��
	static void DebugDrawCircle(int x, int y, int r, unsigned int color, int FillFlag = 1, int LineThickness = 1) {
		DrawCircle(x, y, r, color, FillFlag, LineThickness);
	}
	//�f�o�b�O�p��`�`��
	static void DebugDrawBox(int x1, int y1, int x2, int y2,unsigned int color, int FillFlag) {
		DrawBox(x1, y1,x2,y2,color, FillFlag);
	}

	static void DebugDrawSphere3D(VECTOR   CenterPos, float  r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag) {
		DrawSphere3D(CenterPos, r, DivNum, DifColor, SpcColor, FillFlag);
	}
	static void DebugDrawLine3D(VECTOR   Pos1, VECTOR   Pos2, unsigned int Color) {
		DrawLine3D(Pos1, Pos2, Color);
	}
#endif

};
