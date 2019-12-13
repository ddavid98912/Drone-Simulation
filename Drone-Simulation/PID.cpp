#include "PID.h"

PID::PID(int n, Movement* M) {
	ref = new float[n];
	err = new float[n];
	lasterr = new float[n];
	integr = new float[n];
	deriv = new float[n];
	mvmt = M;
	rigleta = new PIDr(2, mvmt);
	Ki = 0;
	Kd = -50;
	Kp = 1;
	dim = n;

	for (int i = 0; i < n; i++) {
		ref[i] = 0;
		err[i] = 0;
		lasterr[i] = 0;
		integr[i] = 0;
		deriv[i] = 0;
	}
}

void PID::update() {
	err[0] = ref[0] - mvmt->x;
	err[1] = ref[1] - mvmt->y;
	err[2] = ref[2] - mvmt->z;

	for (int i = 0; i < dim; i++) {

		integr[i] += err[i] * mvmt->time_step;
		deriv[i] = err[i] - lasterr[i];

	}

	v[0] = Kp * err[0] + Ki * integr[0] + Kd * deriv[0];
	v[1] = Kp * err[1] + Ki * integr[1] + Kd * deriv[1];
	v[2] = Kp * err[2] + Ki * integr[2] + Kd * deriv[2];

	for (int i = 0; i < dim; i++) {
		lasterr[i] = err[i];
	}

	rigleta->calcAngles(v[0], v[1], v[2]);
	rigleta->update();
}

void PID::setREF(float* r) {

	for (int i = 0; i < dim; i++) {
		ref[i] = r[i];
	}
}


