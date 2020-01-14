#include "PIDr.h"

PIDr::PIDr(int n, Movement* M) {
	ref = new float[n];
	err = new float[n];
	lasterr = new float[n];
	integr = new float[n];
	deriv = new float[n];
	mvmt = M;
	//Kp = 8*Kd / Tu ; unde Tu = perioada de oscilatie https://en.wikipedia.org/wiki/PID_controller#Ziegler%E2%80%93Nichols_method
	Ki =0;
	Kd = 11;
	Kp = 10;
	dim = n;
	T = 0;

	for (int i = 0; i < n; i++) {
		ref[i] = 0;
		err[i] = 0;
		lasterr[i] = 0;
		integr[i] = 0;
		deriv[i] = 0;
	}
}

void PIDr::calcAngles(double vx, double vy, double vz) {
	vy += mass * 10;
	T = sqrt(vx * vx + vy * vy + vz * vz);
	if (T == 0)
	{
		ref[0] = 0;
		ref[1] = 0;
		return;
	}

	if (vy < 0)
		T = -T;

	
	//ref[0] = atan((vx) / (T * sqrt(1 - ((vx * vx) / (T * T)))));
	//ref[1] = atan(sqrt(T * T - vy * vy - vx * vx) / vy);
	ref[0] = atan(-vx / sqrt(vy * vy + vz * vz));
	ref[1] = atan(vz / vy);


	ref[0] = ref[0] * 180 / PI;
	ref[1] = ref[1] * 180 / PI;
}

void PIDr::update() {
	err[0] = ref[0] - (mvmt->roll);
	err[1] = ref[1] - (mvmt->pitch);

	for (int i = 0; i < dim; i++) {

		integr[i] += err[i] * mvmt->time_step;
		deriv[i] = (err[i] - lasterr[i]) / mvmt->time_step;

	}
	double c_roll = Kp * err[0] + Ki * integr[0] + Kd * deriv[0];
	double c_pitch = Kp * err[1] + Ki * integr[1] + Kd * deriv[1];

	mvmt->forte[0].setMag(T / 4 - c_pitch / 2 - c_roll / 2);
	mvmt->forte[1].setMag(T / 4 - c_pitch / 2 + c_roll / 2);
	mvmt->forte[2].setMag(T / 4 + c_pitch / 2 - c_roll / 2);
	mvmt->forte[3].setMag(T / 4 + c_pitch / 2 + c_roll / 2);

	for (int i = 0; i < dim; i++) {
		lasterr[i] = err[i];
	}
}
