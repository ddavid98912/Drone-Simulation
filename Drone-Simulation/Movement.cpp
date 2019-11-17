#include "Movement.h"

Movement::Movement(double x, double y, double z, double vx, double vy, double vz, double ax, double ay, double az) {

	this->x = x;
	this->y = y;
	this->z = z;
	this->vx = x;
	this->vy = y;
	this->vz = vz;
	this->ax = ax;
	this->ay = ay;
	this->az = az;
	time = 0;
	time_step = 0.01;
}

void Movement::update() {

	// timp
	time = time + time_step;
	
	//update viteze
	vx += ax * time_step;
	vy += ay * time_step;
	vz += az * time_step;

	//update coords
	x += vx * time_step;
	y += vy * time_step;
	z += vz * time_step;
	
	//forte

	
}
