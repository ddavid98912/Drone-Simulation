#include "Force.h"
#include <iostream>

Force::Force() {
	x = 0;
	y = 0;
	z = 0;
	pitch = 0;
	yaw = 0;
	roll = 0;
	magnitude = 0;
}

Force::Force(double initx, double inity, double initz) {
	x = initx;
	y = inity;
	z = initz;
	pitch = 0;
	yaw = 0;
	roll = 0;
	magnitude = 0;
}

void Force::addForce(Force f) {
	x = x + f.getX();
	y = y + f.getY();
	z = z + f.getZ();
}

void Force::addForce(double x_comp, double y_comp, double z_comp) {
	x = x + x_comp;
	y = y + y_comp;
	z = z + z_comp;
}

void Force::setMag(double mag) {
	magnitude = mag;
}

void Force::set(double xval, double yval, double zval) {
	x = xval;
	y = yval;
	z = zval;
}

void Force::setAngles(double r, double p, double y)
{
	//Functia primeste ungiurile in grade din Movement (asa le calculeaza si OpenGL)
	//si trebuie sa le treaca in radiani pt cmath

	roll = r * PI / 180.0;
	pitch = p * PI / 180.0;
	yaw = -y * PI / 180.0;

}

void Force::setX(double val) {
	x = val;
}

void Force::setY(double val) {
	y = val;
}

void Force::setZ(double val) {
	z = val;
}

double Force::getX() {
	return x;
}

double Force::getY() {
	return y;
}

double Force::getZ() {
	return z;
}

void Force::calcComp() {
	/*z = magnitude * cos(unghiZ) * sin(unghiY);
	y = magnitude * cos(unghiY);
	x = magnitude * sin(unghiZ) * sin(unghiY);*/

	//Rezultate luate de aici: https://math.stackexchange.com/questions/1637464/find-unit-vector-given-roll-pitch-and-yaw

	//updateul unghiurilor

	//Componenta verticala dupa transformare:
	y = magnitude * cos(roll) * cos(pitch);

	//Componenta orizontala fata-spate:
	z = -magnitude * (sin(roll) * sin(yaw) - cos(roll) * sin(pitch) * cos(yaw));

	//Componenta laterala stanga-dreapta:
	x = magnitude * ( -sin(roll) * cos(yaw) - cos(roll) * sin(pitch) * sin(yaw));
}

double* Force::calcMom(double* bF) {
	//bF este bratul fortei
	mom[0] = bF[1] * z + bF[2] * y;
	mom[1] = bF[2] * x - bF[0] * z;
	mom[2] = bF[0] * y - bF[1] * x;
	return mom;
}
