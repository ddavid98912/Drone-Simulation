#include "PIDr.h"

PIDr::PIDr(int n, Movement* M) {
	ref = new float[n];
	err = new float[n];
	lasterr = new float[n];
	integr = new float[n];
	deriv = new float[n];
	mvmt = M;
	//Kp = 8*Kd / Tu ; unde Tu = perioada de oscilatie https://en.wikipedia.org/wiki/PID_controller#Ziegler%E2%80%93Nichols_method
	Ki = 0;
	Kd = 0.4;
	Kp = 32;
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
	T = sqrt(vx * vx + vy * vy + vz * vz);
	if (T == 0)
	{
		ref[0] = 0;
		ref[1] = 0;
		return;
	}

	if (vy < 0)
		T = -T;

	/*if (vx >= 0 && vy >= 0) {
		std::cout << "ref1 " << ((T - vx) / T) - (int)((((T - vx) / T) / 2) * 2) << std::endl;
		std::cout << "ref2 " << (vy / (T - vx)) - (int)(((vy / (T - vx)) / 2) * 2) << std::endl;

		ref[0] = acos( ((T - vx) / T) - (int)((((T - vx) / T) / 2) * 2));
		ref[1] = acos( (vy / (T - vx)) - (int)(((vy / (T - vx))/2) * 2));
	}
	else if (vx >= 0 && vy < 0) {
		std::cout << "ref1 " << ((T - vx) / T) - (int)((((T - vx) / T) / 2) * 2) << std::endl;
		std::cout << "ref2 " << ((T - vx - vz) / (T - vx)) - (int)((((T - vx - vz) / (T - vx)) / 2) * 2) << std::endl;

		ref[0] = acos(((T - vx) / T) - (int)((((T - vx) / T) / 2) * 2));
		ref[1] = acos(((T - vx - vz) / (T - vx)) - (int)((((T - vx - vz) / (T - vx))/2)*2));
	}
	else if (vx < 0 && vy >= 0) {

		std::cout << "ref1 " << ((vx + T) / T) - (int)((((vx + T) / T) / 2) * 2) << std::endl; 
		std::cout << "ref2 " << (vy / (T - vx)) - (int)(((vy / (T - vx)) / 2) * 2) << std::endl;

		ref[0] = acos( ((vx + T) / T) - (int)((((vx + T) / T)/2)*2)) ;
		ref[1] = acos((vy / (T - vx)) - (int)(((vy / (T - vx)) / 2) * 2));
	}
	else if (vx < 0 && vy < 0) {
		std::cout << "ref1 " << ((vx + T) / T) - (int)((((vx + T) / T) / 2) * 2) << std::endl;
		std::cout << "ref2 " << ((T - vx - vz) / (T - vx)) - (int)((((T - vx - vz) / (T - vx)) / 2) * 2) << std::endl;

		ref[0] = acos(((vx + T) / T) - (int)((((vx + T) / T) / 2) * 2));
		ref[1] = acos(((T - vx - vz) / (T - vx)) - (int)((((T - vx - vz) / (T - vx)) / 2) * 2));
	}
	*/
	ref[0] = atan((vx) / (T * sqrt(1 - ((vx * vx) / (T * T)))));
	//ref[1] = atan(sqrt(T * T - vy * vy - vx * vx) / vy);
	ref[1] = atan(vz / vy);


	ref[0] = ref[0] * 180 / PI;
	ref[1] = ref[1] * 180 / PI;
}

void PIDr::update() {
	std::cout << "ref[0]: " << ref[0] << " ref[1]: " << ref[1] << std::endl;
	err[0] = ref[0] - (mvmt->roll * 180 / PI);
	err[1] = ref[1] - (mvmt->pitch * 180 / PI);

	std::cout << "err1 " << err[0] << " err2 " << err[1] << std::endl;

	for (int i = 0; i < dim; i++) {

		integr[i] += err[i] * mvmt->time_step;
		deriv[i] = err[i] - lasterr[i];

	}
	double c_roll = Kp * err[0] + Ki * integr[0] + Kd * deriv[0];
	double c_pitch = Kp * err[1] + Ki * integr[1] + Kd * deriv[1];

	mvmt->forte[0].setMag(T / 4 - c_pitch / 2 + c_roll / 2 + mass * 2.5);
	mvmt->forte[1].setMag(T / 4 - c_pitch / 2 - c_roll / 2 + mass * 2.5);
	mvmt->forte[2].setMag(T / 4 + c_pitch / 2 + c_roll / 2 + mass * 2.5);
	mvmt->forte[3].setMag(T / 4 + c_pitch / 2 - c_roll / 2 + mass * 2.5);

	for (int i = 0; i < dim; i++) {
		lasterr[i] = err[i];
	}
}
