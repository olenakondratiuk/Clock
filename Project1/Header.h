#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<cmath>
#include "math.h"
#include <ctime>
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
ref class clockClass {
private:
	struct tm * timeinfo;
	float x1 = 150;
	float y1 = 150;
	float x2;
	float y2;
public:	
	int getTime() {
		time_t rawtime; 
		time(&rawtime);       
		timeinfo = localtime(&rawtime);
		return timeinfo->tm_sec, timeinfo->tm_min, timeinfo->tm_hour;
	}
	int Calculate(float x20, float y20, float c, float a, int h) {
		if (h != 0) {
			for (int i = 1; i <= h; i++) {
				float d = sqrt(pow(abs(x1 - x20), 2) + pow(abs(y1 - y20), 2));
				float k = (pow(a, 2) - pow(c, 2) + pow(d, 2)) / (2 * d);
				float t = sqrt(pow(a, 2) - pow(k, 2));
				float x0 = x1 + k*(x20 - x1) / d;
				float y0 = y1 + k*(y20 - y1) / d;

				float x = x0 - t*(y20 - y1) / d;
				float y = y0 + t*(x20 - x1) / d;
				x20 = x;
				y20 = y;
			}				
		}
		x2 = x20;
		y2 = y20;
		return x2, y2;
	}
	void OneSec(System::Windows::Forms::PaintEventArgs^  e) {
		getTime();
		Pen^ greyPen = gcnew Pen(Color::Gray, 2.0f);		
		Calculate(150, 50, 10.467, 100, timeinfo->tm_sec);
		e->Graphics->DrawLine(greyPen, x1, y1, x2, y2);
	}
	void OneMin(System::Windows::Forms::PaintEventArgs^  e) {
		getTime();
		Pen^ blackPen = gcnew Pen(Color::Black, 4.0f);	
		Calculate(150, 50, 10.467, 100, timeinfo->tm_min);
		e->Graphics->DrawLine(blackPen, x1, y1, x2, y2);
	}
	void OneHour(System::Windows::Forms::PaintEventArgs^  e) {
		getTime();
		Pen^ blackPen = gcnew Pen(Color::Black, 6.0f);		
		Calculate(150, 80, 7.327, 70, timeinfo->tm_hour * 5 + timeinfo->tm_min / 12);
		e->Graphics->DrawLine(blackPen, x1, y1, x2, y2);
	}
};
