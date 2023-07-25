#include <iostream>
#include <string>
#include <cmath>
#include "blackscholes.cpp"

using namespace std;

double K = 1500;       //asset price
double F = 1600;       //forward price
double Q1 = 0.02;      //1st year probability of default
double Q2 = 0.03;      //2nd year probability of default
double rf_rate = 0.05; //risk free rate
double rec_rate = 0.3; //recovery rate
double sigma = 0.2;    //volatility of the forward price 
double timeT1 = 0.5;   //time first year
double timeT2 = 1.5;   //time second year (bc we're using 2 year forward contract for example)

// expected exposure at time t w(t)= e^-r(T-t) * [F * N(d1(t)) - K * N(d2(t))]
// where d1(t) = ln(F/K) + (sig^2 * t / 2)  / sig sqrt(t)
// and d2(t) = d1(t) - sig sqrt(t)
// so that the no default value v = w(ti)e^-rti * (1-R)

int main(){
    
    //this is a two period valuation, so for period 1 (t1)
    double d1t1 = blackscholes(F, K, rf_rate, sigma, timeT1);
    double d2t1 = d1t1 - sigma * sqrt(timeT1);
    double Nd1t1 = d1getnormsdist(d1t1);
    double Nd2t1 = d2getnormsdist(d2t1);

    double wt1 = expectedexposure(rf_rate, timeT2, F, Nd1t1, K, Nd2t1);
    double vt1 = nodefaultvalue(wt1, rf_rate, timeT1, rec_rate);
    cout << "The expected exposure at time t1 is: "<< wt1 <<endl;
    cout << "The no default value Vi at time t1 is: "<< vt1 <<endl;

    //for period 2 (t2)
    double d1t2 = blackscholes(F, K, rf_rate, sigma, timeT2);
    double d2t2 = d1t2 - sigma * sqrt(timeT2);
    double Nd1t2 = d1getnormsdist(d1t2);
    double Nd2t2 = d2getnormsdist(d2t2);

    double wt2 = expectedexposure(rf_rate, timeT2, F, Nd1t2, K, Nd2t2);
    double vt2 = nodefaultvalue(wt2, rf_rate, timeT2, rec_rate); 
    cout << "The expected exposure at time t2 is: "<< wt2 <<endl;
    cout << "The no default value Vi at time t2 is: "<< vt2 <<endl;
    
    //The expected cost of defaults is q1v1 þ q2v2
    double expcostdefault = Q1 * vt1 + Q2 * vt2; 
    cout << "The expected cost of default is: "<< expcostdefault<<endl<<endl;

    //The no-default value of the forward contract is (F - K)e^-rt. When counterparty defaults are considered, the value drops by the amount of expected cost of defaults
    double value_forward = (F - K) * exp(-rf_rate * (timeT1 + timeT2));
    double value_cr_adjusted = value_forward - expcostdefault;
    cout << "The final credit risk adjusted value of the derivative is: " << value_cr_adjusted <<endl;
}
