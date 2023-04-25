#include "path.hpp" 
#include <iostream>

int main() {
    std::vector<double> x_vals = {0.0, 1.0, 2.0, 3.0};
    std::vector<double> y_vals = {0.0, 1.0, 2.0, 3.0};
    int bordNummer = 42;
    path my_path(x_vals, y_vals, bordNummer);

    std::vector<double> x_copy = my_path.getXVals();
    std::vector<double> y_copy = my_path.getYVals();

    std::cout << "Path points:" << std::endl;
    for (int i = 0; i < x_copy.size(); i++) {
        std::cout << "(" << x_copy[i] << ", " << y_copy[i] << ")" << std::endl;
    }

    int bord_nummer = my_path.getBordNummer();
    std::cout << "Board number: " << bord_nummer << std::endl;

    return 0;
}
