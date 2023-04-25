#include <iostream>
#include "path.hpp"

int main() {
    std::vector<double> x_vals = {0.0, 1.0, 2.0, 3.0};
    std::vector<double> y_vals = {0.0, 1.0, 2.0, 3.0};
    path my_path(x_vals, y_vals);

    std::vector<double> x_copy = my_path.getXVals();
    std::vector<double> y_copy = my_path.getYVals();

    for (int i = 0; i < x_copy.size(); i++) {
        std::cout << "(" << x_copy[i] << ", " << y_copy[i] << ")" << std::endl;
    }

    return 0;
}
