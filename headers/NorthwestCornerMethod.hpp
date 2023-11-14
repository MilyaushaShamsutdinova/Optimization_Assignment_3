#ifndef OPTIMIZATION_ASSIGNMENT_3_NORTHWESTCORNERMETHOD_HPP
#define OPTIMIZATION_ASSIGNMENT_3_NORTHWESTCORNERMETHOD_HPP


#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Matrix.hpp"


using namespace std;


class NorthwestCornerMethod {
public:
    static void start_method(const Matrix &C, Vector &S, Vector &D);

private:

    static bool isSolvable(const Matrix &C, Vector &S, Vector &D);
    static void printInitialTable(const Matrix &C, Vector &S, Vector &D);
    static void setValues(Matrix &X, Vector &S, Vector &D, int i, int j);
    static void printSolution(Matrix &X, const Matrix &C);

};

#endif //OPTIMIZATION_ASSIGNMENT_3_NORTHWESTCORNERMETHOD_HPP