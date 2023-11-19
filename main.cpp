#include <iostream>

#include "headers/Matrix.hpp"
#include "headers/Vector.hpp"
#include "headers/NorthwestCornerMethod.hpp"
#include "headers/VogelsMethod.hpp"
#include "headers/RusselsMethod.hpp"

using namespace std;

void perform() {
    int n, m;

    cout << "Enter number of sources:\n";
    cin >> m;
    cout << "Enter number of destinations:\n";
    cin >> n;

    Vector S(m), D(n);
    Matrix C(m, n);

    cout << "Enter the transportation cost table:\n";
    cin >> C;
    cout << "Enter the vector of supply:\n";
    cin >> S;
    cout << "Enter the vector of demand:\n";
    cin >> D;
    cout << "\n\n";

    NorthwestCornerMethod::start_method(C,S,D);

    VogelsMethod::start_method(C,S,D);

    RusselsMethod::start_method(C,S,D);
}

int main() {
    perform();
    system("pause");
    return EXIT_SUCCESS;
}