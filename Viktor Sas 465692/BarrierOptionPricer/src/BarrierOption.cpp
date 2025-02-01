#include <iostream>
#include <cmath>
#include "getOneGaussianByBoxMueller.h"
#include "BarrierOption.h"


//definition of constructor
BarrierOption::BarrierOption(
    int nInt_,
    double strike_,
    double spot_,
    double vol_,
    double r_,
    double expiry_,
    double barrier_) {
    nInt = nInt_;
    strike = strike_;
    spot = spot_;
    vol = vol_;
    r = r_;
    expiry = expiry_;
    barrier = barrier_;
    generatePath();
}

//method definition
void BarrierOption::generatePath() {
    double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
    double cumShocks = 0;
    thisPath.clear();

    for (int i = 0; i < nInt; i++) {
        cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
        thisPath.push_back(spot * exp(cumShocks));
    }
}

//method definition
double BarrierOption::getArithmeticMean() {
    double runningSum = 0.0;
    for (int i = 0; i < nInt; i++) {
        runningSum += thisPath[i];
    }
    return runningSum / double(nInt);
}

//method definition
double BarrierOption::getGeometricMean() {
    double runningSum = 0.0;
    for (int i = 0; i < nInt; i++) {
        runningSum += log(thisPath[i]);
    }
    return exp(runningSum / double(nInt));
}

//method definition
void BarrierOption::printPath() {
    for (int i = 0; i < nInt; i++) {
        std::cout << thisPath[i] << "\n";
    }
}

//method definition
double BarrierOption::getUpAndOutCallPrice(int nReps) {
    double rollingSum = 0.0;
    double thisPayoff = 0.0;
    bool barrierHit;

    for (int i = 0; i < nReps; i++) {
        generatePath();
        barrierHit = false;

        for (int j = 0; j < nInt; j++) {
            if (thisPath[j] >= barrier) {
                barrierHit = true;
                break;
            }
        }

        if (!barrierHit) {
            thisPayoff = (thisPath.back() > strike) ? (thisPath.back() - strike) : 0;
        } else {
            thisPayoff = 0;
        }

        rollingSum += thisPayoff;
    }

    return exp(-r * expiry) * rollingSum / double(nReps);
}

//overloaded operator ();
double BarrierOption::operator()(char char1, int nReps) {
    if (char1 == 'U' && nReps > 0) {
        return getUpAndOutCallPrice(nReps);
    } else {
        return -99;
    }
}