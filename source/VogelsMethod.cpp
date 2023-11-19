#include "../headers/VogelsMethod.hpp"

#include <iostream>
#include <climits>
#include <cfloat>

using namespace std;

void VogelsMethod::start_method(Matrix C, Vector S, Vector D) {
    cout << "-------------------------------------------\n";
    cout << "------------- Vogel's Method --------------\n";
    cout << "-------------------------------------------\n\n";

    bool problemIsSolvable = isSolvable(C, S, D);
    Matrix C_copy = Matrix(C);

    if (problemIsSolvable) {
        int m = C.rows();
        int n = C.columns();

        Matrix X = Matrix(m, n);
        Vector row_difference = Vector(m, 0);
        Vector col_difference = Vector(n, 0);

        calculate_row_difference(C, row_difference);
        calculate_col_difference(C, col_difference);

        while (true) {
            int index_of_max_row_difference = index_of_max_element(row_difference);
            int index_of_max_col_difference = index_of_max_element(col_difference);
            int col_index, row_index;

            if (row_difference[index_of_max_row_difference] < 0 || col_difference[index_of_max_col_difference] < 0) {
                break;
            }

            if (row_difference[index_of_max_row_difference] > col_difference[index_of_max_col_difference]) {
                row_index = index_of_max_row_difference;
                col_index = index_of_min_element_in_row(C, row_index);

                set_value(X, S, D, row_index, col_index);
            } else {
                col_index = index_of_max_col_difference;
                row_index = index_of_min_element_in_col(C, col_index);

                set_value(X, S, D, row_index, col_index);
            }

            if(D[col_index] == 0) {
                col_difference[col_index] = -1;
                for (int i = 0; i < m; ++i) {
                    C(i, col_index) = INT_MAX;
                }
                calculate_row_difference(C, row_difference);
            }
            if (S[row_index] == 0) {
                row_difference[row_index] = -1;
                for (int i = 0; i < n; ++i) {
                    C(row_index, i) = INT_MAX;
                }
                calculate_col_difference(C, col_difference);
            }
        }

        printSolution(X, C_copy);
    }
}

bool VogelsMethod::isSolvable(const Matrix &C, const Vector &S, const Vector &D) {
    double sum_S = 0, sum_D = 0;
    int num_of_negative_elements = 0;

    for (int i = 0; i < S.size(); i++) {
        sum_S += S[i];
        if (S[i] < 0) num_of_negative_elements++;
    }
    for (int i = 0; i < D.size(); i++) {
        sum_D += D[i];
        if (D[i] < 0) num_of_negative_elements++;
    }
    for (int i = 0; i < C.rows(); i++) {
        for (int j = 0; j < C.columns(); j++) {
            if (C(i, j) < 0) num_of_negative_elements++;
        }
    }

    if (num_of_negative_elements != 0) {
        cout << "Method is not applicable!\n";
        return false;
    }

    if (sum_S != sum_D) {
        cout << "The problem is not balanced!\n";
        return false;
    }

    return true;
}

void VogelsMethod::calculate_row_difference(const Matrix &C, Vector &row_difference) {
    for (int i = 0; i < C.rows(); i++) {
        auto min1 = DBL_MAX, min2 = DBL_MAX;
        for (int j = 0; j < C.columns(); j++) {
            if (C(i, j) < min1) {
                min2 = min1;
                min1 = C(i, j);
            } else if (C(i, j) < min2) {
                min2 = C(i, j);
            }
        }

        if(min1 == DBL_MAX){
            row_difference[i] = -1;
        } else if(min2 == DBL_MAX) {
            row_difference[i] = 1;
        } else {
            row_difference[i] = min2 - min1;
        }
    }
}

void VogelsMethod::calculate_col_difference(const Matrix &C, Vector &col_difference) {
    for (int j = 0; j < C.columns(); j++) {
        auto min1 = DBL_MAX, min2 = DBL_MAX;
        for (int i = 0; i < C.rows(); i++) {
            if (C(i, j) < min1) {
                min2 = min1;
                min1 = C(i, j);
            } else if (C(i, j) < min2) {
                min2 = C(i, j);
            }
        }

        if(min1 == DBL_MAX){
            col_difference[j] = -1;
        } else if(min2 == DBL_MAX) {
            col_difference[j] = 1;
        } else {
            col_difference[j] = min2 - min1;
        }
    }
}

int VogelsMethod::index_of_max_element(Vector &vec) {
    int index = 0;
    double max_val = vec[0];

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > max_val) {
            max_val = vec[i];
            index = i;
        }
    }
    return index;
}

int VogelsMethod::index_of_min_element_in_row(const Matrix &C, int row_index) {
    auto min_val = DBL_MAX;
    int index = -1;

    for (int j = 0; j < C.columns(); j++) {
        if (C(row_index, j) < min_val) {
            min_val = C(row_index, j);
            index = j;
        }
    }
    return index;
}

int VogelsMethod::index_of_min_element_in_col(const Matrix &C, int col_index) {
    auto min_val = DBL_MAX;
    int index = -1;

    for (int i = 0; i < C.rows(); i++) {
        if (C(i, col_index) < min_val) {
            min_val = C(i, col_index);
            index = i;
        }
    }
    return index;
}

void VogelsMethod::set_value(Matrix &X, Vector &S, Vector &D, int i, int j) {
    auto min_val = min(S[i], D[j]);
    X(i, j) = min_val;
    S[i] -= min_val;
    D[j] -= min_val;
}


void VogelsMethod::printSolution(Matrix &X, const Matrix &C){
    cout << "--Matrix X--\n";
    for (int i = 0; i < X.rows(); i++){
        for(int j = 0; j < X.columns(); j++){
            cout << X(i,j) << " ";
        }
        cout << "\n";
    }

    double cost = 0;
    for (int i = 0; i < X.rows(); i++){
        for(int j = 0; j < X.columns(); j++){
            cost += X(i,j)*C(i,j);
        }
    }
    cout << "--The total distribution cost = " << cost << "\n\n";
}
