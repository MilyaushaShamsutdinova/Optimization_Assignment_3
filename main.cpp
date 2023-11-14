#include <iostream>

#include "headers/Matrix.hpp"
#include "headers/Vector.hpp"
#include "headers/NorthwestCornerMethod.hpp"
#include "headers/RusselsMethod.hpp"

using namespace std;

void perform() {
    int n, m;

    //cout << "Enter number of basic variables:\n";
    cin >> m;
    //cout << "Enter number of constraint functions:\n";
    cin >> n;

    Vector S(m), D(n);
    Matrix C(m, n);

    cin >> C;
    cin >> S;
    cin >> D;

    NorthwestCornerMethod::start_method(C,S,D);

    //VogelMethod::start_method.....

    RusselsMethod::start_method(C,S,D);
}

int main() {
    perform();
    //system("pause");
    return EXIT_SUCCESS;
}