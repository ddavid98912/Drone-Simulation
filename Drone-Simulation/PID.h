#pragma once
#include "globals.h"
#include "Movement.h"
#include "PIDr.h"

class PID {
	Movement* mvmt;
	PIDr* rigleta;
	float Ki, Kp, Kd;
	float* ref;
	float* err;
	float* lasterr;
	float* integr;
	float* deriv;
	int dim;
	double v[3];
public:
	PID(int, Movement*);
	void update();
	void setREF(float*);
};

