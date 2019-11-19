#include "Force.h"

Force::Force() {
	x = 0;
	y = 0;
	z = 0;
}

Force::Force(double initx, double inity, double initz) {
	x = initx;
	y = inity;
	z = initz;
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
