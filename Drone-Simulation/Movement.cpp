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
}

void Movement::update() {
	//update viteze
	vx += ax;
	vy += ay;
	vz += az;

	//update coords
	x += vx;
	y += vy;
	z += vz;
}
