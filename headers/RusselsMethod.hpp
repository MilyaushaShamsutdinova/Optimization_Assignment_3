#ifndef OPTIMIZATION_ASSIGNMENT_3_RUSSELSMETHOD_HPP
#define OPTIMIZATION_ASSIGNMENT_3_RUSSELSMETHOD_HPP


#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Matrix.hpp"


using namespace std;


class RusselsMethod {
public:

    static void start_method(Matrix C, Vector S, Vector D);

private:

    static bool isSolvable(const Matrix &C, Vector &S, Vector &D);

    static void setValues(Matrix &X, Vector &S, Vector &D, int i, int j);

    static void printSolution(Matrix &X, const Matrix &C);

    static Vector max_coordinates(Matrix &D, Matrix &C, Vector &usable_rows, Vector &usable_cols);

};

#endif //OPTIMIZATION_ASSIGNMENT_3_RUSSELSMETHOD_HPP