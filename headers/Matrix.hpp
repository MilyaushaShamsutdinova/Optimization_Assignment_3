#ifndef OPTIMIZATION_ASSIGNMENT_3_MATRIX_HPP
#define OPTIMIZATION_ASSIGNMENT_3_MATRIX_HPP

#include <iostream>
#include <iterator>
#include "Vector.hpp"

using namespace std;

class Matrix {
public:
    Matrix();

    Matrix(int rows, int columns);

    Matrix(const Matrix &other);

    ~Matrix();

    [[nodiscard]] int rows() const;

    [[nodiscard]] int columns() const;

    double &operator()(int row, int column);

    double operator()(int row, int column) const;

    Matrix &operator=(const Matrix &other);

    Vector operator*(Vector vector);

    Matrix operator*(const Matrix& item) const;

    Matrix& operator*=(const Matrix& item);

    Matrix operator-(const Matrix& item) const;

    Matrix& operator-=(const Matrix& item);

    [[nodiscard]] Vector getRow(int index) const;

    void setRow(int index, Vector &vector);

    [[nodiscard]] Vector getCol(int index) const;

    void setCol(int index, Vector &vector);

    Matrix transpose();

    Matrix inverse();

    double max_in_row(int row_index) const;

    double max_in_col(int col_index) const;

    //overloaded ostream operator
    friend std::ostream &operator<<(std::ostream &os, const Matrix &item) {
        for (int i = 0; i < item.rows(); ++i) {
            for (int j = 0; j < item.columns(); ++j) {
                os << item(i, j) << " ";
            }
            cout << "\n";
        }
        return os;
    }

    //overloaded istream operator
    friend std::istream &operator>>(std::istream &input_stream, Matrix &item) {
        for (int i = 0; i < item.rows(); ++i) {
            for (int j = 0; j < item.columns(); ++j) {
                input_stream >> item(i, j);
            }
        }
        if (!input_stream) {
            throw std::runtime_error("Invalid input (matrix input error)\n");
        }
        return input_stream;
    }

private:
    int rows_;
    int columns_;
    vector<vector<double>> data_;

    static void swap(Matrix &first, Matrix &second);
};


#endif //OPTIMIZATION_ASSIGNMENT_3_MATRIX_HPP