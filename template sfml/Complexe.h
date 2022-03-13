#pragma once
#include <cmath>
#include <ostream>

#define PI 3.1415926535

class Complexe
{

private:
	double im;
	double re;

public:
	void rotation(double angle);

	void translation(double x, double y);
	void translation(Complexe& complexe);

	Complexe conjugue();

	float getAlpha();
	double getModule();

	inline double getReel() { return re; };
	inline double getImaginaire() { return im; };

	Complexe operator =(const Complexe& complexe);
	Complexe operator +(const Complexe& complexe);
	Complexe operator -(const Complexe& complexe);
	Complexe operator *(const Complexe& complexe);
	Complexe operator /(const Complexe& complexe);

	bool operator ==(const Complexe& complexe);
	bool operator !=(const Complexe& complexe);

	Complexe();
	Complexe(double angle);
	Complexe(const Complexe& complexe);
	Complexe(double reel, double imaginaire);

	virtual ~Complexe();

protected:
	float Radian(double angle);
};

