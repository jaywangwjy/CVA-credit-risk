#include <cmath>
#include <iostream>
#include <string>

using namespace std;

double blackscholes (double S, double K, double r, double sig, double t){
    double numerator = (log(S) - log(K)) + ((sig * sig) * t);
	double denominator = sig * sqrt(t);
    return numerator / denominator;

}

double d1getnormsdist (double d1){
    return 0.5 * erfc(-d1 * M_SQRT1_2);
}

double d2getnormsdist (double d2){
    return 0.5 * erfc(-d2 * M_SQRT1_2);
}

//w(t)= e^-r(T-t) * [F * N(d1(t)) - K * N(d2(t))]
double expectedexposure (double r, double t2, double F, double nd1, double K, double nd2){
    return exp(-r*t2) * (F * nd1 - K * nd2);
}

// v = w(ti)e^-rti * (1-R)
double nodefaultvalue (double w, double r, double t1, double R){
    return w * exp(-r*t1) * (1-R);
}