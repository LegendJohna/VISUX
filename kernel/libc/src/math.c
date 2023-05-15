#include "../include/math.h"
static const double PI = 3.14159265358979323846;
static const double e = 2.7182818284590452354;
static const double ln2 = 0.69314718055994530942;
static const double ln10 = 2.30258509299404568402;

double pown(double x,int n)
{
    if(n<0) return 1/pow(x,-n);
    double result = 1.0;
    while(n)
    {
        if(n&1) 
        {
            result *= x;
        }
        x *= x;
        n >>= 1;
    }
    return result;
}

double sin (double x)
{
    return 1.0;
}
double cos (double x)
{
    return 1.0;
}
double tan (double x)
{
    return 1.0;
}
double sinh (double x)
{
    return 1.0;
}
double cosh (double x)
{
    return 1.0;
}
double tanh (double x)
{
    return 1.0;
}
double asin (double x)
{
    return 1.0;
}
double acos (double x)
{
    return 1.0;
}
double atan (double x)
{
    return 1.0;
}
double atan2 (double x, double y)
{
    return 4.0;
}
double exp (double x)
{
    return 1.0;
}
double log (double x)
{
    return 1.0;
}
double log10 (double x)
{
    return 1.0;
}
double pow (double x, double n)
{
    return 1.0;
}
double sqrt (double x)
{
    return 1.0;
}
double ceil (double x)
{
    return 1.0;
}
double floor (double x)
{
    return 1.0;
}
double fabs (double x)
{
    return (x>0?x:(-x));
}
double ldexp (double x, int n)
{
    return 1.0;
}
double frexp (double x, int* p)
{
    return 1.0;
}
double modf (double x, double* y)
{
    return 1.0;
}
double fmod (double x, double y)
{
    return 1.0;
}