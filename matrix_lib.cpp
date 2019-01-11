#include "matrix_lib.h"
#include <iostream>
#include <math.h>

using namespace std;

TMatrix::TMatrix(int _H, int _W, DVECTOR Temp){
    Height = _H;
    Width = _W;
    Matrix = Temp;
    Matrix.resize(_H);
    for (int i = 0; i < _H; i++)
        Matrix[i].resize(_W);
};

void PrintTMatrix(TMatrix Matr){
    for (int i = 0; i < Matr.Matrix.size(); i++){
        for (int j = 0; j < Matr.Matrix[i].size(); j++)
            cout << Matr.Matrix[i][j] << " ";
        cout << endl;
    }
};

TMatrix SumTMatrix(TMatrix Matr_1, TMatrix Matr_2){
    DVECTOR temp;
    int H, W;
    if ( Matr_1.Height != Matr_2.Height || Matr_1.Width != Matr_2.Width ){
        cout << "Error: different size of matrices";
        return TMatrix(0, 0, temp);
    }
    H = Matr_1.Height;
    W = Matr_1.Width;
    for ( int i = 0; i < H; i++ ){
        temp.push_back({});
        for ( int j = 0; j < W; j++ )
            temp[i].push_back(Matr_1.Matrix[i][j] + Matr_2.Matrix[i][j]);
    }
    return TMatrix(H, W, temp);
};

TMatrix MulTMatrix(TMatrix Matr_1, TMatrix Matr_2){
    DVECTOR temp;
    int H, W, L, tmp;
    H = Matr_2.Height;
    W = Matr_1.Width;
    if ( H != W ){
        cout << "Error: different size of matrices";
        return TMatrix(0, 0, temp);
    }
    L = H;
    H = Matr_1.Height;
    W = Matr_2.Width;
    for ( int i = 0; i < H; i++ ){
        temp.push_back({});
        for ( int j = 0; j < W; j++ ){
            tmp = 0;
            for ( int k = 0; k < L; k++ ){
                tmp += Matr_1.Matrix[i][k]*Matr_2.Matrix[k][j];
            }
            temp[i].push_back(tmp);
        }
    }
    return TMatrix(H, W, temp);
};

TMatrix MulTMatrixConst(TMatrix Matr, float Const){
    DVECTOR temp;
    for ( int i = 0; i < Matr.Height; i++ ){
        temp.push_back({});
        for ( int j = 0; j < Matr.Width; j++)
            temp[i].push_back(Matr.Matrix[i][j] * Const);
    }
    return TMatrix(Matr.Height, Matr.Width, temp);
};

DVECTOR GetMatr(int H, int W, DVECTOR A){
    DVECTOR temp;
    int S = A.size();
    for ( int i = 0; i < S; i++ ){
        if ( i == H ) continue;
        temp.push_back({});
        for ( int j = 0; j < S; j++ ){
            if ( j == W ) continue;
            temp.back().push_back(A[i][j]);
        }
    }
    return temp;
}

float Determinant(DVECTOR A){
    int H = A.size();
    float temp = 0;
    if ( H == 1 )
        return A[0][0];
    for ( int i = 0; i < H; i++ )
        temp += pow(-1, i) * A[0][i] * Determinant(GetMatr(0, i, A));
    return temp;
}

float DetTMatrix(TMatrix Matr){
    if ( Matr.Height != Matr.Width ){
        cout << "Error: different size of matrice";
        return 0;
    }
    return Determinant(Matr.Matrix);
};

DVECTOR Transposition(DVECTOR A){
    DVECTOR temp;
    for ( int i = 0; i < A[0].size(); i++ ){
        temp.push_back({});
        for ( int j = 0; j < A.size(); j++ )
            temp.back().push_back(A[j][i]);
    }
    return temp;
}

TMatrix InversTMatrix(TMatrix Matr){
    int det = DetTMatrix(Matr);
    DVECTOR temp;
    if (!det) return TMatrix(0, 0, temp);
    for ( int i = 0; i < Matr.Height; i++ ){
        temp.push_back({});
        for ( int j = 0; j < Matr.Width; j++ )
            temp[i].push_back( pow(-1, i+j) * Determinant(GetMatr(i, j, Matr.Matrix)) / det );
    }
    temp = Transposition(temp);
    return TMatrix(Matr.Height, Matr.Width, temp);
};
