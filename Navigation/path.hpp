#include <vector>

class path {
public:
    path(const std::vector<double>& x_vals, const std::vector<double>& y_vals)          
        : x_vals_(x_vals), y_vals_(y_vals) {}

    std::vector<double> getXVals() const { return x_vals_; }
    std::vector<double> getYVals() const { return y_vals_; }

private:
    const std::vector<double> x_vals_;
    const std::vector<double> y_vals_;
};
