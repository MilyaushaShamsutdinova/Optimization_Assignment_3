#include "../headers/VogelsMethod.hpp"

#include <iostream>
#include <climits>

using namespace std;

void VogelsMethod::start_method(Matrix C, Vector S, Vector D) {
    cout << "-------------------------------------------\n";
    cout << "------------- Vogel's Method --------------\n";
    cout << "-------------------------------------------\n\n";

    bool problemIsSolvable = isSolvable(C, S, D);

    if (problemIsSolvable) {
        int m = C.rows();
        int n = C.columns();

        printInitialTable(C, S, D); // Печать начальной таблицы

        Matrix X = Matrix(m, n);
        Vector row_d = Vector(m, 0);
        Vector col_d = Vector(n, 0);

        calculate_row_difference(C, row_d, col_d, m, n);
        calculate_col_difference(C, row_d, col_d, m, n);

        while (true) {
            int max_row_ind = max_ind(row_d);
            int max_col_ind = max_ind(col_d);

            if (row_d[max_row_ind] < 0 || col_d[max_col_ind] < 0) {
                break;
            }

            if (row_d[max_row_ind] > col_d[max_col_ind]) {
                int min_i = find_min_ind_in_row(C, row_d, max_row_ind, m, n);
                set_value(X, S, D, max_row_ind, min_i);
                row_d[max_row_ind] = -1;

                if (D[min_i] == 0) {
                    col_d[min_i] = -1;
                }

                // Mark the row as deleted
                for (int j = 0; j < n; ++j) {
                    C(max_row_ind, j) = INT_MAX;
                }

                calculate_col_difference(C, row_d, col_d, m, n);
            } else {
                int min_i = find_min_ind_in_col(C, col_d, max_col_ind, m, n);
                set_value(X, S, D, min_i, max_col_ind);
                col_d[max_col_ind] = -1;

                if (S[min_i] == 0) {
                    row_d[min_i] = -1;
                }

                // Mark the column as deleted
                for (int i = 0; i < m; ++i) {
                    C(i, max_col_ind) = INT_MAX;
                }

                calculate_row_difference(C, row_d, col_d, m, n);
            }
        }

        cout << "--Distribution Table--\n";
        // Вывод таблицы X
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << X(i, j) << " ";
            }
            cout << "\n";
        }

        int total_cost = calculateTotalCost(X, C);
        cout << "The total distribution cost = " << total_cost << "\n";
    }
}

bool VogelsMethod::isSolvable(const Matrix &C, const Vector &S, const Vector &D) {
    int sum_S = 0, sum_D = 0;
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

void VogelsMethod::calculate_row_difference(const Matrix &C, Vector &row_d, Vector &col_d, int m, int n) {
    for (int i = 0; i < m; i++) {
        int min1 = INT_MAX, min2 = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (C(i, j) < min1) {
                min2 = min1;
                min1 = C(i, j);
            } else if (C(i, j) < min2) {
                min2 = C(i, j);
            }
        }
        row_d[i] = min2 - min1;
    }
}

void VogelsMethod::calculate_col_difference(const Matrix &C, Vector &row_d, Vector &col_d, int m, int n) {
    for (int j = 0; j < n; j++) {
        int min1 = INT_MAX, min2 = INT_MAX;
        for (int i = 0; i < m; i++) {
            if (C(i, j) < min1) {
                min2 = min1;
                min1 = C(i, j);
            } else if (C(i, j) < min2) {
                min2 = C(i, j);
            }
        }
        col_d[j] = min2 - min1;
    }
}

int VogelsMethod::max_ind(Vector &vec) {
    int max_index = 0;
    int max_val = vec[0];

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > max_val) {
            max_val = vec[i];
            max_index = i;
        }
    }
    return max_index;
}

int VogelsMethod::find_min_ind_in_row(const Matrix &C, Vector &row_d, int row, int m, int n) {
    int min_val = INT_MAX;
    int min_index = -1;

    for (int j = 0; j < n; j++) {
        if (C(row, j) < min_val && row_d[j] == 0) {
            min_val = C(row, j);
            min_index = j;
        }
    }
    return min_index;
}

int VogelsMethod::find_min_ind_in_col(const Matrix &C, Vector &col_d, int col, int m, int n) {
    int min_val = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < m; i++) {
        if (C(i, col) < min_val && col_d[i] == 0) {
            min_val = C(i, col);
            min_index = i;
        }
    }
    return min_index;
}

void VogelsMethod::set_value(Matrix &X, Vector &S, Vector &D, int i, int j) {
    int min_val = min(S[i], D[j]);
    X(i, j) = min_val;
    S[i] -= min_val;
    D[j] -= min_val;
}

void VogelsMethod::printInitialTable(const Matrix &C, Vector &S, Vector &D) {
    cout << "--Initial table--\n";

    for (int i = 0; i < C.rows(); i++) {
        for (int j = 0; j < C.columns(); j++) {
            cout << C(i, j) << " ";
        }
        cout << S[i] << "\n";
    }
    for (int j = 0; j < D.size(); j++) {
        cout << D[j] << " ";
    }
    cout << "\n\n";
}

bool VogelsMethod::check_unbalanced_problem(Matrix &X, Vector &S, Vector &D, int m, int n) {
    int sum_S = 0, sum_D = 0;

    for (int i = 0; i < S.size(); i++) {
        sum_S += S[i];
    }
    for (int i = 0; i < D.size(); i++) {
        sum_D += D[i];
    }

    if (sum_S != sum_D) {
        return true;
    }

    return false;
}

int VogelsMethod::calculateTotalCost(Matrix &X, const Matrix &C) {
    int total_cost = 0;
    for (int i = 0; i < X.rows(); ++i) {
        for (int j = 0; j < X.columns(); ++j) {
            total_cost += X(i, j) * C(i, j);
        }
    }
    return total_cost;
}
