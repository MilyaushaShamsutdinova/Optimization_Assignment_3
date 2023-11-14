#include "../headers/RusselsMethod.hpp"

#include <iostream>

using namespace std;

void RusselsMethod::start_method(Matrix C, Vector S, Vector D){
    cout << "-------------------------------------------\n";
    cout << "------------- Russel's Method -------------\n";
    cout << "-------------------------------------------\n\n";
    bool problemIsSolvable = isSolvable(C,S,D);

    if(problemIsSolvable){
        int m = C.rows();
        int n = C.columns();

        Matrix X = Matrix(m, n);
        Matrix U = Matrix(m, 1);
        Matrix V = Matrix(1, n);

        Matrix ones_row = Matrix(1, n);
        Matrix ones_col = Matrix(m, 1);
        Vector usable_rows = Vector(m, 1);
        Vector usable_cols = Vector(n, 1);

        for(int row = 0; row < m; row++){
            U(row, 0) = C.max_in_row(row);
            ones_col(row, 0) = 1;
        }
        for(int col = 0; col < n; col++){
            V(0, col) = C.max_in_col(col);
            ones_row(0, col) = 1;
        }

        Matrix Delta = C - U*ones_row - ones_col*V;

        while(true){
            Vector maxCoordinates = max_coordinates(Delta, usable_rows, usable_cols, m, n);
            if(maxCoordinates[0] == -1 || maxCoordinates[1] == -1){
                break;
            }
            setValues(X, S, D, maxCoordinates[0], maxCoordinates[1]);

            //continue
            if(S[maxCoordinates[0]] == 0){
                usable_rows[maxCoordinates[0]] = 0;
            }
            if(D[maxCoordinates[1]] == 0){
                usable_cols[maxCoordinates[1]] = 0;
            }
        }

        printSolution(X,C);
    }
}

bool RusselsMethod::isSolvable(const Matrix &C, Vector &S, Vector &D){
    int sum_S = 0, sum_D = 0;
    int num_of_negative_elements = 0;

    for(int i = 0; i < S.size(); i++){
        sum_S += S[i];
        if(S[i] < 0) num_of_negative_elements++;
    }
    for(int i = 0; i < D.size(); i++){
        sum_D += D[i];
        if(D[i] < 0) num_of_negative_elements++;
    }
    for(int i = 0; i < C.rows(); i++){
        for(int j = 0; j < C.columns(); j++){
            if(C(i,j) < 0) num_of_negative_elements++;
        }
    }

    if(num_of_negative_elements != 0) {
        cout << "Method is not applicable!\n";
        return false;
    }

    if(sum_S != sum_D){
        cout << "The problem is not balanced!\n";
        return false;
    }

    return true;
}


void RusselsMethod::setValues(Matrix &X, Vector &S, Vector &D, int i, int j){
    X(i,j) = min(S[i], D[j]);
    S[i] -= X(i,j);
    D[j] -= X(i,j);
}

void RusselsMethod::printSolution(Matrix &X, const Matrix &C){
//    cout << "--Initial basic feasible solution--\n\n";
    cout << "--Matrix X--\n";
    for (int i = 0; i < X.rows(); i++){
        for(int j = 0; j < X.columns(); j++){
            cout << X(i,j) << " ";
        }
        cout << "\n";
    }

    int cost = 0;
    for (int i = 0; i < X.rows(); i++){
        for(int j = 0; j < X.columns(); j++){
            cost += X(i,j)*C(i,j);
        }
    }
    cout << "The total distribution cost = " << cost << "\n\n";
}

Vector RusselsMethod::max_coordinates(Matrix &Delta, Vector &usable_rows, Vector &usable_cols, int m, int n) {
    Vector maxCoordinates = Vector(2, -1);
    for(int i = 0; i < m; i++){
        if(usable_rows[i] == 0){
            continue;
        }
        for(int j = 0; j < n; j++){
            if(usable_cols[j] == 0 || Delta(i,j) >= 0){
                continue;
            }
            if(maxCoordinates[0] == -1 && maxCoordinates[1] == -1){
                maxCoordinates[0] = i;
                maxCoordinates[1] = j;
            }
            if(Delta(i,j) < Delta(maxCoordinates[0],maxCoordinates[1])){
                maxCoordinates[0] = i;
                maxCoordinates[1] = j;
            }
        }
    }
    return maxCoordinates;
}

