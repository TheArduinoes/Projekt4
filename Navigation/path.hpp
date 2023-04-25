#include <vector>

class path {
public:
    path(const std::vector<double>& x_vals, const std::vector<double>& y_vals, int bordNummer)          
        : x_vals_(x_vals), y_vals_(y_vals), bordNummer_(bordNummer) {}

    std::vector<double> getXVals() const { return x_vals_; }
    std::vector<double> getYVals() const { return y_vals_; }
    int getBordNummmer(){return bordNummer_}


    //Mangler get FSK kode eller netværksid

private:
    const std::vector<double> x_vals_;
    const std::vector<double> y_vals_;
    const int bordNummer_;

    //Mangler FSK kode eller netværksid
};
