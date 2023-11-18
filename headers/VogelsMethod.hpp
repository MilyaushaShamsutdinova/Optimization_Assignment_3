#ifndef OPTIMIZATION_ASSIGNMENT_3_VOGELSMETHOD_HPP
#define OPTIMIZATION_ASSIGNMENT_3_VOGELSMETHOD_HPP


#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Matrix.hpp"

class VogelsMethod {
public:

    static void start_method(Matrix C, Vector S, Vector D);

private:

    static bool isSolvable(const Matrix &C, const Vector &S, const Vector &D);

    static void calculate_row_difference(const Matrix &C, Vector &row_difference);

    static void calculate_col_difference(const Matrix &C, Vector &col_difference);

    static int index_of_max_element(Vector &vec);

    static int index_of_min_element_in_row(const Matrix &C, int row_index);

    static void set_value(Matrix &X, Vector &S, Vector &D, int i, int j);

    static int index_of_min_element_in_col(const Matrix &C, int col_index);

    static void printSolution(Matrix &X, const Matrix &C);

    //static bool check_unbalanced_problem(Matrix &X, Vector &S, Vector &D, int m, int n);
};
#endif //OPTIMIZATION_ASSIGNMENT_3_VOGELSMETHOD_HPP