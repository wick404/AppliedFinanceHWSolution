#include <vector>

class BarrierOption {
public:
    //constructor
    BarrierOption(
        int nInt_,
        double strike_,
        double spot_,
        double vol_,
        double r_,
        double expiry_,
        double barrier_
    );

    //destructor
    ~BarrierOption(){};

    //methods
    void generatePath();
    double getArithmeticMean();
    double getGeometricMean();
    void printPath();
    double getUpAndOutCallPrice(int nReps);
    double operator()(char char1, int nReps);

    //members
    std::vector<double> thisPath;
    int nInt;
    double strike;
    double spot;
    double vol;
    double r;
    double expiry;
    double barrier; 
};