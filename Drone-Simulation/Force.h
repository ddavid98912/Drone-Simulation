#pragma once
class Force
{
	//componentele pe x, y, z
	double x, y, z;
public:
	Force();
	Force(double, double, double);
	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	void addForce(Force);
	void addForce(double, double, double);
};

