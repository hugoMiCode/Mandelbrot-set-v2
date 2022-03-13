#include "Complexe.h"

float Complexe::Radian(double angle)
{
    return (angle * PI / 180.0);
}

float Complexe::getAlpha()
{
    // Eviter les calculs inutiles

    if (re == 0.0 && im == 0)
        return 0.0;

    double alpha;
    double cosinus;


    cosinus = re / getModule();

    alpha = acos(cosinus);
    alpha = (alpha * 180.0 / PI);

    if (im < 0.0)
        alpha = 360 - alpha;

    return alpha;
}

double Complexe::getModule()
{
    return sqrt((re * re) + (im * im));
}

Complexe Complexe::conjugue()
{
    return Complexe(re, -im);
}

void Complexe::rotation(double angle)
{
    double total = angle + getAlpha();

    Complexe aux(total);

    double module = getModule();

    re = aux.getReel() * module;
    im = aux.getImaginaire() * module;
}

void Complexe::translation(double x, double y)
{
    Complexe translation(x, y);

    Complexe nouveau = translation + (*this);

    re = nouveau.getReel();
    im = nouveau.getImaginaire();
}

void Complexe::translation(Complexe& complexe)
{
    Complexe translation(complexe.getReel(), complexe.getImaginaire());

    Complexe nouveau = translation + (*this);

    re = nouveau.getReel();
    im = nouveau.getImaginaire();
}

Complexe Complexe::operator =(const Complexe& complexe)
{
    re = complexe.re;
    im = complexe.im;

    return *this;
}

bool Complexe::operator ==(const Complexe& complexe)
{
    if (re == complexe.re && im == complexe.im)
        return true;
    return false;
}

bool Complexe::operator !=(const Complexe& complexe)
{
    if (re != complexe.re || im != complexe.im)
        return true;
    return false;
}

Complexe Complexe::operator -(const Complexe& complexe)
{
    return Complexe(re - complexe.re, im - complexe.im);
}

Complexe Complexe::operator +(const Complexe& complexe)
{
    return Complexe(re + complexe.re, im + complexe.im);
}

Complexe Complexe::operator *(const Complexe& complexe)
{
    Complexe ptComplexe{};

    ptComplexe.im = re * complexe.im + im * complexe.re;
    ptComplexe.re = re * complexe.re - im * complexe.im;

    return ptComplexe;
}

Complexe Complexe::operator /(const Complexe& complexe)
{
    Complexe ptComplexe{};

    ptComplexe.im = -re * complexe.im + im * complexe.re;
    ptComplexe.re = re * complexe.re + im * complexe.im;

    double denominateur = complexe.re * complexe.re + complexe.im * complexe.im;

    ptComplexe.im /= denominateur;
    ptComplexe.re /= denominateur;

    return ptComplexe;
}

Complexe::Complexe(double reel, double imaginaire)
{
    re = reel;

    im = imaginaire;
}

Complexe::Complexe()
{
    re = 0.0;
    im = 0.0;
}

Complexe::Complexe(const Complexe& complexe)
{
    re = complexe.re;
    im = complexe.im;
}

Complexe::Complexe(double angle)
{
    re = cos(Radian(angle));
    im = sin(Radian(angle));
}

Complexe::~Complexe()
{
    re = 0.0;
    im = 0.0;
}