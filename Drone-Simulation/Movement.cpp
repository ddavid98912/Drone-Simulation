#include "Movement.h"
#include <iostream>

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
	time_step = 0.016;
}

void Movement::update() {
	// timp
	time = time + time_step;

	updateForces();

	//update acceleratii
	ax = res.getX() / mass;
	ay = res.getY() / mass;
	az = res.getZ() / mass;

//	std::cout << ax << " " << ay << " " << az << std::endl;
	
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
	res.set(0, 0, 0);
	for (int i = 0; i < 4; i++) {
		//set magnitude undeva

		forte[i].calcComp();
		res.addForce(forte[i]);
	}
	frecare.set(-beta * vx, -beta * vy, -beta * vz);
	res.addForce(frecare);

//	std::cout << "Res: " << res.getX() << " " << res.getY() << " " << res.getZ() << std::endl;
}
