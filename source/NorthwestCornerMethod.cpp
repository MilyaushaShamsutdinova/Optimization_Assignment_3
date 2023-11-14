#include "../headers/NorthwestCornerMethod.hpp"

#include <iostream>

using namespace std;

void NorthwestCornerMethod::start_method(const Matrix &C, Vector &S, Vector &D){
    bool problemIsSolvable = isSolvable(C,S,D);
    cout << "-------------------------------------------\n";
    cout << "--------- Northwest Corner Method ---------\n";
    cout << "-------------------------------------------\n\n";
    //print input parameter table
    printInitialTable(C,S,D);
    //print that it is northsest method

    if(problemIsSolvable){
        Matrix X = Matrix(C.rows(), C.columns());
        int i = 0, j = 0;

        while(i < C.rows() & j < C.columns()){
            setValues(X,S,D,i,j);
            if(S[i] == 0){
                i++;
            }
            else j++;
        }

        printSolution(X,C);
    }
}

bool NorthwestCornerMethod::isSolvable(const Matrix &C, Vector &S, Vector &D){
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

void NorthwestCornerMethod::printInitialTable(const Matrix &C, Vector &S, Vector &D){
    cout << "Initial table:\n";
    int sum = 0;

    for(int i = 0; i < C.rows(); i++){
        for(int j = 0; j < C.columns(); j++){
            cout << C(i,j) << " ";

        }
        cout << S[i] << "\n";
    }
    for(int j = 0; j < D.size(); j++){
        cout << D[j] << " ";
        sum += D[j];
    }
    cout << sum << "\n\n";
}


void NorthwestCornerMethod::setValues(Matrix &X, Vector &S, Vector &D, int i, int j){
    X(i,j) = min(S[i], D[j]);
    S[i] -= X(i,j);
    D[j] -= X(i,j);
}

void NorthwestCornerMethod::printSolution(Matrix &X, const Matrix &C){

    cout << "Initial basic feasible solution:\n\n";
    cout << "Matrix X:\n";
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
    cout << "The total distribution cost = " << cost << "\n";
}

