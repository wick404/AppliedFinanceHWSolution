#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "BarrierOption.h"
#include "getVecMean.h"
#include "getVecStdDev.h"

using std::vector;
using std::cout;
using std::cin;

int main() {
    
    // set the seed
    srand(time(NULL));

    //create a new instance of class
    BarrierOption myBarrier(126, 110, 105, 0.21, 0.05, 0.75, 120);

    // Iterate over all the elements.
    // myAsian.printPath();

    //get arithmetic means
    cout << "Arithmetic mean = " << myBarrier.getArithmeticMean() << "\n";
    cout << "Geometric mean = " << myBarrier.getGeometricMean() << "\n";

    //get last price of underlying
    cout << "Last price of underlying = " << myBarrier.thisPath.back() << "\n";

    //run Monte Carlo to obtain theoretical price of Asian options
    cout << "Price of up-and-out call = " << myBarrier.getUpAndOutCallPrice(10000) << "\n";

    //call Monte Carlo via overloaded () operator
    cout << "Calling function via operator() \n";
    cout << "Price of up-and-out call = " << myBarrier('U', 10000) << "\n";

    //check whether the Data Generating Process runs correctly
    //(is the expected price and volatility of underlying close to option parameters?)
    vector<double> myVec2;
    for (int i = 0; i < 1000; i++) {
        myBarrier.generatePath();
        myVec2.push_back(myBarrier.thisPath.back());
    }

    cout << "mean of last underlying prices is " << getVecMean(myVec2) << "\n";
    cout << "stddev of last underlying prices is " << getVecStdDev(myVec2) << "\n";
    //cout << "\nPress Enter to continue...";
    //cin.get();
    return 0;
}