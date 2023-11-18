#ifndef OPTIMIZATION_ASSIGNMENT_3_VOGELSMETHOD_HPP
#define OPTIMIZATION_ASSIGNMENT_3_VOGELSMETHOD_HPP


#include <iostream>
#include <vector>
#include "Vector.hpp"
#include "Matrix.hpp"

class VogelsMethod {
public:
    static void start_method(Matrix C, Vector S, Vector D);

    static int calculateTotalCost(Matrix &X, const Matrix &C);

    static void printInitialTable(const Matrix &C, Vector &S, Vector &D);

    static bool isSolvable(const Matrix &C, const Vector &S, const Vector &D);

    static void calculate_row_difference(const Matrix &C, Vector &row_d, Vector &col_d, int m, int n);

    static void calculate_col_difference(const Matrix &C, Vector &row_d, Vector &col_d, int m, int n);

    static int max_ind(Vector &vec);

    static int find_min_ind_in_row(const Matrix &C, Vector &row_d, int row, int m, int n);

    static void set_value(Matrix &X, Vector &S, Vector &D, int i, int j);

    static int find_min_ind_in_col(const Matrix &C, Vector &col_d, int col, int m, int n);

    static bool check_unbalanced_problem(Matrix &X, Vector &S, Vector &D, int m, int n);
};
#endif //OPTIMIZATION_ASSIGNMENT_3_VOGELSMETHOD_HPP