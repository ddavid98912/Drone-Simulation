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

	//update acceleratii
	ax = res.getX() / mass;
	ay = res.getY() / mass;
	az = res.getZ() / mass;
	
	//update viteze
	vx += ax * time_step;
	vy += ay * time_step;
	vz += az * time_step;

	//update coords
	x += vx * time_step;
	y += vy * time_step;
	z += vz * time_step;
}

void Movement::modVel(double deltaVx, double deltaVy, double deltaVz) {
	vx = deltaVx;
	vy = deltaVy;
	vz = deltaVz;
}

void Movement::updateForces() {
	// am considerat sistemul de axe relativ cu camera viewul, nu cu drona..	
	for (int i = 0; i < 4; i++) {
		res.addForce(forte[i]);
	}
	//efectul greutatii
	res.addForce(0, -mass * 9.81, 0);
}
