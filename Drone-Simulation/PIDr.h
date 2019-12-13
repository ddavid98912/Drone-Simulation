#pragma once
#include "globals.h"
#include <math.h>
#include "Movement.h"

class PIDr {
	Movement* mvmt;
	float Ki, Kp, Kd;
	float* ref;
	float* err;
	float* lasterr;
	float* integr;
	float* deriv;
	int dim;
	double T;
public:
	PIDr(int, Movement*);
	void calcAngles(double, double, double);
	void update();
};

