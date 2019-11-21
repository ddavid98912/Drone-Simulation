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

	roll = pitch = yaw = 0;
	v_roll = v_pitch = v_yaw = 0;
	a_roll = a_pitch = a_yaw = 0;
	greutate.set(0, -mass / 10, 0);


	time = 0;
	time_step = 0.016;
}

void Movement::update() {
	// timp
	time = time + time_step;

	updateForces();

	//luate fata de openGL
	//roll cu axa de rotatie oZ
	a_roll = moments[2] / mass;
	//pitch cu axa de rotatie oX
	a_pitch = moments[0] / mass;
	//yaw cu axa de rotatie oY
	a_yaw = moments[1] / mass;

	//update vitezele unghiulare
	v_roll += a_roll * time_step;
	v_pitch += a_pitch * time_step;
	v_yaw += a_yaw * time_step;

	//update unghiuri
	roll += v_roll * time_step;
	pitch += v_pitch * time_step;
	yaw += v_yaw * time_step;

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

	//std::cout << "Coords: " << x << " " << y << " " << z << std::endl;
	std::cout << "unghiuri: " << roll << " " << pitch << " " << yaw << std::endl;
}

void Movement::modVel(double deltaVx, double deltaVy, double deltaVz) {
	vx = deltaVx;
	vy = deltaVy;
	vz = deltaVz;
}

void Movement::updateForces() {
	// am considerat sistemul de axe relativ cu camera viewul, nu cu drona..	
	//setam Forta rezulatnat si momentul rezultant 0 la fiecare frame apoi le calculam
	res.set(0, 0, 0);
	for (int i = 0; i < 3; i++) {
		moments[i] = 0;
	}
	double* mom = new double[3];
	for (int i = 0; i < 4; i++) {
		//set magnitude undeva
		forte[i].setAngles(roll, pitch, yaw);
		forte[i].calcComp();
		
		//aici calculam momentul pt fiecare din fortele generate de elice
		if (i == 0) {
			//fata-stanga
			double brat[3] = { -width / 2, -length / 2, height / 2 };
			mom = forte[i].calcMom(brat);
			//std::cout << "Moment fata-stanga: " << mom[0] << " " << mom[1] << " " << mom[2] << std::endl;
		}
		else if (i == 1) {
			//fata-dreapta
			double brat[3] = { width / 2, -length / 2, height / 2 };
			mom = forte[i].calcMom(brat);
			//std::cout << "Moment fata-dreapta: " << mom[0] << " " << mom[1] << " " << mom[2] << std::endl;
		}
		else if (i == 2) {
			//spate-stanga
			double brat[3] = { -width / 2, length / 2, height / 2 };
			mom = forte[i].calcMom(brat);
			//std::cout << "Moment spate-stanga: " << mom[0] << " " << mom[1] << " " << mom[2] << std::endl;
		}
		else if (i == 3) {
			//spate-dreapta
			double brat[3] = { width / 2, length / 2, height / 2 };
			mom = forte[i].calcMom(brat);
			//std::cout << "Moment spate-dreapta: " << mom[0] << " " << mom[1] << " " << mom[2] << std::endl;
		}
		//aici adaugam la momentul total
		for (int j = 0; j < 3; j++) {
			moments[j] += mom[j];
		}
		//forta totala
		res.addForce(forte[i]);
	}
	
	frecare.set(-beta * vx, -beta * vy, -beta * vz);
	res.addForce(frecare);
	if (y > 0) {
		res.addForce(greutate);
	}

	//std::cout << "Res: " << res.getX() << " " << res.getY() << " " << res.getZ() << std::endl;
}
